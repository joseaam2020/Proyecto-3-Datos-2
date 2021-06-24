#include "DiskNode.h"
#include <cstring>

void DiskNode::createSectors(){
    int numberSectors = this->size/this->sectorSize;
    for(int i = 0; i < numberSectors; i++){
        std::ofstream newSector; 
        newSector.open("Libros" + std::to_string(i+1) +".txt");
        newSector << "This is The Hobbit" + std::to_string(i+1);
        newSector.close();
        newSector.open("Meta" + std::to_string(i+1) +".txt");
        newSector.close();  
    }
    
}

void DiskNode::write(std::string data, std::string fileName){
    std::ifstream libroCurrentSector; 
    std::ifstream metaCurrentSector; 
    libroCurrentSector.open("Libros" + std::to_string(this->currentSector) + ".txt");
    metaCurrentSector.open("Meta" + std::to_string(this->currentSector) + ".txt");
    if(!(libroCurrentSector.fail() || metaCurrentSector.fail())){
        std::string inLibro;
        std::string tempLine;
        while(getline(libroCurrentSector,tempLine)){
            inLibro += tempLine;
        }
        std::string inMeta;
        tempLine;
        while(getline(metaCurrentSector,tempLine)){
            inMeta += tempLine;
        }
        int sizeOfInLibro = sizeof(inLibro.front()) * inLibro.size();
        int sizeOfInMeta = sizeof(inMeta.front()) * inMeta.size(); 
        int sizeOfInputData = sizeof(data.front()) * data.size();
        
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

        if(currentSize == this->sectorSize){
            this->currentSector++;
            return this->write(data,fileName);
        } else {  
            std::ofstream writingLibros;
            std::ofstream writingMeta;
            writingLibros.open("Libros" + std::to_string(this->currentSector) + ".txt");
            writingMeta.open("Meta" + std::to_string(this->currentSector) + ".txt");
            if(inputSize + currentSize > this->sectorSize){ //Si no cabe en memoria
                std::string newInputData;
                std::string newInLibroData;
                int newSizeOfInLibro = this->sectorSize - currentSize - sizeOfInputMeta;
                
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

                writingLibros << inLibro << newInLibroData;
                writingMeta << inMeta << metaData;
                
                writingLibros.close();
                writingMeta.close();

                this->currentSector++;
                return this->write(newInputData,fileName);
            } else{ 
                writingLibros << inLibro << data;
                writingMeta << inMeta << metaData;
                writingMeta.close();
                writingLibros.close();
            }
        }
    } else {
        std::cout << "Failed to access memory: could be full" << std::endl;
    }
    
}