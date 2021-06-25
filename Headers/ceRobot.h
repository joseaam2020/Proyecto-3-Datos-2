//
// Created by david on 22/6/21.
//

#ifndef PROYECTO2_CEROBOT_H
#define PROYECTO2_CEROBOT_H
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include <vector>
#include "../Headers/Button.h"
#include "../Headers/FileLoader.h"
#include "../Headers/Huffman.h"
#include "rapidjson/document.h"
#include "tinyxml.h"

using namespace std;
using namespace sf;
using namespace rapidjson;


class ceRobot {
private:
    int width;
    int height;

    //window
    RenderWindow* window;

    //GUI
    RectangleShape background;
    RectangleShape toptitle;


    //FONTS
    Font font;

    //BUTTONS
    Button* filebtn;


    //TEXT
    Text title;

    //Variables
    bool keepOpen;

    //FILE LOADER
    FileLoader* filer;

public:
    /**
     * Constructor de la clase
     */
    ceRobot();
    /**
     * Corre el UI del ceRobot
     */
    void run();
    /**
     * actualiza el color y la accion de los botones
     * @param mousepos posicion del mouse
     * @param socket socket para conectar
     */
    void update(Vector2f mousepos, TcpSocket* socket);
    /**
     * dibuja el UI en la pantalla cada frame
     */
    void render();
    /**
     * Extrae el nombre de los archivos de un folder y manda el path
     * @return un vector con el path de todos los archivos del folder
     */
    vector<string> foldersender();
};


#endif //PROYECTO2_CEROBOT_H
