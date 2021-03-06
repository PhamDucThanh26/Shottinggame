#include "SFML/Graphics.hpp"
#include<iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "collision.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#ifndef GAME_H
#define GAME_H
void play(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First Game");
    window.setFramerateLimit(60);
    //Player Texture
    sf::Texture playerTex;
    if (!playerTex.loadFromFile("Res/playerTex.png"));
    playerTex.setSmooth(true);

    // Projectile Texture
    sf::Texture projectileTex;
    if (!projectileTex.loadFromFile("Res/projectileTex.png"));
    projectileTex.setSmooth(true);

    // Enemy texture

    sf::Texture enemyTex;
    if (!enemyTex.loadFromFile("Res/enemyTex.png"));
    enemyTex.setSmooth(true);

    // loosing Screen texture;
    sf::Image Screenshot;//Image to store the screenshot
    sf::Texture losing;
    losing.create(window.getSize().x, window.getSize().y);

    //PLAYER
    sf::RectangleShape player(sf::Vector2f(80.f, 80.f));
    player.setOrigin(player.getSize() / 2.f);
    player.setPosition(window.getSize().x / 2.f, window.getSize().y - 50.f);
    player.setTexture(&playerTex);
    player.setFillColor(sf::Color(0, 0, 255, 100));

    //PROJECTILE
    sf::CircleShape projectile(10.f);
    projectile.setOrigin(projectile.getOrigin().x + 10.f, projectile.getOrigin().y + 10.f);
    projectile.setTexture(&projectileTex);
    //projectile.setFillColor(sf::Color::Red);
    vector <sf::CircleShape> projectiles;
    projectiles.push_back(sf::CircleShape(projectile));

    //ENEMY
    sf::RectangleShape enemy(sf::Vector2f(60.f, 60.f));
    enemy.setOrigin(enemy.getSize() / 2.f);
    enemy.setTexture(&enemyTex);
    //enemy.setFillColor(sf::Color::Blue);
    vector <sf::RectangleShape> enemies;

    //LOOSING
    sf::RectangleShape loosing(sf::Vector2f(800, 600));
    loosing.setOrigin(loosing.getSize() / 2.f);
    loosing.setTexture(&losing);
    loosing.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    //TEXT
    sf::Text scoreOnScreen;
    scoreOnScreen.setPosition(window.getSize().x / 2.f - 120, 3.f);
    scoreOnScreen.setCharacterSize(30);
    scoreOnScreen.setFillColor(sf::Color::Black);
    sf::Font gotham;
    if (!gotham.loadFromFile("Res/Gotham-Bold.otf"));
    scoreOnScreen.setFont(gotham);

    sf::Vector2f mousePos;
    sf::Vector2f enemyCenter;
    sf::Vector2f aimDir;
    sf::Vector2f aimNormal;
    sf::Vector2f velocity;

    long double deltatime = 0; //for finding duration of clock
    double shot = 0;		//time counter for shooting
    double rain = 0;		//time counter for raining
    double chaser = 0;
    double shotspeed = 0.09;		//time limit for shooting
    double rainSpeed = 0.15;		//time limit for raining
    double chaserSpeed = 1;		//time limit for chaser ghosts
    double speed = 0;
    int score = 0;
    srand(time(NULL));

    bool lose = false;
    bool pause = false;
    sf::Clock clock;
    while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::LostFocus)
                    pause = true;
                if (event.type == sf::Event::GainedFocus)
                    pause = false;
            } // event loop


            deltatime = clock.restart().asSeconds();

            if (score <= 50) speed = 8 * deltatime * 56.2;		//speed of falling ghosts


            // If Loosing Screen or pause
            if (lose || pause) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {	//Reset the game

                    shotspeed = 0.09;	//time limit for shooting
                    rainSpeed = 0.15;	//time limit for raining
                    chaserSpeed = 1;		//time limit for chaser ghosts
                    speed = 8 * deltatime * 56.2;		//speed of falling ghosts
                    shot = 0; rain = 0; lose = false;
                    score = 0;
                    enemies.clear(); projectiles.clear();
                }

                // Clear the window
                window.clear(sf::Color::White);
                // Print message
                stringstream message;
                message << "    SCORE: " << score;
                lose ? message << "\n     PRESS R\nTO GO AGAIN! " : message << "  \nPAUSED";
                scoreOnScreen.setString(message.str());
                //Opacity decrease
                loosing.setFillColor(sf::Color(255, 255, 255, 40.f));
                //draw all
                window.draw(loosing);
                window.draw(scoreOnScreen);
                window.display();
                // continue the loop, do not go in game;
                continue;
            }

            //======== INCREMENTING LIMITS ======================================================================

            if (shot < shotspeed) shot += deltatime;
            if (rain < rainSpeed) rain += deltatime;
            if (chaser < chaserSpeed) chaser += deltatime;

            //===================================================================================================

            //======== INCREASING DIFFICULTY ====================================================================

            // Increase enemies every 40 points
            if (score % 50 == 40) {
                speed += 0.1 * deltatime * 56.2;
                if (rainSpeed > 0.03) rainSpeed -= 0.0005;

            }
            //// decrease projectiles
            if (score % 100 == 40) {
                if (shotspeed < 0.2) shotspeed += 0.005;
            }

            //=====================================================================================================

            //UPDATE



            //UPDATE PLAYER

            mousePos = player.getPosition();
            player.setPosition(sf::Mouse::getPosition(window).x, window.getSize().y - 50.f);

            if (player.getPosition().x > window.getSize().x - 40) {
                player.setPosition(window.getSize().x - 40, player.getPosition().y);
            }

            if (sf::Mouse::getPosition(window).x < 40) {
                player.setPosition(40, player.getPosition().y);
            }

            //================================================================================

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shot > shotspeed) {
                projectile.setPosition(player.getPosition());
                projectiles.push_back(sf::CircleShape(projectile));
                shot = 0;

            }


            // UPDATE ENEMIES

            // UPDATE PROJECTILES

            if (rain > rainSpeed) {

                if (chaser > chaserSpeed) {
                    enemy.setFillColor(sf::Color(255, 0, 0, 128));
                    chaser = 0;
                    enemy.setPosition(rand() % ((window.getSize().x)), 0);
                }

                else {
                    enemy.setFillColor(sf::Color(255, 255, 255, 255));
                    enemy.setPosition(rand() % ((window.getSize().x - 60)) + 30, 100);
                }

                enemies.push_back(enemy);
                rain = 0;
            }
            ;		for (int i = 0; i < enemies.size(); i++) {
                enemyCenter = enemies[i].getPosition();
                aimDir = mousePos - enemyCenter;
                aimNormal = aimDir / sqrt(aimDir.x * aimDir.x + aimDir.y * aimDir.y);
                //cout << i << endl;
                velocity.x = 0;

                if (enemies[i].getFillColor() == sf::Color(255, 0, 0, 128)) {
                    velocity.x = aimNormal.x * float(speed);
                    velocity.y = speed + 20 * deltatime * 56.2;


                }
                enemies[i].move(velocity.x, speed);

                if (enemies[i].getPosition().y >= player.getPosition().y - 10.f) {
                    enemies.erase(enemies.begin() + i);
                    score++;
                }
            }

            //cout << aimNormal.x << " " << aimNormal.y << endl;

            for (int i = 0; i < projectiles.size(); i++) {
                projectiles[i].move(0, -8.f * deltatime * 56.2);
                if (projectiles[i].getPosition().y < 40)
                    projectiles.erase(projectiles.begin() + i);
            }

            //cout << fixed << setprecision (10) << deltatime << endl;
            //COLLISION:
            collision(enemies, projectiles, player, lose, score);

            if (!lose) {
                window.clear(sf::Color::White);
                stringstream scoreMessage;
                scoreMessage << "    SCORE: " << score;
                scoreOnScreen.setString(scoreMessage.str());

                // Score draw
                window.draw(scoreOnScreen);

                // Player draw

                // Enemies draw:
                for (auto& x : enemies) {
                    window.draw(x);
                }

                // Projectile draw
                for (auto& x : projectiles) {
                    window.draw(x);
                }

                window.draw(player);

                // DISPLAY

                losing.update(window);
                window.display();
            }
        }
}
#endif // GAME_H
