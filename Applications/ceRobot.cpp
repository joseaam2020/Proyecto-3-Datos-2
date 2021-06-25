#include "../Headers/ceRobot.h"

ceRobot::ceRobot() {
    this->keepOpen = true;

    //WINDOW
    this->width = 600;
    this->height = 600;
    this->window = new RenderWindow(VideoMode(width,height), "ceROBOT");

    //BACKGROUND
    this->background.setSize(Vector2f(width,height));
    this->background.setFillColor(Color(223, 218, 224));
    this->background.setPosition(0,0);

    this->toptitle.setSize(Vector2f(width,100));
    this->toptitle.setFillColor(Color(149, 125, 212));
    this->toptitle.setPosition(0,0);

    //FONT
    if (!this->font.loadFromFile("fonts/Exton Free Trial.ttf"))
        cout << "Couldn't load font" << endl;


    //UTILITY LOAD
    this->filer = new FileLoader();

    //TEXT
    this->title.setFont(font);
    this->title.setString("ceRobot");
    this->title.setCharacterSize(70);
    this->title.setPosition(width/2-title.getGlobalBounds().width/2,5);
    this->title.setFillColor(Color::Black);

    //BUTTONS
    this->filebtn = new Button((width/2)-100,200,200,100,&this->font,"Load Folder",
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
string jsonSender(string type, string path)
{
    string jsonStr = R"({"type":")"+ type + R"(","path":")" + path +"\"}";
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


vector<string> ceRobot::foldersender() {
    //crear vector
    vector<string> files;
    DIR *dr; //abrir file
    dr = ::opendir(this->filer->folder.c_str());
    struct dirent *en;
    if (dr) {
        while ((en = readdir(dr)) != NULL) {//ir por cada archivo
            cout<<en->d_name<<endl;
            string end = en->d_name;
            if(end != "." &&  end != ".."){//revisar que no sea . o ..
                files.push_back(this->filer->folder+ "/"+en->d_name);
            }
        }
        closedir(dr); //close all directory
    }

    for(int a = 0;a<files.size();a++){
        cout<<files.at(a)<<endl;
    }

    return files;
}


void ceRobot::update(Vector2f mousepos,TcpSocket* socket) {
    //sockets
    Packet packetS;
    string json;
    //BUTTON UPDATE
    this->filebtn->update(mousepos);

    //BUTTON ACTIONS
    //si le boton de file es oprimido
    if(this->filebtn->is_pressed()){
        //crea vector
        vector<string> files;
        //se carga el folder
        this->filer->load_folder();
        cout<<filer->folder<<endl;
        //se crea el path
        files = foldersender();
        //loop para mandar
        for(int i = 0; i < files.size();i++){
            Huffman huff = Huffman(); //instancia de huffman
            json = jsonSender("10",files.at(i));//formato json
            cout<<json<<endl;
            string encoded;
            string map_str;
            //comprimir
            map_str = huff.start_huffman(json);
            encoded = huff.compressed_message(json);
            cout<< map_str<<endl;
            cout<<encoded<<endl;
            //mandar
            /*
            packetS << map_str << encoded;//empaqueta el json
            socket->send(packetS);//manda el json a cliente
            packetS.clear();//vacia los packets
            */
        }
    }
}

void ceRobot::render() {
    //main window
    this->window->draw(this->background);
    this->window->draw(this->toptitle);

    //buttons
    this->filebtn->render(this->window);

    //text
    this->window->draw(this->title);
}


void ceRobot::run() {
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
                this->window->close();
                this->keepOpen = false;

            }
            if (event.type == Event::MouseButtonPressed) {
                cout << "--------------------" << endl;
                cout << "X: " << event.mouseButton.x << " | Y: " << event.mouseButton.y << endl;
            }
        }

        //clear
        this->window->clear(Color::White);
        //mouse pos
        Vector2f mousepos = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
        //update mouse button
        update(mousepos,&socket);
        //draw UI
        render();
        //show
        this->window->display();
    }
}

int main(){
    ceRobot CR = ceRobot();
    CR.run();
    return 0;
}