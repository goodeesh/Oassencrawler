#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>



class Character {
private:
    int lives;
    int relics_found = 0;
    int position_x = 0;
    int position_y = 0;
    int movements = 0;
    int damage_taken = 0;
    int damage_recovered = 0;
    int strength = 0;
    int agility = 0;
    int vigor = 0;
    int skill_points = 6;
    int max_lives = 5;

public:
    Character(int lives);
    void assign_skill_points();
    void input_stat(std::string stat);
    int get_max_lives();
    int get_strength();
    int getagility();
    int getlives();
    int getMovements();
    int getDamageTaken();
    int getDamageRecovered();
    int getrelics_found();
    int getposition_x();
    int getposition_y();
    void movechar(int large);
    void increaseLifePoints();
    void increaseRelicPoints();
    void increaseDamageTaken();
    void loseLife();
    void increaseLifeRestored();
    void dead();
    int input_strength();
    int input_vigor();
    int input_agility();
    void NewLevel();

};

#endif
