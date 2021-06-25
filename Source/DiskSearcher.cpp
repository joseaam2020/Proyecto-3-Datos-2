
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
            if(end != "." &&  end != ".."){//revisar que no sea . o ..
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

                            cout<<"substring is present at line "<<line<<endl;
                            libros.push_back(files.at(a));
                            ans=true;     // if substring present make ans variable true.
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
    Bnames.clear();
    vector<string> sectors;
    for(int i = 0;i < paths.size();i++){
        string s = paths.at(i);
        int start = 0;
        int end = s.find(del);
        while (end != -1) {
            sectors.push_back(s.substr(start, end - start));
            start = end + del.size();
            end = s.find(del, start);
        }
        sectors.push_back(s.substr(start, end - start));
        vector<string> temp = {sectors.at(sectors.size()-2),sectors.at(sectors.size()-1)};
        Bnames.push_back(temp);
    }
    for(int a = 0;a<Bnames.size();a++){
        cout<<Bnames.at(a).at(0) <<" | "<<Bnames.at(a).at(1)<<endl;
    }

    book_to_meta();
}

void DiskSearcher::book_to_meta() {
    vector<vector<string>> locations;
    for(int i = 0;i < Bnames.size();i++){
        vector<string> tmp;
        string dn(1,Bnames.at(i).at(0)[Bnames.at(i).at(0).size()-1]);
        tmp.push_back(dn);
        string sn(1,Bnames.at(i).at(1)[Bnames.at(i).at(1).size()-5]);
        tmp.push_back(sn);
        locations.push_back(tmp);
    }

    for(int a = 0; a <locations.size();a++){
        cout<<"disk num: "<<locations.at(a).at(0)<<" | "<<"Book num: "<<locations.at(a).at(1)<<endl;
    }
    for(int f = 0; f < locations.size();f++){
        /*
    string line;
    ifstream myfile ("example.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
        }
        myfile.close();
    }

    else cout << "Unable to open file";
    */
    }

}

int main(){
    DiskSearcher dk = DiskSearcher();
    string path = "/home/david/Documents/proyecto#3/Proyecto-3-Datos-2/Disk prueba1";
    string path2 = "/home/david/Documents/proyecto#3/Proyecto-3-Datos-2/Disk prueba2";
    vector<string> paths;
    paths.push_back(path);
    paths.push_back(path2);
    dk.insertdiskpath(paths);
    dk.find("estas");
    for(int a = 0;a<dk.libros.size();a++){
        cout<<dk.libros.at(a)<<endl;
    }

    dk.getBookNames(dk.libros,"/");




    return 0;
}