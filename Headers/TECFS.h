

#ifndef PROYECTO3_TECFS_H
#define PROYECTO3_TECFS_H
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
    /**
     * Constructor de la clase
     */
    TECFS();
    /**
     * corre la ventana principal
     */
    void run();
    /**
     * actualiza los botones
     * @param mousepos posicion del mouse
     * @param socket socket para conectarse
     */
    void update(Vector2f mousepos,TcpSocket* socket);
    /**
     * dibuja el UI
     */
    void render();
    /**
     * Extrae la informacion de un XML
     * @return un vector con IP, port y path
     */
    vector<string> xmlextract();

};


#endif //PROYECTO3_TECFS_H
