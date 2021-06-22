#ifndef DISKNODE_H_
#define DISKNODE_H_ 

class DiskNode{ 
    private: 
        int size;
        int sectorSize;
    public: 
        DiskNode();
        void setSize(int size){
            this->size = size; 
        }
        void setSectorSize(int sectorSize){
            this->sectorSize = sectorSize;
        }
};


#endif /* DISKNODE_H_*/