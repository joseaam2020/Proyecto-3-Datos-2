#include "DiskNode.h"
#include <cstring>

/**
 * @file DiskNode.cpp
 * @version 1.0
 * @title DiskNode
 * @brief Disco virtual para conectar con ControllerNode
 */

/**
 * @brief crea todos los sectores del disco (archivos Libros y Meta .txt)
 * @param string path del disco, donde se guardan los archivos.
 **/
void DiskNode::createSectors(std::string pathToDisk){
    int numberSectors = this->size/this->sectorSize;
    for(int i = 0; i < numberSectors; i++){
        std::ofstream newSector; 
        newSector.open(pathToDisk + "Libros" + std::to_string(i+1) +".txt");
        newSector.close();
        newSector.open(pathToDisk + "Meta" + std::to_string(i+1) +".txt");
        newSector.close();  
    }
    
}

/**
 * @brief escribe a los archivos asignados con paridad
 * @param string data que se escribe en archivo libro del sector
 * @param string meta que se escribe en archivo meta del sector
 * @param string pathToDisk path donde estan los archivos
 * @param int paritySector sector de paridad al que se quiere escribir
 **/
void DiskNode::writeParity(std::string data, std::string meta, std::string pathToDisk, int paritySector){
    bool parityMet = false;
    for(int parityNumber : this->paritySectors){
        if(parityNumber = paritySector){
            parityMet = true;
        }
    }
    if(!parityMet){
        std::cout << "Could not write parity: Parity sector not available" << std::endl;
        return;
    }
    std::ofstream writingLibros;
    std::ofstream writingMeta;
    writingLibros.open(pathToDisk + "Libros" + std::to_string(paritySector) + ".txt");
    writingMeta.open(pathToDisk + "Meta" + std::to_string(paritySector) + ".txt");
    
    if(writingLibros.fail()||writingMeta.fail()){
        std::cout << "Failed to open" << std::endl;
    }

    writingLibros << data;
    writingMeta << meta;

    writingLibros.close();
    writingMeta.close();
}

/**
 * @brief escribe la data en los sectores de no paridad
 * @param string data que se escribe en los archivos 
 * @param string fileName del cual proviene la data
 * @param string pathToDisk donde se encuentran los archivos
 **/
void DiskNode::write(std::string data, std::string fileName,std::string pathToDisk){
    std::cout << data << std::endl;
    std::ifstream libroCurrentSector; 
    std::ifstream metaCurrentSector; 
    libroCurrentSector.open(pathToDisk + "Libros" + std::to_string(this->currentSector) + ".txt");
    metaCurrentSector.open(pathToDisk + "Meta" + std::to_string(this->currentSector) + ".txt");
    if(!(libroCurrentSector.fail() || metaCurrentSector.fail())){
        std::string inLibro;
        std::string tempLine;
        while(getline(libroCurrentSector,tempLine)){
            inLibro += tempLine;
        }
        std::string inMeta;
        while(getline(metaCurrentSector,tempLine)){
            inMeta += tempLine;
        }
        int sizeOfInLibro = sizeof(inLibro.front()) * inLibro.size();
        int sizeOfInMeta = sizeof(inMeta.front()) * inMeta.size(); 
        int sizeOfInputData = sizeof(data.front()) * data.size();
        
        std::cout << pathToDisk << std::endl;
        std::cout << "Current Sector: " << this->currentSector << std::endl;
        std::cout << "Size of In libro: " << sizeOfInLibro << std::endl;
        std::cout << "Size of In meta: " << sizeOfInMeta << std::endl;
        std::cout << "Size of input: " << sizeOfInputData << std::endl;

        std::string metaData; 
        metaData += fileName;//nombre
        metaData += "#";
        metaData += std::to_string(sizeOfInputData);//tamaño
        metaData += "#";
        metaData += std::to_string(inLibro.size());//Posicion
        metaData += "#";

        libroCurrentSector.close();
        metaCurrentSector.close();

        int sizeOfInputMeta = sizeof(metaData.front()) * metaData.size();
        long inputSize = sizeOfInputData+sizeOfInputMeta;
        long currentSize = sizeOfInLibro+sizeOfInMeta;

        std::cout << "Size of Input Meta: " << sizeOfInputMeta << std::endl;
        std::cout << "Size of Input: " << inputSize << std::endl;
        std::cout << "Current size: " << currentSize << std::endl;

        bool isParitySector = false;
        for(int sector : this->paritySectors){
            if(sector == currentSector){
                isParitySector = true;
            }
        }
        std::cout << "Parity: " << isParitySector << std::endl;
        if(currentSize == this->sectorSize || isParitySector){
            this->currentSector++;
            return this->write(data,fileName,pathToDisk);
        } else {  
            std::ofstream writingLibros;
            std::ofstream writingMeta;
            writingLibros.open(pathToDisk + "Libros" + std::to_string(this->currentSector) + ".txt");
            writingMeta.open(pathToDisk + "Meta" + std::to_string(this->currentSector) + ".txt");
            std::cout << "Opened to write: " << writingLibros.fail() << writingMeta.fail() << std::endl;
            if(inputSize + currentSize > this->sectorSize){ //Si no cabe en memoria
                std::string newInputData;
                std::string newInLibroData;
                int newSizeOfInLibro = this->sectorSize - currentSize - sizeOfInputMeta;
                
                if(newSizeOfInLibro < 0){
                    std::cout << "Was less" << std::endl;
                    this->currentSector++;
                    return this->write(data,fileName,pathToDisk);
                }

                std::cout << "Size of new In libro: " << newSizeOfInLibro << std::endl;
                
                for(int i = 0; i < data.length();i++){ //Cuanto cabe
                    if(i < newSizeOfInLibro/sizeof(data.front())){
                        newInLibroData += data.at(i);
                    } else{
                        newInputData += data.at(i);
                    }
                }
                metaData = ""; //Nueva Metadata
                metaData += fileName;
                metaData += "#";
                metaData += std::to_string(newSizeOfInLibro);
                metaData += "#";
                metaData += std::to_string(inLibro.size());
                metaData += "#";

                std::cout << "wrote with adjutment" << std::endl;
                writingLibros << inLibro << newInLibroData;
                writingMeta << inMeta << metaData;

                writingLibros.close();
                writingMeta.close();

                this->currentSector++;
                return this->write(newInputData,fileName,pathToDisk);
            } else{ 
                std::cout << "wrote without adjutment" << std::endl;
                writingLibros << inLibro << data;
                writingMeta << inMeta << metaData;
                writingMeta.close();
                writingLibros.close();
                this->currentSector++;
            }
        }
    } else {
        std::cout << "Failed to access memory: could be full" << std::endl;
    }
    
}