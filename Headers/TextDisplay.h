//
// Created by david on 25/6/21.
//

#ifndef PROYECTO3_TEXTDISPLAY_H
#define PROYECTO3_TEXTDISPLAY_H
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include <vector>
#include "../Headers/Button.h"

using namespace std;
using namespace sf;


class TextDisplay {
public:
    int width;
    int height;

    //window
    RenderWindow* window;

    //GUI
    RectangleShape background;
    RectangleShape toptitle;


    //FONTS
    Font font;


    //TEXT
    Text title;
    Text texto;
    string txt;

    //Variables
    bool keepOpen;
    /**
     * Constructor de la clase
     */
    TextDisplay(const string& titles, string textos);
    /**
     * Corre el UI del ceRobot
     */
    void run();
    /**
     * dibuja el UI en la pantalla cada frame
     */
    void render();
    /**
     * Extrae el nombre de los archivos de un folder y manda el path
     * @return un vector con el path de todos los archivos del folder
     */
};


#endif //PROYECTO3_TEXTDISPLAY_H
