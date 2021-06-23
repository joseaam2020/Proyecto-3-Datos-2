#include "ControllerNode.h"
#include <SFML/Graphics.hpp>
#include <iostream>

ControllerNode::ControllerNode(){
    sf::RenderWindow window(sf::VideoMode(300,300),"Disk Size Query");
    
    //Creando Fondo 
    sf::RectangleShape background; 
    background.setSize(sf::Vector2f(300.0,300.0));
    background.setFillColor(sf::Color(22,37,50));
    
    //Creando texto
    sf::Text diskSizeQuery, numberSectorQuery; 
    sf::Text diskSizeText, numberSectorText; 
    std::string diskSizeString, numberSectorString;
    
    //Creando Botones
    sf::RectangleShape diskSizeButton,numberSectorButton,readyButton;
    sf::Text DSButtonText, NSButtonText, readyText; 

    //Cargando Font
    sf::Font font; 
    if(!font.loadFromFile("../Code 7x5.ttf")){
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
    diskSizeText.setFillColor(sf::Color(252,58,81));
    numberSectorText.setFillColor(sf::Color(252,58,81));
    DSButtonText.setFillColor(sf::Color::White);
    NSButtonText.setFillColor(sf::Color::White);
    readyText.setFillColor(sf::Color::White);
    
    diskSizeQuery.setCharacterSize(50);
    numberSectorQuery.setCharacterSize(50);
    diskSizeText.setCharacterSize(50);
    numberSectorText.setCharacterSize(50);
    DSButtonText.setCharacterSize(50);
    NSButtonText.setCharacterSize(50);
    readyText.setCharacterSize(50);

    diskSizeQuery.setString("Ingrese tamaño de discos en KB");
    numberSectorQuery.setString("Ingrese numero de sectores por disco");
    diskSizeText.setString("0");
    numberSectorText.setString("0");
    DSButtonText.setString("Listo");
    NSButtonText.setString("Listo");
    readyText.setString("Listo?");

    //Posicionando Texto
    diskSizeQuery.setPosition(5,5);
    diskSizeText.setPosition(5,65);
    diskSizeButton.setSize(sf::Vector2f(50.0,50.0));
    diskSizeButton.setPosition(150,65);
    DSButtonText.setPosition(150,65);
    numberSectorQuery.setPosition(5,125);
    numberSectorText.setPosition(5,185);
    numberSectorButton.setSize(sf::Vector2f(50.0,50.0));
    numberSectorButton.setPosition(150,185);
    NSButtonText.setPosition(150,185);

    //Creando Bools
    bool numberSectorBool = false;
    bool diskSizeBool = false;

    //Window Loop    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type = sf::Event::TextEntered){
                if(diskSizeBool){

                }
                else if(numberSectorBool){

                }
            }
        }
    }
}

void ControllerNode::run(){
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

int main(){
    ControllerNode controller = ControllerNode();
    return 0;
}