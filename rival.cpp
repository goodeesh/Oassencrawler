#ifndef RIVAL_CPP_INCLUDED
#define RIVAL_CPP_INCLUDED
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rival.h"
Rival::Rival() {}

Rival::Rival(int large){
    int random;
    random = rand() % large + 1;
    this->position_x = random;
    random = rand() % large + 1;
    this->position_y = random;
}
//movement of the rival, based on our actual position, he is trying to catch us
void Rival::move_rival(Character& character, int num_rival){
    if (this->alive == 0) return; //if this monster is already dead we don't move it
    int position_x = character.getposition_x();
    int position_y = character.getposition_y();
    srand (time(0));
    int random_aux;
    random_aux = rand() % 10 + 1;
    if (num_rival == 0){
      std::cout << "The monster/s move!" << std::endl;
    if (random_aux >7){
        std::cout << "But apparently he/they got stuck with something, so he/they won't move this turn." << std::endl;
        return;
    }
    }

    int difference_x = position_x - this->position_x;
    int difference_y = position_y - this->position_y;
    if (difference_x<0) difference_x*(-1);
    if (difference_y<0) difference_y*(-1);
    if (difference_x == difference_y){
        random_aux = rand() % 10 + 1;
        if (random_aux>5) {
            if(position_y < this->position_y) this->position_y--;
            else this->position_y++;
        }
        else {
            if(position_x<this->position_x) this->position_x--;
            else this->position_x++;
        }
    }
    else if (difference_x == 0){
            if(position_y<this->position_y) this->position_y--;
            else this->position_y++;
    }
    else if (difference_y == 0){
            if(position_x<this->position_x) this->position_x--;
            else this->position_x++;
    }
    else if(difference_x<difference_y){
            if(position_y<this->position_y) this->position_y--;
            else this->position_y++;
    }
    else{
            if(position_x<this->position_x) this->position_x--;
            else this->position_x++;
    }
}
//we check if the character and monster are on the same tile
void Rival::check_character(Character& character, int level){
    int character_x = character.getposition_x();
    int character_y = character.getposition_y();
    int rival_x = this->getposition_x();
    int rival_y = this->getposition_y();
    if (this->alive == 0) return; // if our monster is dead, we don't need to check anymore
    if (character_x == rival_x && character_y == rival_y){
    int difference_strength = character.get_strength() - this->strength - level;
    // here is when the strength comes in handy, reducing or neglecting the damage from the monster
    if (difference_strength >= 0){
        std::cout << "The monster got you but he is not a problem for you, you manage to defeat him and don't take any damage" << std::endl;
    } else
        {
            std::cout << "Your rival got you" << std::endl;
            int difference_positive = difference_strength * (-1);
            std::cout << "After fighting with him, you took " <<  difference_positive << " damage points" << std::endl;
            for (int i = 0; i<difference_positive; i++){
                character.loseLife();
            }
        }
    this->alive = 0;
    }
}
//this are just the getters
int Rival::getposition_x() {
    return this->position_x;
}

int Rival::getposition_y() {
    return this->position_y;
}
int Rival::getalive(){
    return this->alive;
}


#endif // RIVAL_CPP_INCLUDED
