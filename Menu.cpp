#include "Menu.h"

Menu::Menu(float w, float h){
    if (!font.loadFromFile("Res/Gotham-Bold.otf")){
        std::cout << "Error";
    }
    //Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::Red);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(30);
    mainMenu[0].setPosition(50, 100);

    //How to play
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::Blue);
    mainMenu[1].setString("How to play");
    mainMenu[1].setCharacterSize(30);
    mainMenu[1].setPosition(50, 300);

    //Exit
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::Blue);
    mainMenu[2].setString("Exit");
    mainMenu[2].setCharacterSize(30);
    mainMenu[2].setPosition(50, 500);

    MainMenuSelected=0;
}
Menu::~Menu(){
}
//Draw MainMenu
void Menu::draw(RenderWindow &window){
    for(int i=0; i<3; i++){
        window.draw(mainMenu[i]);
    }
}

void Menu::MoveUp(){
    if (MainMenuSelected -1 >= 0){
        mainMenu[MainMenuSelected].setColor(sf::Color::Blue);
        MainMenuSelected--;
        if (MainMenuSelected == -1) MainMenuSelected = 0;
        mainMenu[MainMenuSelected].setColor(sf::Color::Red);
    }
}

void Menu::MoveDown(){
    if (MainMenuSelected + 1 <= 3){
        mainMenu[MainMenuSelected].setColor(sf::Color::Blue);
        MainMenuSelected++;
        if (MainMenuSelected == 3) MainMenuSelected = 2;
        mainMenu[MainMenuSelected].setColor(sf::Color::Red);
    }
}

