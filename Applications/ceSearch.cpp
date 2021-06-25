
#include "ceSearch.h"


ceSearch::ceSearch() {

    this->keepOpen = true;

    //WINDOW
    this->width = 900;
    this->height = 700;
    this->window = new RenderWindow(VideoMode(width, height), "ceSEARCH");

    //BACKGROUND
    this->background.setSize(Vector2f(width, height));
    this->background.setFillColor(Color(242, 222, 206));
    this->background.setPosition(0, 0);

    //Title backkground
    this->toptitle.setSize(Vector2f(width,100));
    this->toptitle.setFillColor(Color(250, 176, 115));
    this->toptitle.setPosition(0,0);

    //TEXTRECT
    textrect.setSize(Vector2f(300,50));
    textrect.setFillColor(Color::White);
    textrect.setPosition(width/2-300/2,150);

    textrectB.setSize(Vector2f(308,58));
    textrectB.setFillColor(Color::Black);
    textrectB.setPosition(width/2-300/2-4,150-4);

    listrect.setSize(Vector2f (width-200,height-300));
    listrect.setFillColor(Color(245, 243, 240));
    listrect.setPosition(100,250);

    listStopper.setSize(Vector2f (width,150));
    listStopper.setFillColor(Color(242, 222, 206));
    listStopper.setPosition(0,100);

    listStopper2.setSize(Vector2f (width,50));
    listStopper2.setFillColor(Color(242, 222, 206));
    listStopper2.setPosition(0,650);

    //FONT
    if (!this->font.loadFromFile("fonts/Exton Free Trial.ttf"))
        cout << "Couldn't load font" << endl;

    if(!TX.loadFromFile("fonts/arial.ttf")){
        cout << "Could not load font" << endl;
    }
    //TEXT
    this->title.setFont(font);
    this->title.setString("ceSearch");
    this->title.setCharacterSize(70);
    this->title.setPosition(width/2-title.getGlobalBounds().width/2,5);
    this->title.setFillColor(Color::Black);

    this->textbox = Textbox(25,Color::Black, false);
    this->textbox.setfont(TX);
    this->textbox.setPosition(Vector2f(width/2-300/2,157));
    this->textbox.setLimit(true,18);

    list.setFont(TX);
    listtext = "";
    list.setString(listtext);
    list.setCharacterSize(25);
    list.setFillColor(Color::Black);
    list.setPosition(110,255);

    //UTILITY LOAD
    this->filer = new FileLoader();

    //BUTTONS
    searchbtn = new Button(width/2 + 200,150,150,50,&this->font,"Search",
                           Color(199, 199, 199),
                           Color(166, 166, 166),
                           Color(227, 227, 227),40);

    openbtn = new Button(50,30,150,50,&this->font,"Open",
                           Color(199, 199, 199),
                           Color(166, 166, 166),
                           Color(227, 227, 227),40);
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

    std::cout << "Received" << std::endl;

    decoded = huff.decompress(map_str,encoded);
    cout<<decoded<<endl;

    const char* petChar = decoded.c_str();
    petD.Parse(petChar);

    return petD;
}

/**
 * @brief jsonSender se encarga de formatear los mensajes de servidor-> cliente
 * @param memory espacio de memoria alocada
 * @param value valor de la variable
 * @param variable nombre de la variable
 * @param ref cantiad de referencias
 * @return un string en formato JSON listo para enviar
 */
string jsonSender(string type, string description)
{
    string jsonStr = R"({"type":")"+ type + R"(","description":")" + description +"\"}";
    return jsonStr;
}

