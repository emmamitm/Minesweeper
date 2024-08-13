//
// Created by Emma Mitchell on 4/11/22.
//
 //class for tiles and spaces
#ifndef MINESWEEPER_TILES_H
#define MINESWEEPER_TILES_H
#include "vector"
#include "string"
#include "TextureManager.h"

using namespace std;
class tiles{
public:
    bool hasMine = false;
    int num=1; //the tile that will be displayed in the output image window (1=default)
    int mineCount=0;
    bool hasFlag = false;
    bool rev = false; //whether or not the revealed tile should sho
    int adjacentTiles=0;
    int adjacentMines=0;
    vector<tiles*> adjacentT;
    sf:: Sprite hidden;
    sf:: Sprite revealed;
    sf:: Sprite number;
    sf:: Sprite mine;
    sf:: Sprite flag;
    void createTile();
    sf::Texture thidden;
    sf::Texture trevealed;
    sf::Texture tnumber;
    sf::Texture tmine;
    sf::Texture tflag;
    int xpos; //x coordinate
    int ypos; //y coordinate

    void addFlag();
    void addNumber();
    void addMine();
    void clearT();

};


void tiles:: createTile(){
    hidden.setTexture(thidden);
    hidden.setPosition(xpos*32, ypos*32);
    revealed.setTexture(trevealed);
    revealed.setPosition(xpos*32, ypos*32);
}
void tiles:: addFlag(){
    hasFlag = true;
    flag.setTexture(tflag);
    flag.setPosition(xpos*32, ypos*32);
}
void tiles::addNumber() {
    number.setTexture(tnumber);
    number.setPosition(xpos*32, ypos*32);
}
void tiles::addMine() {
    mine.setTexture(tmine);
    mine.setPosition(xpos*32, ypos*32);
}
void tiles :: clearT(){
    hasMine = false;
    mineCount=0;
    hasFlag = false;
    rev = false; //whether or not the revealed tile should show
    adjacentTiles=0;
    adjacentMines=0;
    adjacentT.clear();
    num=1;
}
#endif //MINESWEEPER_TILES_H
