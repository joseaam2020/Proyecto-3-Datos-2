#include "ControllerNode.h"
#include "rapidjson/document.h"
#include "Huffman.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include <filesystem>
#include <fstream>
#include <DiskSearcher.h>

/**
 * @file ControllerNode.cpp
 * @version 1.0
 * @title ControllerNode
 * @brief Controlador de Discos de RAID 5
 */

/**
*@brief Constructor de la clase,crea interfaz para ingresar valores de los discos y crea threads para recibir y cargar archivos
**/
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
                    if ((diskSizeInt >= 1 && diskSizeInt <= 500000) && (numberSectorInt > 1 && numberSectorInt <= 10))
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

    /*
    this->getDiskPaths()->push_back("/home/jose430/Escritorio/Disk1/");
    this->getDiskPaths()->push_back("/home/jose430/Escritorio/Disk2/");
    this->getDiskPaths()->push_back("/home/jose430/Escritorio/Disk3/");
    this->getFilePaths()->push_back("/home/jose430/Documentos/Narnia1");
    
    std::cout << "after new set" << std::endl;
    */

    std::thread gettingDisks(std::bind(&ControllerNode::getDisksAndFiles,this));
    std::thread addingDisks(std::bind(&ControllerNode::addDisksAndFiles,this));
    gettingDisks.join();
    addingDisks.join();
 
}

/**
 *@brief basado en la cantidad de paths guardados, crea y almacena archivos 
 **/
