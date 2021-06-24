#include "ControllerNode.h"
#include "rapidjson/document.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include <filesystem>
#include <fstream>

ControllerNode::ControllerNode()
{
    sf::RenderWindow window(sf::VideoMode(600, 300), "Disk Size Query");

    //Creando Fondo
    sf::RectangleShape background;
    background.setPosition(0, 0);
    background.setSize(sf::Vector2f(600.0, 300.0));
    background.setFillColor(sf::Color(34, 40, 49));

    //Creando texto
    sf::Text diskSizeQuery, numberSectorQuery;
    sf::Text diskSizeText, numberSectorText;
    std::string diskSizeString, numberSectorString;
    diskSizeString = "0";
    numberSectorString = "0";

    //Creando Botones
    sf::RectangleShape diskSizeButton, numberSectorButton, readyButton;
    sf::Text DSButtonText, NSButtonText, readyText;

    //Cargando Font
    sf::Font font;
    if (!font.loadFromFile("Code 7x5.ttf"))
    {
        std::cout << "Could not load font" << std::endl;
    }

    //Colocando font
    diskSizeQuery.setFont(font);
    numberSectorQuery.setFont(font);
    diskSizeText.setFont(font);
    numberSectorText.setFont(font);
    DSButtonText.setFont(font);
    NSButtonText.setFont(font);
    readyText.setFont(font);

    //Colocando color, strings y tamaño
    diskSizeQuery.setFillColor(sf::Color::White);
    numberSectorQuery.setFillColor(sf::Color::White);
    diskSizeText.setFillColor(sf::Color(252, 58, 81));
    numberSectorText.setFillColor(sf::Color(252, 58, 81));
    diskSizeButton.setFillColor(sf::Color(48, 71, 94));
    numberSectorButton.setFillColor(sf::Color(48, 71, 94));
    readyButton.setFillColor(sf::Color(48, 71, 94));
    DSButtonText.setFillColor(sf::Color::White);
    NSButtonText.setFillColor(sf::Color::White);
    readyText.setFillColor(sf::Color::White);

    diskSizeQuery.setCharacterSize(20);
    numberSectorQuery.setCharacterSize(20);
    diskSizeText.setCharacterSize(20);
    numberSectorText.setCharacterSize(20);
    DSButtonText.setCharacterSize(20);
    NSButtonText.setCharacterSize(20);
    readyText.setCharacterSize(20);

    diskSizeQuery.setString("Ingrese volumen de discos en KB");
    numberSectorQuery.setString("Ingrese numero de sectores por disco");
    diskSizeText.setString(diskSizeString);
    numberSectorText.setString(numberSectorString);
    DSButtonText.setString("Listo");
    NSButtonText.setString("Listo");
    readyText.setString("Listo?");

    //Posicionando Texto
    diskSizeQuery.setPosition(5, 5);
    diskSizeText.setPosition(20, 65);
    diskSizeButton.setSize(sf::Vector2f(110.0, 50.0));
    diskSizeButton.setPosition(170, 65);
    DSButtonText.setPosition(175, 72);
    numberSectorQuery.setPosition(5, 125);
    numberSectorText.setPosition(20, 185);
    numberSectorButton.setSize(sf::Vector2f(110.0, 50.0));
    numberSectorButton.setPosition(170, 185);
    NSButtonText.setPosition(175, 192);
    readyButton.setSize(sf::Vector2f(180.0, 50.0));
    readyButton.setPosition(400, 245);
    readyText.setPosition(405, 252);

    //Creando Bools
    bool numberSectorBool = false;
    bool diskSizeBool = false;

    //Creando ints
    int numberSectorInt = 0;
    int diskSizeInt = 0;

    //Window Loop
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (diskSizeBool)
                {
                    if (!(event.text.unicode == 8))
                    {
                        diskSizeString += event.text.unicode;
                    }
                    else
                    {
                        if (diskSizeString.length() > 0)
                        {
                            diskSizeString.pop_back();
                        }
                    }
                    diskSizeText.setString(diskSizeString);
                }
                else if (numberSectorBool)
                {
                    if (!(event.text.unicode == 8))
                    {
                        numberSectorString += event.text.unicode;
                    }
                    else
                    {
                        if (numberSectorString.length() > 0)
                        {
                            numberSectorString.pop_back();
                        }
                    }
                    numberSectorText.setString(numberSectorString);
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;
                sf::Vector2f mousePos(mouseX, mouseY);

                if (diskSizeButton.getGlobalBounds().contains(mousePos))
                {
                    if (!diskSizeBool)
                    {
                        diskSizeBool = true;
                        diskSizeButton.setFillColor(sf::Color(46, 204, 113));
                        DSButtonText.setString("Listo?");
                    }
                    else
                    {
                        diskSizeBool = false;
                        diskSizeButton.setFillColor(sf::Color(48, 71, 94));
                        DSButtonText.setString("Listo");
                    }
                }
                else if (numberSectorButton.getGlobalBounds().contains(mousePos))
                {
                    if (!numberSectorBool)
                    {
                        numberSectorBool = true;
                        numberSectorButton.setFillColor(sf::Color(46, 204, 113));
                        NSButtonText.setString("Listo?");
                    }
                    else
                    {
                        numberSectorBool = false;
                        numberSectorButton.setFillColor(sf::Color(48, 71, 94));
                        NSButtonText.setString("Listo");
                    }
                }
                else if (readyButton.getGlobalBounds().contains(mousePos))
                {
                    std::string diskSizeSTDString = diskSizeText.getString();
                    std::string numberSectorSTDString = numberSectorText.getString();
                    try
                    {
                        diskSizeInt = std::stoi(diskSizeSTDString);
                        numberSectorInt = std::stoi(numberSectorSTDString);
                    }
                    catch (std::exception e)
                    {
                        std::cout << "Could not load disk and sector number" << std::endl;
                    }
                    if ((diskSizeInt > 1 && diskSizeInt <= 500000) && (numberSectorInt > 1 && numberSectorInt <= 10))
                    {
                        this->diskSize = diskSizeInt;
                        this->numberSector = numberSectorInt;
                        window.close();
                    }
                    else
                    {
                        readyText.setString("Try again");
                    }
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(diskSizeQuery);
        window.draw(diskSizeText);
        window.draw(diskSizeButton);
        window.draw(DSButtonText);
        window.draw(numberSectorQuery);
        window.draw(numberSectorText);
        window.draw(numberSectorButton);
        window.draw(NSButtonText);
        window.draw(readyButton);
        window.draw(readyText);


        window.display();
    }

    std::thread gettingDisks(std::bind(&ControllerNode::getDisksAndFiles,this));
    std::thread addingDisks(std::bind(&ControllerNode::addDisksAndFiles,this));
    gettingDisks.join();
    addingDisks.join();
    
    /*
        Hacer un thread separado que consiga los discos

        Por cada disco: 
        Si el numero de archivos cambio: 
            Procesar archivos(puede ser una funcion):
            -Convertir libro a bytes
            -Partir bytes
            -Colocar bytes en discos
    */
}


void ControllerNode::addDisksAndFiles()
{
    bool insufficientDisksMessageSent = false; 
    while(true){
        currentNumberOfDisks = this->getDiskPaths()->size();
        if(lastNumberOfDisks < currentNumberOfDisks){
            insufficientDisksMessageSent = false;
            DiskNode newDisk = DiskNode();
            newDisk.setSize(this->diskSize*1000);
            newDisk.setSectorSize((this->diskSize*1000)/this->numberSector);
            this->getDiskVector()->push_back(newDisk);
            int counter = 0;
            for(DiskNode disk: *(this->disks)){
                disk.createSectors(this->diskPaths->at(counter));
                disk.getParitySectors()->clear();
                disk.setCurrentSector(1);
                counter++;
            }
            int j = 0;
            bool right = true;
            for(int i = 1; i <= numberSector;i++){
                disks->at(j).getParitySectors()->push_back(i);
                if(j == disks->size()-1){
                    right= false;
                } if (j == 0){
                    right = true;
                }
                if(right){
                    j++;
                } else{
                    j--;
                }
            }
        }
        if(this->diskPaths->size()>=3){
            if(this->filePaths->size() > 0){
                std::string path;
                path = filePaths->back();
                filePaths->pop_back();
                this->writeToDisks(path);
            }
        } else{ 
            if(!insufficientDisksMessageSent){
                std::cout << "Insufficient disks: Minimum 3" << std::endl;
                insufficientDisksMessageSent = true;
            }
        }
        
    }   
    
}
rapidjson::Document jsonReceiverCN(sf::Packet packet);
void ControllerNode::getDisksAndFiles()
{
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    sf::TcpListener listener;
    int port = 8080;
    bool successfulPortbind = false;
    while (!successfulPortbind)
    {
        try
        {
            listener.listen(port);
            successfulPortbind = true;
        }
        catch (std::exception e)
        {
            port++;
            std::cout << "Trying port: " << port << std::endl;
        }
    }
    std::cout << "Port at: " << std::to_string(port) << std::endl;
    listener.accept(socket);
    sf::Packet packetS, packetR;
    rapidjson::Document jsonPet;
    while (true)
    {
        socket.receive(packetR);
        if (packetR.getData() != NULL)
        {
            jsonPet = jsonReceiverCN(packetR);
        }
        std::string path;
        if(jsonPet["type"].GetInt() == 0){
            //Path a un disk
            path = jsonPet["path"].GetString();
            this->diskPaths->push_back(path);
        } else if(jsonPet["type"].GetInt() == 1){
            //Path a un file
            path = jsonPet["path"].GetString();
            this->filePaths->push_back(path);
        }
        packetR.clear();
    }
    
}

int main()
{
    /*   
    DiskNode newDisk0 = DiskNode();
    DiskNode newDisk1 = DiskNode();
    DiskNode newDisk2 = DiskNode();
    newDisk0.setSize(1000);
    newDisk0.setSectorSize(200);
    newDisk.createSectors("/home/jose430/Escritorio/");
    newDisk.getParitySectors()->push_back(1);
    newDisk.write("THIS IS A STORY ABOUT SOMETHING THAT the comings and goings between our own world and the land of Narnia first began. In those days Mr. Sherlock Holmes was still living in Baker Street and the Bastables were looking for treasure in the Lewisham Road. In those days, if you were a boy you had to wear a stiff Eton collar every day, and schools were usually nastier than now. But meals were nicer; and as for sweets, I won’t tell you how cheap and good they were, because it would only make your mouth water in vain. And in those days there lived in London a girl called Polly Plummer. She lived in one of a long row of houses which were all joined together. One morning she was out in the back garden when a boy scrambled up from the garden next door and put his face over the wall.","Narnia 1","/home/jose430/Escritorio/");
    */
    ControllerNode controller = ControllerNode();
    controller.getDiskPaths()->push_back("/home/jose430/Escritorio/Disk1/");
    controller.getDiskPaths()->push_back("/home/jose430/Escritorio/Disk2/");
    controller.getDiskPaths()->push_back("/home/jose430/Escritorio/Disk3/");
    controller.getFilePaths()->push_back("/home/jose430/Documentos/Narnia1.txt");
    return 0;
}

void ControllerNode::writeToDisks(std::string path){
    std::ifstream newFile; 
    newFile.open(path);
    std::string inFile;
    std::string tempLine; 
    while(getline(newFile,tempLine)){
        inFile += tempLine;
    }
    int fileSize = sizeof(inFile.front()) * inFile.size();
    //dividir entre numero de discos menos 1
    int divisionSize = (fileSize/(this->disks->size()-1));
    int initialPosition = 0;
    int finalPosition = divisionSize; 
    int firstSector = 1; 
    int lastSector = 1; 
    for(int i = 0; i < (this->disks->size()-1);i++){
        std::string divisionData;
        divisionData = inFile.substr(initialPosition,finalPosition);
        std::size_t slash = path.find_last_of("/\\");
        std::size_t period = path.find_last_of(".");
        std::string fileNameWithType = path.substr(slash+1);
        std::string fileName = fileNameWithType.substr(0,period);
        std::thread newWriteThread(std::bind(&DiskNode::write,&this->disks->at(i),divisionData,fileName,this->diskPaths->at(i)));
        newWriteThread.detach();
    }
    lastSector = this->disks->at(0).getCurrentSector();
    std::vector<std::string> SectorLibros; 
    std::vector<std::string> SectorMeta; 
    int j = 0;
    bool right = true;
    for(int i = 1; i <= numberSector;i++){
        SectorLibros.clear();
        SectorMeta.clear();
        for(int disk = 0; disk < this->diskPaths->size();disk++){
            if(disk != j){
                std::ifstream newSectorData;
                std::ifstream newSectorMeta;
                newSectorData.open(this->diskPaths->at(disk) + "Libros" + std::to_string(i) + ".txt");
                newSectorMeta.open(this->diskPaths->at(disk) + "Meta" + std::to_string(i) + ".txt");
                std::string inLibro;
                std::string tempLine;
                while(getline(newSectorData,tempLine)){
                    inLibro += tempLine;
                }
                std::string inMeta;
                while(getline(newSectorMeta,tempLine)){
                    inMeta += tempLine;
                }
                SectorLibros.push_back(inLibro);
                SectorMeta.push_back(inMeta);
            }
        }
        while(SectorLibros.size() > 1){
            std::string libro1 = SectorLibros.back();
            SectorLibros.pop_back();
            std::string libro2 = SectorLibros.back();
            SectorLibros.pop_back();
            std::string parity; 

            while(libro1.length() == 0 && libro2.length() == 0){
                int front1 = (int) libro1.front();
                int front2 = (int) libro2.front(); 
                int frontParity = front1^front2;
                char parityChar = (char)frontParity;
                parity += parityChar;
                libro1 = libro1.substr(1);
                libro2 = libro2.substr(1);
            }

            SectorLibros.push_back(parity);
        }
        while(SectorMeta.size() > 1){
            std::string meta1 = SectorMeta.back();
            SectorMeta.pop_back();
            std::string meta2 = SectorMeta.back();
            SectorMeta.pop_back();
            std::string parity; 

            while(meta1.length() == 0 && meta2.length() == 0){
                int front1 = (int) meta1.front();
                int front2 = (int) meta2.front(); 
                int frontParity = front1^front2;
                char parityChar = (char)frontParity;
                parity += parityChar;
                meta1 = meta1.substr(1);
                meta2 = meta2.substr(1);
            }

            SectorMeta.push_back(parity);
        }
        if(SectorMeta.size()==1 && SectorLibros.size()==1){
            this->disks->at(j).writeParity(SectorLibros.at(0),SectorMeta.at(0),this->diskPaths->at(j),j);
        }
        if(j == disks->size()-1){
            right= false;
        } if (j == 0){
            right = true;
        }
        if(right){
            j++;
        } else{
            j--;
        }
    }
}

rapidjson::Document jsonReceiverCN(sf::Packet packet)
{
    std::string pet;
    rapidjson::Document petD;

    packet >> pet;
    std::cout << pet << std::endl;
    const char* petChar = pet.c_str();
    petD.Parse(petChar);

    return petD;
}

