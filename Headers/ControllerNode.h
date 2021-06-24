#ifndef CONTROLLERNODE_H_
#define CONTROLLERNODE_H_

#include <vector>
#include "DiskNode.h"

class ControllerNode{
    private:
        int diskSize = 1; 
        int numberSector = 1; 
        std::vector<std::string>* diskPaths = new std::vector<std::string>();
        std::vector<std::string>* filePaths = new std::vector<std::string>();
        std::vector<DiskNode>* disks = new std::vector<DiskNode>();
        int currentNumberOfDisks = 0; 
        int lastNumberOfDisks = 0;  
    public: 
        ControllerNode();
        int getDiskSize(){
            return this->diskSize; 
        } 
        int getNumberSector(){
            return this->numberSector; 
        }
        std::vector<std::string>* getDiskPaths(){
            return this->diskPaths;
        }
        std::vector<DiskNode>* getDiskVector(){
            return this->disks;
        }
        void addDisks(); 
        void getDisksAndFiles();
};

#endif /* CONTROLLERNODE_H_*/