void ceSearch::update(Vector2f mousepos, TcpSocket* socket) {
    //update button
    searchbtn->update(mousepos);
    openbtn->update(mousepos);

    //BUTTON ACTIONS
    if(openbtn->is_pressed()){
        filer->getfilename();
        cout<<filer->filename<<endl;
    }

}
void ceSearch::render() {
    //main window
    this->window->draw(this->background);
    this->window->draw(listrect);

    //TEXTO DE LISTA
    window->draw(list);
    //-----
    this->window->draw(this->toptitle);
    this->window->draw(this->title);

    window->draw(listStopper);
    window->draw(listStopper2);

    this->window->draw(textrectB);
    this->window->draw(textrect);
    //BUTTONS
    searchbtn->render(window);
    openbtn->render(window);
    //TEXT
    this->textbox.drawTo(*this->window);
}

void closeSocket(TcpSocket* socket){
    Huffman huff = Huffman(); //instancia de huffman
    string json; Packet packetS;
    json = jsonSender("2","");//formato json
    cout<<json<<endl;
    string encoded;
    string map_str;
    //comprimir
    map_str = huff.start_huffman(json);
    encoded = huff.compressed_message(json);
    cout<< map_str<<endl;
    cout<<encoded<<endl;
    //mandar
    packetS << map_str << encoded;//empaqueta el json
    socket->send(packetS);//manda el json a cliente
    packetS.clear();//vacia los packets
    socket->disconnect();
}

void ceSearch::run() {
    //Se definen la variables necesarias para la comunicacion por sockets
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    Packet packetR,packetS;

    //Se conecta el cliente al socket
    socket.connect(ip, 8080);
    socket.setBlocking(false);

    while (this->keepOpen) {

        Event event;
        while (this->window->pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    closeSocket(&socket);
                    this->window->close();
                    this->keepOpen = false;
                    break;

                case Event::MouseButtonPressed:
                    if(Mouse::isButtonPressed(Mouse::Left)){
                        Vector2f mpos = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
                        if(textrect.getGlobalBounds().contains(mpos)){
                            textbox.setSelected(!textbox.getSelected());
                        }
                        searchbtn->update(mpos);
                        if(searchbtn->is_pressed()){
                            if(textbox.getText() != ""){
                                listtext = "";
                                list.setString(listtext);
                                std::cout << textbox.getText() << std::endl;
                                string json;
                                Huffman huff = Huffman();
                                json = jsonSender("3",textbox.getText());
                                cout<<json<<endl;
                                string encoded;
                                string map_str;

                                map_str = huff.start_huffman(json);
                                encoded = huff.compressed_message(json);
                                cout<< map_str<<endl;
                                cout<<encoded<<endl;
                                packetS << map_str << encoded;//empaqueta el json
                                socket.send(packetS);//manda el json a cliente
                                packetS.clear();//vacia los packets
                            }
                        }
                    }
                    break;
                case Event::MouseWheelMoved:
                    if (event.mouseWheel.delta >= 0 ){
                        if(list.getPosition().y + list.getGlobalBounds().height > 300){
                            list.setPosition(list.getPosition().x,list.getPosition().y-5);
                        }
                    }
                    else if (event.mouseWheel.delta <= 0){
                        if(list.getPosition().y  < 255 ){
                            list.setPosition(list.getPosition().x,list.getPosition().y+5);
                        }
                    }
                    break;
                case Event::TextEntered:
                    textbox.typedOn(event);
                    break;
            }
        }
        socket.receive(packetR);
        if (packetR.getData() != NULL) {
            Document petition = jsonReceiver(packetR);//desempaqueta el JSON

            //separa el json en variables
            string type = petition["type"].GetString();
            std::cout << "After type" << std::endl;
            string content = petition["name"].GetString();
            std::cout << "After name" << std::endl;
            string fPath = petition["path"].GetString();
            std::cout << "After path" << std::endl;

            if(type == "1"){
                listtext += content + "\n";
                list.setString(listtext);
            }
        }
        packetR.clear();
        //clear
        this->window->clear(Color::White);
        //update mouse pos
        Vector2f mousepos = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
        //update buttons
        update(mousepos,&socket);
        //dibujar UI
        render();
        //mostrar UI
        this->window->display();
    }
}

int main(){
    ceSearch CS = ceSearch();
    CS.run();
    return 0;
}