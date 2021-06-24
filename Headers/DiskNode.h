#ifndef DISKNODE_H_
#define DISKNODE_H_ 

#include <iostream>
#include <fstream>

class DiskNode{ 
    private: 
        int size;
        int sectorSize;
        int currentSector = 1;
    public: 
        DiskNode(){};
        void setSize(int size){
            this->size = size; 
        }
        void setSectorSize(int sectorSize){
            this->sectorSize = sectorSize;
        }
        void createSectors();
        void write(std::string data, std::string fileName);
};


#endif /* DISKNODE_H_*/