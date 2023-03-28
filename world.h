#ifndef WORLD_H
#define WORLD_H
#include "character.h"
#include "rival.h"
#include <vector>


class World
{
public:
    World(int grosse);
    void create();
    void print_field(Character& character, Rival rivals[], int num_rivals);
    void print_cheatsheet();
    int getRelics();
    int getRelics_beggining();
    void action(Character& character);
    void set_isGameOver(Character& character);
    bool getisGameOver(Character& character);
    int getLarge();
    void print_Statistics(Character& character);
    int getLevel();
    void increaseLevel();
    void NewWorld();

private:
    std::vector<std::vector<int>> arr;
    int relics = 0;
    int relics_beggining = 0;
    int large;
    int level = 1;
    bool isGameOver = false;
};

#endif // WORLD_H
