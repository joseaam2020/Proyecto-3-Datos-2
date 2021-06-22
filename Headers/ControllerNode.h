#ifndef CONTROLLERNODE_H_
#define CONTROLLERNODE_H_

class ControllerNode{
    private:
        int diskSize = 1; 
        int numberSector = 1; 

    public: 
        ControllerNode();
        int getDiskSize(){
            return this->diskSize; 
        } 
        int getNumberSector(){
            return this->numberSector; 
        }
        void run(); 
};

#endif /* CONTROLLERNODE_H_*/