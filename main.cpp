#include<iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "Menu.h"
#include "collision.h"
#include "game.h"
#include <SFML/Audio.hpp>
using namespace std;

int main() {
    //MUSIC
    sf::Music music;
    if (!music.openFromFile("Res/Viet-Nam-Oi-Minh-Beta.wav"));
    music.play();
	//WINDOW
	sf::RenderWindow game(sf::VideoMode(800, 600), "Game");
    Menu menu(game.getSize().x, game.getSize().y);
    Texture text;
    text.loadFromFile("Res/background.jpg");
    Sprite s(text);
	while(game.isOpen()){
        Event event;
        while (game.pollEvent(event)){
            if (event.type == Event::Closed)
                game.close();
            if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::Up)
                    menu.MoveUp();
                if (event.key.code == Keyboard::Down)
                    menu.MoveDown();
                if (event.key.code == Keyboard::Escape)
                    game.close();
                if (event.key.code == Keyboard::Return){
                    int x = menu.GetPressedItem();
                    if (x == 0){
                         music.play();
                        play();
                    }
                }
            }
        }
        game.draw(s);
        menu.draw(game);
        game.display();
    }
}
