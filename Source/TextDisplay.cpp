//
// Created by david on 25/6/21.
//

#include "TextDisplay.h"

#include <utility>

TextDisplay::TextDisplay(const string& titles, string txts) {

    this->keepOpen = true;

    //WINDOW
    this->width = 900;
    this->height = 700;
    this->window = new RenderWindow(VideoMode(width, height), "ceSEARCH");


    //BACKGROUND
    this->background.setSize(Vector2f(width, height));
    this->background.setFillColor(Color::White);
    this->background.setPosition(0, 0);

    if(!font.loadFromFile("fonts/arial.ttf")){
        cout << "Could not load font" << endl;
    }

    texto.setFont(font);
    txt = txts;
    texto.setString(txt);
    texto.setCharacterSize(20);
    texto.setFillColor(Color::Black);
    texto.setPosition(10,60);

    title.setFont(font);
    title.setString(titles);
    title.setCharacterSize(40);
    title.setFillColor(Color::Black);
    title.setPosition(10,5);
}
void TextDisplay::render() {
    //main window
    this->window->draw(this->background);
    window->draw(texto);
    window->draw(title);
}

void TextDisplay::run() {
    while (this->keepOpen) {

        Event event;
        while (this->window->pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    this->window->close();
                    this->keepOpen = false;
                    break;

            }
        }

        //clear
        this->window->clear(Color::White);
        //update mouse pos

        //dibujar UI
        render();
        //mostrar UI
        this->window->display();
    }
}

