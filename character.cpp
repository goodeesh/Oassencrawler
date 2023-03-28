#include "character.h"
#include <iostream>
#include "world.h"
#include <string>

//initiate our character, i let lives be chosen, in case of more difficulty at the beggining
Character::Character(int lives)
{
    this->lives = lives;
}
//this next two functions assign the skill points to our character at the beggining
void Character::assign_skill_points(){
    int aux = 0;
    std::string strength = "strength";
    std::string agility = "agility";
    std::string vigor = "vigor";
    while (aux<3){
        aux++;
        if (aux == 1) Character::input_stat(strength);
        if (aux == 2) Character::input_stat(agility);
        if (aux == 3) Character::input_stat(vigor);
    }
}
//depending on what i call the function with, i assign the points to the different categories
void Character::input_stat(std::string stat){
    int points = 0;
    std::string input;
    std::cout << "How many points do you want to assign to " << stat << "?" << std::endl;
    std::cout << "You currently have " << this->skill_points << " to assign." << std::endl;
    bool is_valid_input = false;
    do {
        std::cin >> input;
        try {
            points = std::stoi(input);
            if (points > this->skill_points || points < 0) {
                std::cout << "That is not a valid input. Try again." << std::endl;
            } else {
                is_valid_input = true;
            }
        } catch (const std::invalid_argument&) {
            std::cout << "That is not a valid input. Try again." << std::endl;
        }
    } while(!is_valid_input);
    this->skill_points = this->skill_points-points;
    if (stat == "strength") this->strength += points;
    if (stat == "agility") this->agility += points;
    if (stat == "vigor"){
        this->vigor += points;
        this->max_lives += points;
        this->lives= this->max_lives;
    }
}
//this is how i move my character in the map, large is important to know i don't go off-limits
void Character::movechar(int large)
{
    int boolean = 0; // we use boolean to control the loop, then check for different invalid inputs
    std::string input;
    char movement;
    while (boolean == 0)
    {
        std::cout << "Enter (w) to go up, (s) to go down, (d) to go right and (a) to go left." << std::endl;
        std::cin >> input;
        if (input.length()>1)
        {
            std::cout << "That is not a valid input" << std::endl;
            continue;
        }
        movement = input[0];

        if (this->position_y == 0 && movement == 'w')
        {
            std::cout << "That is not a valid movement" << std::endl;
            continue;
        }
        else if (this->position_y == large-1 && movement == 's')
        {
            std::cout << "That is not a valid movement" << std::endl;
            continue;
        }
        else if (this->position_x == 0 && movement == 'a')
        {
            std::cout << "That is not a valid movement" << std::endl;
            continue;
        }
        else if (this->position_x == large-1 && movement == 'd')
        {
            std::cout << "That is not a valid movement" << std::endl;
            continue;
        }
        else if (movement == 'w') this->position_y--;
        else if (movement == 's') this->position_y++;
        else if (movement == 'd') this->position_x++;
        else if (movement == 'a') this->position_x--;
        else
        {
            std::cout << "That is not a valid input" << std::endl;
            continue;
        }
        this->movements++;
        boolean = 1; // if everything worked i set the boolean to 1
    }
}
//this are just some getters from the different variables in character
int Character::getDamageTaken(){
    return this->damage_taken;
}
int Character::getDamageRecovered(){
    return this->damage_recovered;
}
int Character::getMovements(){
    return this->movements;
}
int Character::get_max_lives()
{
    return this->max_lives;
}
int Character::getlives()
{
    return this->lives;
}
int Character::getrelics_found()
{
    return this->relics_found;
}
int Character::getposition_x()
{
    return this->position_x;
}
int Character::getposition_y()
{
    return this->position_y;
}
int Character::getagility(){
    return this->agility;
}
int Character::get_strength(){
    return this->strength;
}
//the next functions modify stats and or statistics of the character
void Character::increaseLifePoints()
{
    this->lives++;
}
void Character::increaseLifeRestored()
{
    this->damage_recovered++;
}
void Character::increaseDamageTaken()
{
    this->damage_taken++;
}

void Character::loseLife()
{
    this->lives--;
}
void Character::increaseRelicPoints()
{
    this->relics_found++;
}
//new level so i give the character new skill points and reset position and lives
void Character::NewLevel()
{
    this->skill_points++;
    this->skill_points++;
    assign_skill_points();
    this->position_x = 0;
    this->position_y = 0;
    this->lives = this->max_lives;
}

