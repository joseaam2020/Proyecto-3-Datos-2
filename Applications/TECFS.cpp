
#include "TECFS.h"

TECFS::TECFS() {
    this->keepOpen = true;
    disknum = 0;

    //WINDOW
    this->width = 600;
    this->height = 600;
    this->window = new RenderWindow(VideoMode(width,height), "TECFS-DISK");

    //BACKGROUND
    this->background.setSize(Vector2f(width,height));
    this->background.setFillColor(Color(223, 218, 224));
    this->background.setPosition(0,0);

    this->toptitle.setSize(Vector2f(width,100));
    this->toptitle.setFillColor(Color(149, 125, 212));
    this->toptitle.setPosition(0,0);

    //FONT
    if (!this->font.loadFromFile("../fonts/Exton Free Trial.ttf"))
        cout << "Couldn't load font" << endl;

    if(!TX.loadFromFile("../fonts/arial.ttf")){
        cout << "Could not load font" << endl;
    }

    //UTILITY LOAD
    this->filer = new FileLoader();

    //TEXT
    this->title.setFont(font);
    this->title.setString("TECFS-DISK");
    this->title.setCharacterSize(70);
    this->title.setPosition(width/2-title.getGlobalBounds().width/2,5);
    this->title.setFillColor(Color::Black);

    this->diskt.setFont(TX);
    this->diskt.setString("# disks: " + to_string(disknum));
    this->diskt.setCharacterSize(50);
    this->diskt.setPosition(width/2-diskt.getGlobalBounds().width/2,200);
    this->diskt.setFillColor(Color::Black);

    //BUTTONS
    this->filebtn = new Button((width/2)-100,350,200,100,&this->font,"ADD DISK",
                               Color(149, 125, 212),
                               Color(113, 96, 158),
                               Color(202, 190, 232),40);

}
/**
 * @brief jsonSender se encarga de formatear los mensajes de servidor-> cliente
 * @param memory espacio de memoria alocada
 * @param value valor de la variable
 * @param variable nombre de la variable
 * @param ref cantiad de referencias
 * @return un string en formato JSON listo para enviar
 */
string jsonSender(string type, string ip,string port, string path)
{
    string jsonStr = R"({"type":")"+ type + R"(","ip":")" + ip + R"(","port":")" + port + R"(","path":")" + path +"\"}";
    return jsonStr;
}

/**
 * @brief jsonReviever se encarga de desempaquetar el mensaje JSON del cliente
 * @param packet paquete que envio el cliente
 * @return un documento donde se pueden extraer las variables
 */
Document jsonReceiver(Packet packet){
    Huffman huff = Huffman();
    string map_str;
    string encoded;
    Document petD;

    packet >> map_str >> encoded;
    string decoded;

    decoded = huff.decompress(map_str,encoded);
    cout<<decoded<<endl;

    const char* petChar = decoded.c_str();
    petD.Parse(petChar);

    return petD;
}

vector<string> TECFS::xmlextract() {
    //vector output
    vector<string> xmlinfo;

    //abrir archivo xml
    TiXmlDocument XMLdoc(this->filer->folder + "/setup.xml");
    bool loadOkay = XMLdoc.LoadFile();
    if (loadOkay) {
        cout << "setup.xml loaded" << endl;
        TiXmlElement *pRoot, *pIP, *pPort, *pLoc;
        pRoot = XMLdoc.FirstChildElement("DiskNode");
        if (pRoot) {
            // Parse IP address
            pIP = pRoot->FirstChildElement("IpAdress");
            xmlinfo.push_back(pIP->Attribute("ip"));

            cout << "IpAdress: ip=" << pIP->Attribute("ip")<< endl;
            // Parse Port
            pPort = pRoot->FirstChildElement("Port");
            xmlinfo.push_back(pPort->Attribute("port"));
            cout << "Port: " << pPort->Attribute("port") << endl;
            //Parse Location
            pLoc = pRoot->FirstChildElement("Location");
            xmlinfo.push_back(pLoc->Attribute("address"));
            cout << "Location: " << pLoc->Attribute("address") << endl;
            return xmlinfo;

        } else {
            cout << "Cannot find 'Configuration' node" << endl;
            return static_cast<vector<string>>(0);
        }
    }
    return vector<string>();
}



void TECFS::update(Vector2f mousepos, TcpSocket* socket) {
    Packet packetS;
    string json;

    this->filebtn->update(mousepos);
    //BUTTON ACTIONS
    if(this->filebtn->is_pressed()){
        this->filer->load_folder();
        cout<<filer->folder<<endl;
        vector<string> xmlinfo = xmlextract();

        disknum++;
        diskt.setString("# disks: " + to_string(disknum));

        Huffman huff = Huffman();
        json = jsonSender("8",xmlinfo.at(0),xmlinfo.at(1),xmlinfo.at(2));
        cout<<json<<endl;
        string encoded;
        string map_str;

        map_str = huff.start_huffman(json);
        encoded = huff.compressed_message(json);
        cout<< map_str<<endl;
        cout<<encoded<<endl;
        /*
        packetS << map_str << encoded;//empaqueta el json
        socket->send(packetS);//manda el json a cliente
        packetS.clear();//vacia los packets
         */
    }

}

void TECFS::render() {
    this->window->draw(this->background);
    this->window->draw(this->toptitle);


    this->filebtn->render(this->window);

    this->window->draw(this->title);
    this->window->draw(this->diskt);
}

void TECFS::run() {
    //Se definen la variables necesarias para la comunicacion por sockets
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    Packet packetR;

    //Se conecta el cliente al socket
    socket.connect(ip, 8080);
    socket.setBlocking(false);

    while (this->keepOpen) {

        Event event;
        while (this->window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                cout<<"end"<<endl;
                this->window->close();
                this->keepOpen = false;
            }
            if (event.type == Event::MouseButtonPressed) {
                cout << "--------------------" << endl;
                cout << "X: " << event.mouseButton.x << " | Y: " << event.mouseButton.y << endl;
            }
        }


        this->window->clear(Color::White);
        Vector2f mousepos = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));

        update(mousepos,&socket);

        render();
        this->window->display();
    }
}
int main(){
    TECFS TFS = TECFS();
    TFS.run();
    return 0;
}