

#ifndef PROYECTO3_TECFS_H
#define PROYECTO3_TECFS_H
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

class TECFS {
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
    Font TX;

    //BUTTONS
    Button* filebtn;
    Button* testbtn;


    //TEXT
    Text title;
    Text diskt;

    //Variables
    bool keepOpen;
    int disknum;

    //FILE LOADER
    FileLoader* filer;
public:
    TECFS();
    void run();
    void update(Vector2f mousepos,TcpSocket* socket);
    void render();
    vector<string> xmlextract();

};


#endif //PROYECTO3_TECFS_H
