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
    if (!this->font.loadFromFile("../fonts/Exton Free Trial.ttf"))
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

    this->testbtn = new Button((width/2)-100,400,200,100,&this->font,"XML read",
                               Color(149, 125, 212),
                               Color(113, 96, 158),
                               Color(202, 190, 232),40);

}


string ceRobot::jsonSender(string type, string path) {

    string jsonStr = R"({"type":")"+ type  + R"(","path":")" + path + "\"}";
    return jsonStr;
}


void ceRobot::foldersender() {
    vector<string> files;
    DIR *dr;
    dr = ::opendir(this->filer->folder.c_str());
    struct dirent *en;
    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            cout<<en->d_name<<endl;
            files.push_back(this->filer->folder+ "/"+en->d_name);
        }
        closedir(dr); //close all directory
    }
    files.erase(files.end());
    vector<string>::iterator it;
    it = files.begin();
    int size = files.size()-1;
    int i = 0;
    while(i<size-2){
        ++it;
        i++;
    }

    files.erase(it);
    for(int a = 0;a<files.size();a++){
        cout<<files.at(a)<<endl;
    }
}


void ceRobot::update(Vector2f mousepos) {
    //BUTTON UPDATE
    this->filebtn->update(mousepos);
    this->testbtn->update(mousepos);

    //BUTTON ACTIONS
    if(this->filebtn->is_pressed()){
        this->filer->load_folder();
        cout<<filer->folder<<endl;
        foldersender();
    }
    //XML READER
    if(this->testbtn->is_pressed()){
        TiXmlDocument XMLdoc("../TestTXT/test.xml");
        bool loadOkay = XMLdoc.LoadFile();
        if (loadOkay) {
            cout << "test.xml loaded" << endl;
            TiXmlElement *pRoot, *pIP, *pPort, *pLoc;
            pRoot = XMLdoc.FirstChildElement("DiskNode");
            if (pRoot) {
                // Parse IP address
                pIP = pRoot->FirstChildElement("IpAdress");
                cout << "IpAdress: ip=" << pIP->Attribute("ip")<< endl;
                // Parse Port
                pPort = pRoot->FirstChildElement("Port");
                cout << "Port: " << pPort->Attribute("port") << endl;
                //Parse Location
                pLoc = pRoot->FirstChildElement("Location");
                cout << "Location: " << pLoc->Attribute("address") << endl;

            } else {
                cout << "Cannot find 'Configuration' node" << endl;
            }
        }
    }
}

void ceRobot::render() {
    this->window->draw(this->background);
    this->window->draw(this->toptitle);


    this->filebtn->render(this->window);
    this->testbtn->render(this->window);

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


        this->window->clear(Color::White);
        Vector2f mousepos = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));

        update(mousepos);

        render();
        this->window->display();
    }
}

int main(){
    ceRobot CR = ceRobot();
    CR.run();
    return 0;
}