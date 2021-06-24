
#ifndef PROYECTO2_TEXTBOX_H
#define PROYECTO2_TEXTBOX_H
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox{
public:
    Textbox(){

    }
    Textbox(int size,Color color,bool sel){
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        isSelected = sel;
        if(sel){
            textbox.setString("_");
        }
        else{
            textbox.setString("");
        }
    }

    void setfont(Font &font){
        textbox.setFont(font);
    }

    void setPosition(Vector2f pos){
        textbox.setPosition(pos);
    }

    void setLimit(bool TOF, int lim){
        haslimit = TOF;
        limit = lim-1;
    }

    void setSelected(bool sel){
        isSelected = sel;

        if(!sel){
            string t = text.str();
            string newt = "";
            for(int i = 0; i < t.length();i++){
                newt += t[i];
            }
            textbox.setString(newt);
        }
        else{
            textbox.setString(text.str()+"_");
        }
    }

    bool getSelected(){
        return isSelected;
    }

    string getText(){
        if(reinterpret_cast<const char *>(text.str()[-1]) == "_"){
            deleteLastChar();
        }
        return text.str();
    }

    void drawTo(RenderWindow &window){
        window.draw(textbox);
    }

    void typedOn(Event input){
       if(isSelected){
           int chartyped = input.text.unicode;
           if(chartyped < 128){
               if(haslimit){
                   if(text.str().length() <= limit){
                       inputLogic(chartyped);
                   }
                   else if (text.str().length() > limit && chartyped == DELETE_KEY){
                       deleteLastChar();
                   }
               }
               else{
                   inputLogic(chartyped);
               }
           }
       }
    }

private:
    Text textbox;
    ostringstream text;
    bool isSelected = false;
    bool haslimit = false;
    int limit;

    void inputLogic(int charTyped){
        if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY){
            text << static_cast<char>(charTyped);
        }
        else if (charTyped == DELETE_KEY){
            if(text.str().length() > 0){
                deleteLastChar();
            }
        }
        textbox.setString(text.str()+"_");
    }

    void deleteLastChar(){
        string t = text.str();
        string newt = "";
        for(int i = 0; i < t.length()-1;i++){
            newt += t[i];
        }
        text.str("");
        text << newt;
        textbox.setString(text.str());
    }

};


#endif //PROYECTO2_TEXTBOX_H
