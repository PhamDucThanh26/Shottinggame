#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;

class Menu{

public:
    Menu(float w, float h);
    ~Menu();
    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem(){return MainMenuSelected;}

private:
    int MainMenuSelected;
    Font font, font2;
    Text mainMenu[3];
};
