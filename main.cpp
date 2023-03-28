#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include "world.h"
#include "character.h"
#include "rival.h"


void print_readme(){
    std::ifstream inFile;
    inFile.open("readme.txt");
    if (!inFile.is_open()) {
    std::cerr << "Unable to open file.\n";
    exit(1);
    }
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
}
void play_game(World& world, Character& character)
{
    int level = world.getLevel();
    int numberOfRivals = level;
    Rival rivals[level]; // array to store Rival objects
    for (int i = 0; i < level; i++) { // more rivals every new level
        rivals[i] = Rival(world.getLarge()-1); // create a new Rival object with the world large size
    }
    while (world.getisGameOver(character)!= true)
    {
        world.print_field(character, rivals, numberOfRivals);
        character.movechar(world.getLarge());
        for (int i = 0; i < level; i++) { // we need to check if any of the monsters is currently in the player position
            rivals[i].check_character(character, level);
        }
        if (world.getisGameOver(character) == true) break; // afterwards we check we have lives left
        world.action(character); //we check the action the tile has on the player
        if (world.getisGameOver(character) == true) break; // and again check if lives/relics are gone
        for (int i = 0; i < level; i++) { //we need to move each monster and check again if character is there
            rivals[i].move_rival(character, i);
            rivals[i].check_character(character, level);
        }
    }
}
int main()
{
    srand ( time(0) );
    print_readme(); //some instructions of how the game works
    Character character(5); //lives the characters has per default
    character.assign_skill_points(); // this function lets us chose how do we want to divide the skill points
    int large = 5; //large at the beggining
    World world(large);
    Rival rival(world.getLarge()-1);
    world.create(); // generate the world
    // game loop
    int boolean = 1;
    while (boolean == 1){ // i use boolean to see the if the player wants to try a new level
        play_game(world, character);
        if(world.getisGameOver(character) == 0 && world.getRelics()>0) {
            std::cout << "GAME OVER" << std::endl;
            boolean = 0;
            continue;
        }
        std::string input;
        if (character.getlives() < 1) {
                boolean = 0;
                continue;
                }
        std::cout << "Congrats! You have beaten this level, do you want to try one harder?" << std::endl;
        std::cout << "Press (y) for yes or (n) for exiting the game" <<std::endl;
        std::cin >> input;
        if (input.length()>1)
        {
            std::cout << "That is not a valid input" << std::endl;
            continue;
        }
        char decision = input[0];
        if (decision != 'y' && decision != 'n') std::cout << "That is not a valid input" << std::endl;
        if (decision == 'y') {
            character.NewLevel();
            world.NewWorld();
            play_game(world, character);
        }
        if (decision == 'n') boolean = 0;
    }
    //statistics and final gameover printen
    world.print_Statistics(character);
    return 0;
}
