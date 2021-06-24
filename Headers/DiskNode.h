#ifndef DISKNODE_H_
#define DISKNODE_H_ 

#include <iostream>
#include <fstream>
#include <vector>

class DiskNode{ 
    private: 
        int size;
        int sectorSize;
        int currentSector = 1;
        std::vector<int> paritySectors; 
    public: 
        DiskNode(){};
        void setSize(int size){
            this->size = size; 
        }
        void setSectorSize(int sectorSize){
            this->sectorSize = sectorSize;
        }
        std::vector<int>* getParitySectors(){
            return &this->paritySectors;
        }
        void setCurrentSector(int sector){
            this->currentSector = sector;
        }
        int getCurrentSector(){
            return this->currentSector;
        }
        void createSectors(std::string pathToDisk);
        void write(std::string data, std::string fileName, std::string pathToDisk);
        void writeParity(std::string data, std::string meta, std::string pathToDisk, int paritySector);
};


#endif /* DISKNODE_H_*/