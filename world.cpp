#include <iostream>
#include <time.h>
#include "world.h"
using std::cout;
using std::endl;
//lets use enums to see the type of tile
enum TileType {
    Empty = 0,
    Danger = 1,
    Recovery = 2,
    Relic = 3,
    Visited = 4
};


//i have assigned the arr through vector library, to be able to create bigger array without having to set a size in my code
World::World(int grosse)
{
    arr = std::vector<std::vector<int>>(grosse, std::vector<int>(grosse, 0));
    this->relics = relics;
    this->large = grosse;
}
//here we create the world, depending on the size of our array

void World::create()
{
    int random;
    arr.resize(this->large);  // Resize the vector to hold 'this->large' number of rows
    for (int i = 0; i < this->large; i++)
    {
        arr[i].resize(this->large);  // Resize each row to hold 'this->large' number of columns
        for (int j = 0; j < this->large; j++)
        {
            random = rand() % 10 + 1;
            if (random < 5)
            {
                arr[i][j] = TileType::Empty;
            }
            else if (random < 9)
            {
                arr[i][j] = TileType::Danger;
            }
            else if (random < 10)
            {
                arr[i][j] = TileType::Recovery;
            }
            else
            {
                arr[i][j] = TileType::Relic;
                this->relics++;
            }
            //making sure there is at least one relic
            if (i == this->large-1 && j == this->large-1 && this->relics == 0)
            {
                arr[i][j] = TileType::Relic;
                this->relics++;
            }
        }
    }
    arr[0][0] = TileType::Visited; // it does not make sense to don't start on a visited tile
    this->relics_beggining = this->relics;
}
//here we check if there are still relics and/or lives, if one of both is true, the game should be over
bool World::getisGameOver(Character& character)
{
    if (this->relics == 0 || character.getlives() < 1) {
        this->isGameOver = true;
    }
    return this->isGameOver;
}
//printing statistics of the game
void World::print_Statistics(Character& character)
{
    if (character.getlives() == 0 && this->isGameOver== true) { //this one we print only if we don't have more lives at the end
        cout << "GAME OVER" << endl;
    }
    cout <<"_________ Statistics _________" <<endl;
    cout << "You took " << character.getDamageTaken() << " damage points" << endl;
    cout << "You recovered " << character.getDamageRecovered() <<  " damage points" << endl;
    cout << "You did " << character.getMovements() << " movements in this match" << endl;
    cout << "You recovered " << character.getrelics_found() << " relics this match"<< endl;
    }

//here we check what effect had the tile on the character
void World::action(Character& character)
{
    srand(time(0)); // initialize random seed
    int random;
    // i assign this values to variables for readability
    int positionY = character.getposition_y();
    int positionX= character.getposition_x();
    int level = this->level;
    if(this->arr[positionY][positionX] == TileType::Relic)
    {
        this->arr[positionY][positionX] = TileType::Visited;
        this->relics--;
        character.increaseRelicPoints();
        if(this->relics == 0)
        {
            cout << "Congratulations! You found all the relics! You have beaten the level :)"<< endl;
            return;
        }
        else cout << "You found a relic! You are one step closer to beating this level."<< endl;
    }
    else if (this->arr[positionY][positionX] == TileType::Recovery)
    {
        this->arr[positionY][positionX] = TileType::Visited;
        if (character.getlives() == character.get_max_lives()){ // if the character has more vigor, he will be able to store more health points
            cout << "You found a safe place to rest! You health is already capped out though." << endl;
        } else {
            character.increaseLifePoints();
            character.increaseLifeRestored();
            cout << "You found a safe place to rest! You gained one point of health." << endl;
        }

    }
    else if (this->arr[positionY][positionX] == TileType::Danger)
    {
        this->arr[positionY][positionX] = TileType::Visited;
        random  = rand() % 10 + 1;
        int probability = 6 - character.getagility(); // here is when agility comes in handy, reducing the probability of taking damage in danger tiles
        if(random < probability)
        {
            for (int i = 0; i<level; i++){
                character.loseLife();
                character.increaseDamageTaken();
            }

            cout << "As you move to your next destination, you activate a trap... You lose "<< this->level << " point of health." << endl;
            //cout << "As you move to your next destination, you activate a trap... You lose one point of health." << endl;

        }
        else cout << "As you move to your next destination, you activate a trap... but you manage to avoid it at the last second." << endl;
        cout << "You deactivate the trap, this should not happen again." << endl;
    }
    else
    {
        this->arr[positionY][positionX] = TileType::Visited;
        cout << "As you move to your next destination, you found nothing." << endl;
    }
}

//in case we need the cheat_sheet, i let the function prepared
void World::print_cheatsheet()
{
    for (int i = 0; i<this->large; i++)
    {
        for (int j = 0; j<this->large; j++)
        {
            cout << this->arr[i][j] << " ";
        }
        cout << endl;
    }
}

void World::print_field(Character& character, Rival rivals[], int num_rivals)
{
    int character_x = character.getposition_x();
    int character_y = character.getposition_y();
    int lives = character.getlives();
    int relics_found = character.getrelics_found();
    char heart = 3;
    cout << endl;
    cout << "Health: ";
    for (int i = 0; i < lives; i++) cout << heart << " ";
    cout << endl;
    cout << "Relics: " << relics_found;
    cout << "   Level: " << this->level;
    cout << endl << endl;
    for (int i = 0; i < this->large; i++)
    {
        for (int j = 0; j < this->large; j++)
        {
            bool printed = false;
            int enemy_count = 0; //initialize a variable to count enemies on each tile
            if (j == character_x && i == character_y) //print out where our player is
            {
                cout << "[*]" << " ";
                printed = true;
            }
            for (int k = 0; k < num_rivals; k++) //count the number of rivals on each tile, if they are alive
            {
                int rival_x = rivals[k].getposition_x();
                int rival_y = rivals[k].getposition_y();
                int rival_alive = rivals[k].getalive();
                if (j == rival_x && i == rival_y && rival_alive == 1)
                {
                    enemy_count++; //increment the enemy count
                }
            }
            if (enemy_count > 0) //print the number of enemies on each tile
            {
                cout << "[" << enemy_count << "]" << " ";
                printed = true;
            }
            if (!printed&&arr[i][j]== TileType::Visited) cout << "[ ]" << " "; //if no rivals or character, print empty tile
            else if (!printed) cout << "[_]" << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Your character is represented by this: *" << endl;
    cout << "Monster/s are represented by numbers, depending on the quantity." << endl;
    cout << "A non-visited tile is represented by [_], while a visited one will be [ ]." << endl;
    cout << endl;
}
// this are just some getters from the different stats in the world
int World::getRelics()
{
    return this->relics;
}
int World::getLarge()
{
    return this->large;
}
int World::getRelics_beggining()
{
    return this->relics_beggining;
}
int World::getLevel()
{
    return this->level;
}
void World::increaseLevel()
{
    this->level++;
}
//world bigger, relics restart, game is not over... and create a new world
void World::NewWorld()
{
    this->large++;
    this-> relics = 0;
    this-> relics_beggining = 0;
    this->level++;
    this->isGameOver = false;
    create();
}



