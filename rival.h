#ifndef RIVAL_H_INCLUDED
#define RIVAL_H_INCLUDED
#include "character.h"


class Rival {
private:
    int position_x;
    int position_y;
    int strength = 3;
    int alive = 1;

public:
    Rival();
    Rival(int large);
    int getposition_x();
    int getposition_y();
    int getalive();
    void check_character(Character& character, int level);
    void move_rival(Character& character, int num_rival);
};

#endif // RIVAL_H_INCLUDED
