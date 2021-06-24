

#ifndef PROYECTO2_BUTTON_H
#define PROYECTO2_BUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
using namespace sf;
using namespace std;

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button {
private:
    short unsigned buttonstate;

    RectangleShape shape;
    Font* font;
    Text text;

    Color idleColor;
    Color hoverColor;
    Color activeColor;


public:
    bool disabled;
    /**
     * Contructor de la clase
     * @param x posicion x
     * @param y posicion y
     * @param width ancho
     * @param height altura
     * @param font font
     * @param text texto
     * @param idleColor color idle
     * @param hoverColor color hover
     * @param activeColor color activo
     */
    Button(float x, float y, float width, float height, Font* font, string text,
           Color idleColor, Color hoverColor, Color activeColor);
    /**
     * Contructor de la clase
     * @param x posicion x
     * @param y posicion y
     * @param width ancho
     * @param height altura
     * @param font font
     * @param text texto
     * @param idleColor color idle
     * @param hoverColor color hover
     * @param activeColor color activo
     * @param size tamaño de letra
     */
    Button(float x, float y, float width, float height, Font* font, string text,Color idleColor, Color hoverColor, Color activeColor, int size);
    //functions
    /**
     * Dibuja el boton en pantalla
     * @param target pantalla
     */
    void render(RenderTarget* target);
    /**
     * Le hace update al boton si fue clicked
     * @param mousepos posicion del mouse
     */
    void update(const Vector2f mousepos);
    /**
     * Dice si el boton esta siendo presionado
     * @return boolean
     */
    const bool is_pressed()const;


};


#endif //PROYECTO2_BUTTON_H
