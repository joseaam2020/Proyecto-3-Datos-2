
#include "DiskSearcher.h"

DiskSearcher::DiskSearcher() {

}

void DiskSearcher::insertdiskpath(vector<string> paths) {
    diskpaths = paths;
}

vector<string> DiskSearcher::extractbookpaths(string path) {
    vector<string> files;
    DIR *dr; //abrir file
    dr = ::opendir(path.c_str());
    struct dirent *en;
    if (dr) {
        while ((en = readdir(dr)) != NULL) {//ir por cada archivo
            cout<<en->d_name<<endl;
            string end = en->d_name;
            if(end != "." &&  end != ".." && end[end.size()-1] !='l'){//revisar que no sea . o ..
                files.push_back(path+ "/"+en->d_name);
            }
        }
        closedir(dr); //close all directory
    }

    for(int a = 0;a<files.size();a++){
        cout<<files.at(a)<<endl;
    }
    return files;
}


void DiskSearcher::find(string input) {
    libros.clear();
    string substring;   // declaring subtring variable.
    substring = input;     //taking subtring as input.
    int indexNum = 0; 
    for(int i = 0; i < diskpaths.size();i++){
        vector<string> files = extractbookpaths(diskpaths.at(i));

        for(int a = 0; a <files.size();a++){

            ifstream file_text (files.at(a));  // creating file_text object of ifstream type.

            string x;

            bool ans=false;   // declaring ans variable which will get information if substring present or not.

            int line=1;   // it will count line and give an answer on which line we get a substring.

            if (file_text.is_open())       //is_open open the text file.
            {
                while ( getline (file_text,x) )
                {
                    if (x.find(substring, 0) != string::npos) {
                        {
                            int indexInt = static_cast<int>(x.find(substring, 0));
                            std::cout << "Index cast: " << indexInt << "IN: " << indexNum << std::endl;
                            this->index[indexNum] = indexInt;
                            std::cout<<"substring is present at line "<<line<<endl;
                            libros.push_back(files.at(a));
                            ans=true;     // if substring present make ans variable true.
                            indexNum++;
                        }
                        line++;
                    }
                    file_text.close(); //to close text file.
                }
            }
            else
                cout << "Unable to open file";

            if(!ans)   // if subtring not present.
                cout<<"subtring not present is present"<<endl;
        }
    }
}

vector<string> DiskSearcher::split(string input, string del) {
    vector<string> stringSP;
    string s = input;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        stringSP.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    stringSP.push_back(s.substr(start, end - start));
    return stringSP;
}

void DiskSearcher::getBookNames(vector<string> paths,string del) {
    cout<<"------------------------------------------"<<endl;
    cout<<"get book names"<<endl;
    Bnames.clear();


    for(int i = 0;i < paths.size();i++){
        vector<string> sectors;
        string s = paths.at(i);
        int start = 0;
        int end = s.find(del);
        string diskp = "";
        while (end != -1) {
            diskp +=s.substr(start, end - start)+"/";
            start = end + del.size();
            end = s.find(del, start);
        }
        sectors.push_back(diskp);
        sectors.push_back(s.substr(start, end - start));
        vector<string> temp = {sectors.at(0),sectors.at(1)};
        Bnames.push_back(temp);
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"print Bnames"<<endl;
    for(int a = 0;a<Bnames.size();a++){
        cout<<Bnames.at(a).at(0) <<" | "<<Bnames.at(a).at(1)<<endl;
    }

    book_to_meta();
}

void DiskSearcher::book_to_meta() {
    vector<vector<string>> locations;

    for(int i = 0;i < Bnames.size();i++){
        vector<string> tmp;
        string sn(1,Bnames.at(i).at(1)[Bnames.at(i).at(1).size()-5]);
        tmp.push_back(Bnames.at(i).at(0));
        tmp.push_back(sn);
        locations.push_back(tmp);
    }

    for(int a = 0; a <locations.size();a++){
        cout<<"disk loc: "<<locations.at(a).at(0)<<" | "<<"Book num: "<<locations.at(a).at(1)<<endl;
    }

    for(int f = 0; f < locations.size();f++){
        string line;
        string path = locations.at(f).at(0);
        cout<<"disk index: "<<path<<endl;
        string Lindex = locations.at(f).at(1);//numero de libro
        cout<<"book index: "<<Lindex<<endl;

        ifstream myfile (path+"Meta"+Lindex+".txt");
        cout<<path+"Meta"+Lindex+".txt"<<endl;
        if (myfile.is_open())
        {
            getline (myfile,line);
            vector<string> splitVector = split(line,"#");
            for(int file = 0; file < splitVector.size()-1; file+=3){
                int initialPosition = std::stoi(splitVector.at(file+2));
                int finalPosition = initialPosition + std::stoi(splitVector.at(file+1));
                std::cout << splitVector.at(file) << " I: " << initialPosition << "F: " << finalPosition << "S: " << splitVector.size() << std::endl; 
                if(finalPosition < index[f]){
                    continue;
                } else if(initialPosition <= index[f]){
                    metaD.push_back(splitVector.at(file));
                    break;
                } else{
                    continue;
                }
            }
            
            myfile.close();
        }

        else cout << "Unable to open file"<<endl;
    }
    for(int h = 0 ; h < metaD.size();h++){
        cout<<metaD.at(h)<<endl;
    }

}

/*
int main(){

    DiskSearcher dk = DiskSearcher();
    string path = "/home/david/Documents/proyecto#3/Proyecto-3-Datos-2/Disk prueba1";
    string path2 = "/home/david/Documents/proyecto#3/Proyecto-3-Datos-2/Disk prueba2";
    vector<string> paths;
    paths.push_back(path);
    paths.push_back(path2);
    dk.insertdiskpath(paths);
    dk.find("hola");
    cout<<"------------------------------------"<<endl;
    cout<<"Print libros"<<endl;
    for(int a = 0;a<dk.libros.size();a++){
        cout<<dk.libros.at(a)<<endl;
    }
    dk.getBookNames(dk.libros,"/");



    return 0;
}
*/