void ControllerNode::addDisksAndFiles()
{
    bool insufficientDisksMessageSent = false; 
    while(true){
        //std::cout << "starting" << std::endl;
        this->currentNumberOfDisks = this->getDiskPaths()->size();
        if(this->lastNumberOfDisks < this->currentNumberOfDisks){
            //std::cout << this->lastNumberOfDisks << this->currentNumberOfDisks << std::endl;
            insufficientDisksMessageSent = false;
            DiskNode newDisk = DiskNode();
            newDisk.setSize(this->diskSize*1000);
            newDisk.setSectorSize((this->diskSize*1000)/this->numberSector);
            this->getDiskVector()->push_back(newDisk);
            //std::cout << "After pushing the new disk" << std::endl;
            int counter = 0;
            for(DiskNode disk: *(this->disks)){
                disk.createSectors(this->diskPaths->at(counter));
                disk.getParitySectors()->clear();
                disk.setCurrentSector(1);
                counter++;
            }
            //std::cout << "After creating sectors" << std::endl;
            if(this->disks->size() >= 3){
                int j = 0;
                bool right = true;
                //std::cout << disks->size();
                for(int i = 1; i <= numberSector;i++){
                    //std::cout << j << std::endl;
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
                //std::cout << "After assign parity" << std::endl;
            }
            this->lastNumberOfDisks++;
            //std::cout << "After all" << std::endl;
        }
        if(this->disks->size()>=3){
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
string jsonSender(string type, string name, string path);
/**
 * @brief recibe archivos y discos a traves de sockets
 **/
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
    while(true){
        std::cout << "Reset" << std::endl;
        listener.accept(socket);
        sf::Packet packetS, packetR;
        rapidjson::Document jsonPet;
        while (true)
        {
            socket.receive(packetR);
            if (packetR.getData() != NULL)
            {
                jsonPet = jsonReceiverCN(packetR);
                std::string path; 
                std::string type = jsonPet["type"].GetString();
                if(type == "0"){
                    //Path a un disk
                    path = jsonPet["path"].GetString();
                    this->diskPaths->push_back(path);
                } else if(type == "1"){
                    //Path a un file
                    path = jsonPet["path"].GetString();
                    this->filePaths->push_back(path);
                    std::cout << "Received file" << std::endl;
                } else if(type == "2"){
                    break;
                } else if(type == "3"){
                    std::string description = jsonPet["description"].GetString();
                    DiskSearcher searcher = DiskSearcher();
                    searcher.insertdiskpath(*this->diskPaths);
                    searcher.find(description);
                    searcher.getBookNames(searcher.libros,"/");
                    for(int i = 0; i < searcher.metaD.size();i++){
                        std::string send = jsonSender("1",searcher.metaD.at(i),searcher.libros.at(i));
                        Huffman huff = Huffman(); //instancia de huffman
                        string json;//formato json
                        json = send;
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
                        socket.send(packetS);//manda el json a cliente
                        packetS.clear();//vacia los packets
                    }
                    
                }
            }
            
            packetR.clear();
        }
    
    }
    
}

/**
 * @brief funcion main, crea un controller
 **/
int main()
{
    ControllerNode controller = ControllerNode();
    
    return 0;
}

/**
 * @brief divide un texto basado en las posiciones dadas y crea threads para escribirlo en los discos
 * @param string fileName nombre del archivo de donde proviene el texto
 * @param string inFile texto en el archivo
 * @param int initialPosition posicion inicial de la division
 * @param int finalPosition posicion final de la division
 * */
void ControllerNode::writeDivision(std::string fileName, std::string inFile,int initialPosition, int finalPosition, int divisionSize){
    std::cout << "inFile for div: " << inFile << std::endl;
    for(int i = 0; i < (this->disks->size());i++){
        //std::cout << "I: " << initialPosition << "F: " << finalPosition << std::endl;
        std::string divisionData;
        divisionData = inFile.substr(initialPosition,(finalPosition-initialPosition));
        std::cout << "Division Data: " << divisionData << std::endl;
        std::cout << fileName << std::endl;
        std::thread newWriteThread(std::bind(&DiskNode::write,&this->disks->at(i),divisionData,fileName,this->diskPaths->at(i)));
        newWriteThread.join();
        initialPosition = finalPosition; 
        finalPosition += divisionSize;
    }
}

/**
 * @brief separa y escribe el archivo que indica el path en los discos, encargandose de la paridad
 * @param string path direccion del archivo a guardar
 **/
void ControllerNode::writeToDisks(std::string path){
    std::ifstream newFile; 
    newFile.open(path);
    if(newFile.fail()){
        std::cout << "Failed to open file" << std::endl;
        return;
    }
    std::string inFile;
    std::string tempLine; 
    while(getline(newFile,tempLine)){
        inFile += tempLine;
    }
    std::cout << "inf file: " << inFile << std::endl;
    int fileSize = sizeof(inFile.front()) * inFile.size();
    //std::cout << "Size of file: " << std::endl;
    //dividir entre numero de discos menos 1
    int divisionSize = (fileSize/(this->disks->size()));
    //std::cout << "Size of division: " << std::endl;
    int initialPosition = 0;
    int finalPosition = divisionSize; 
    std::size_t slash = path.find_last_of("/\\");
    std::size_t period = path.find_last_of(".");
    std::string fileNameWithType = path.substr(slash+1);
    std::string fileName = fileNameWithType.substr(0,period);
    std::thread writeDivisionThread(std::bind(&ControllerNode::writeDivision,this,fileName,inFile,initialPosition,finalPosition,divisionSize));
    writeDivisionThread.join();
    //std::cout << "Finished writing";
    std::vector<std::string> SectorLibros; 
    std::vector<std::string> SectorMeta; 
    int j = 0;
    bool right = true;
    for(int i = 1; i <= numberSector;i++){
        //std::cout << "got in for" << std::endl;
        SectorLibros.clear();
        SectorMeta.clear();
        for(int disk = 0; disk < this->diskPaths->size();disk++){ 
            if(disk != j){
                //std::cout << "From Disk: " << disk << std::endl;
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
                //std::cout << inLibro << inMeta << std::endl;
                SectorLibros.push_back(inLibro);
                SectorMeta.push_back(inMeta);
            }
        }
        //std::cout << SectorLibros.size() << std::endl;
        while(SectorLibros.size() > 1){
            std::string libro1 = SectorLibros.back();
            SectorLibros.pop_back();
            std::string libro2 = SectorLibros.back();
            SectorLibros.pop_back();
            std::string parity; 

            while(libro1.length() > 0 && libro2.length() > 0){
                /*int front1 = (int) libro1.front();
                int front2 = (int) libro2.front(); 
                int frontParity = front1^front2;
                std::cout << "front: " << libro1.front() << "int: " << front1;
                std::cout << "front: " << libro2.front() << "int: " << front2;
                std::cout << "front: " << "P " << frontParity << std::ezndl;*/
                char parityChar = libro1.front()^libro2.front();
                //std::cout << parityChar << libro1.size() << " " << libro2.size() << std::endl;
                parity += parityChar;
                libro1 = libro1.substr(1);
                libro2 = libro2.substr(1);
            }
            if(libro1.length() > 0 ){
                parity += libro1;
            } else if(libro2.length() > 0 ){
                parity += libro2;
            }
            //std::cout << "Termino parity M" << std::endl;
            SectorLibros.push_back(parity);
        }
        //std::cout << SectorMeta.size() << std::endl;
        while(SectorMeta.size() > 1){
            std::string meta1 = SectorMeta.back();
            SectorMeta.pop_back();
            std::string meta2 = SectorMeta.back();
            SectorMeta.pop_back();
            std::string parity; 

            while(meta1.length() > 0 && meta2.length() > 0){
                /*
                int front1 = (int) meta1.front();
                int front2 = (int) meta2.front(); 
                int frontParity = front1^front2;
                std::cout << "frontM: " << meta1.front() << "int: " << front1;
                std::cout << "frontM: " << meta2.front() << "int: " << front2;
                std::cout << "frontM: " << "P " << frontParity << std::endl;*/
                char parityChar = meta1.front()^meta2.front();
                //std::cout << parityChar << meta1.size() << " " << meta2.size() << std::endl;
                parity += parityChar;
                meta1 = meta1.substr(1);
                meta2 = meta2.substr(1);
            }
             if(meta1.length() > 0 ){
                parity += meta1;
            } else if(meta2.length() > 0 ){
                parity += meta2;
            }
            //std::cout << "Termino parity M" << std::endl;
            SectorMeta.push_back(parity);
        }
        //std::cout << "Data parity: "<< SectorLibros.at(0) <<  "Meta parity: "<<SectorMeta.at(0) << std::endl;
        if(SectorMeta.size()==1 && SectorLibros.size()==1){
            this->disks->at(j).writeParity(SectorLibros.at(0),SectorMeta.at(0),this->diskPaths->at(j),i);
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

/**
 * @brief recibe un packet y lo convierte en un archivo json
 **/
rapidjson::Document jsonReceiverCN(sf::Packet packet)
{
    Huffman huff = Huffman();
    string map_str;
    string encoded;
    rapidjson::Document petD;

    packet >> map_str >> encoded;
    string decoded;

    decoded = huff.decompress(map_str,encoded);
    //cout<<decoded<<endl;

    const char* petChar = decoded.c_str();
    petD.Parse(petChar);

    return petD;
}

string jsonSender(string type, string name, string path)
{
    string jsonStr = R"({"type":")"+ type + R"(","name":")" + name + R"(","path":")" + path +"\"}";
    return jsonStr;
}

