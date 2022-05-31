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
    Font font;
    if (!font.loadFromFile("Res/Gotham-Bold.otf")){
        std::cout << "Error";
    }
    Text t;
    t.setFont(font);
    t.setFillColor(Color::Blue);
    t.setString("use your mouse to move and \n left mouse to shot the enemy . ");
    t.setCharacterSize(30);
    t.setPosition(50, 100);
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
                        play();
                    }
                    if (x==1){
                        sf::RenderWindow howToPlay(sf::VideoMode(800, 600), "HTP");
                        while (howToPlay.isOpen()){
                            Event aevent;
                            while (howToPlay.pollEvent(aevent)){
                                if (aevent.type == Event::Closed)
                                    howToPlay.close();
                                if (aevent.type == Event::KeyPressed)
                                    if (aevent.key.code == Keyboard::Escape)
                                        howToPlay.close();
                            }
                            howToPlay.draw(s);
                            howToPlay.draw(t);
                            howToPlay.display();
                        }
                    }
                    if (x==2){
                        game.close();
                    }
                }
            }
        }
        game.draw(s);
        menu.draw(game);
        game.display();
    }
}
