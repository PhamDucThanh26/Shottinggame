#ifndef COLLISION_H
#define COLLISION_H

void collision(vector <sf::RectangleShape> &enemies, vector <sf::CircleShape> &projectiles, sf::RectangleShape &player, bool &lose, int &score){
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
            lose = true;
            break;
        }
    }

    for (int i = 0; i < enemies.size() && lose == false; i++) {
        for (int j = 0; j < projectiles.size(); j++) {
            if (enemies[i].getGlobalBounds().intersects(projectiles[j].getGlobalBounds())) {
                score++;
                enemies.erase(enemies.begin() + i);
                projectiles.erase(projectiles.begin() + j);
                break;
            }
        }
    }
}
#endif // SET_H
