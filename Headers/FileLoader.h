//
// Created by david on 25/5/21.
//

#ifndef PROYECTO2_FILELOADER_H
#define PROYECTO2_FILELOADER_H
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

class FileLoader {

public:
    string folder;

    /**
     * Carga la imagen
     */
    void load_folder();
    /**
     * lee el string del CMD
     * @param cmd string
     * @return lo que se obtuvo del comando
     */
    string getCmdOutput(string cmd);
    /**
     * Devuelve un mensaje de error
     */
    void error();

};


#endif //PROYECTO2_FILELOADER_H
