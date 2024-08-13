//
// Created by Emma Mitchell on 4/11/22.
//

#ifndef MINESWEEPER_RANDOM_H
#define MINESWEEPER_RANDOM_H
#include "random"



class Random {
    static std:: mt19937 random;
public:
    static int x;
    static int Number(int min, int max);
    static float Number2(float min, float max);
};

#endif //MINESWEEPER_RANDOM_H
