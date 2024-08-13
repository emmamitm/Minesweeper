//
// Created by Emma Mitchell on 4/11/22.
//

#include "Random.h"
#include "ctime"

std::mt19937 Random::random(time(0));
int Random:: Number(int min, int max){
    std:: uniform_int_distribution<int> dis(min, max);
    return dis(random);
}
float Random:: Number2(float min, float max){
    std:: uniform_real_distribution<float> dis(min, max);
    return dis(random);
}


