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
#include "Button.h"
#include "Textbox.h"

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



    //TEXT
    Text title;
    Textbox textbox;
    Text list;
    string listtext;

    //Variables
    bool keepOpen;

public:
    ceSearch();
    void run();
    void update(Vector2f mousepos);
    void render();
};


#endif //PROYECTO2_CESEARCH_H
