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
#include "../Source/Button.cpp"
#include "../Headers/FileLoader.h"
#include "../Source/FileLoader.cpp"
#include "../Headers/Huffman.h"
#include "../Source/Huffman.cpp"
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
    ceRobot();
    void run();
    void update(Vector2f mousepos, TcpSocket* socket);
    void render();
    vector<string> foldersender();
};


#endif //PROYECTO2_CEROBOT_H
