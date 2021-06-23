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
#include "Button.h"
#include "Button.cpp"
#include "FileLoader.h"
#include "FileLoader.cpp"
#include "tinyxml.h"

using namespace std;
using namespace sf;


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
    Button* testbtn;


    //TEXT
    Text title;

    //Variables
    bool keepOpen;

    //FILE LOADER
    FileLoader* filer;

public:
    ceRobot();
    void run();
    void update(Vector2f mousepos);
    void render();
    void foldersender();
};


#endif //PROYECTO2_CEROBOT_H
