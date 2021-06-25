//
// Created by david on 23/6/21.
//

#ifndef PROYECTO2_CESEARCH_H
#define PROYECTO2_CESEARCH_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "rapidjson/document.h"
#include <iostream>
#include <vector>
#include "../Headers/Button.h"
#include "../Source/Button.cpp"
#include "../Headers/Textbox.h"
#include "../Headers/FileLoader.h"
#include "../Source/FileLoader.cpp"
#include "../Headers/Huffman.h"
#include "../Source/Huffman.cpp"

using namespace std;
using namespace sf;
using namespace rapidjson;

class ceSearch {
private:
    int width;
    int height;

    //window
    RenderWindow* window;

    //GUI
    RectangleShape background;
    RectangleShape toptitle;
    RectangleShape textrect;
    RectangleShape textrectB;
    RectangleShape listStopper;
    RectangleShape listStopper2;
    RectangleShape listrect;


    //FONTS
    Font font;
    Font TX;

    //BUTTONS
    Button* searchbtn;
    Button* openbtn;



    //TEXT
    Text title;
    Textbox textbox;
    Text list;
    string listtext;

    //Variables
    FileLoader* filer;
    bool keepOpen;

public:
    /**
     * Constructor de la clase
     */
    ceSearch();
    /**
     * corre la ventana principal
     */
    void run();
    /**
     * Actualiza los botones
     * @param mousepos posicion del mouse
     * @param socket socket para conectar
     */
    void update(Vector2f mousepos, TcpSocket* socket);
    /**
     * dibujar UI
     */
    void render();
};


#endif //PROYECTO2_CESEARCH_H
