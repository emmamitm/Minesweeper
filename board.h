//
// Created by Emma Mitchell on 4/11/22.
//

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
#include "vector"
#include "string"
#include "tiles.h"
#include "Random.h"
#include "Random.cpp"
#include "tiles.h"
#include "array"
#include "fstream"
#include "ostream"
#include "sstream"



using namespace std;
class board{
public:
    int width;
    int height;
    int numOfMines;
    int randMines=0;
    int tileCount;
    int changedMines =0;
    int tilesRevealed =0;
    vector<tiles> tilesT;
    bool gameOver = false;
    bool won= false;
    int minesOnBoard=0;
    int faceNum=1;
    sf::Texture digits;
    sf::Texture digits2;
    sf::Texture digits3;
    sf::Texture digitssign;
    sf::Texture faceWin;
    sf::Texture faceLose;
    sf::Texture faceHappy;
    sf::Texture test1;
    sf::Texture test2;
    sf::Texture test3;
    sf::Texture debug;
    sf:: Sprite digitsSprite;
    sf:: Sprite faceSpriteHappy;
    sf:: Sprite test1Sprite;
    sf:: Sprite test2Sprite;
    sf:: Sprite test3Sprite;
    sf:: Sprite debugSprite;
    void createSprites();
    void lost();
    void victory();
    void clearB();
    void digitsReturn(int num);
    void digitTextures(map<int,sf::IntRect> *myrect, int num);
    void printDigits(sf::RenderWindow *window, int num);
    void loadTest(string filename);
    void tileArr();
    void getRandomMines();
    void changeTilesToAdjacentMines();
};
void board::createSprites() {
    //digitsSprite.setTexture(digits);
    //digits.loadFromFile()
    digitsSprite.setPosition(0, (height-1)*32+67);
    faceSpriteHappy.setTexture(faceHappy);
    faceSpriteHappy.setPosition(width/2*32, (height-1)*32+(50));
    test1Sprite.setTexture(test1);
    test1Sprite.setPosition(width*3/4*32 -64, (height-1)*32+(50));
    test2Sprite.setTexture(test2);
    test2Sprite.setPosition(width*3/4*32 , (height-1)*32+(50));
    test3Sprite.setTexture(test3);
    test3Sprite.setPosition(width*3/4*32+64, (height-1)*32+(50));
    debugSprite.setTexture(debug);
    debugSprite.setPosition(width*3/4*32+128, (height-1)*32+(50));
}
void board:: digitsReturn(int num){
    sf::IntRect myrect;
    map<int, sf::IntRect> myV;
    const int digitsnum =10;
    myV.emplace(-10,sf::IntRect(211,0,21,31));
    for (int i = 0; i < digitsnum; ++i) {
        myV.emplace(i,sf::IntRect(i*21,0,21,31));
    }
    digitTextures(&myV,num);

}
void board:: digitTextures(map<int,sf::IntRect> *myrect, int num){
    string im = "images/";
    string d = "digits.png";
    int val = abs(numOfMines - num);
    if ((numOfMines-num)<0){
        digits.loadFromFile(im+d,myrect->at(-10));
    }
    else if ( ((numOfMines-num)>0)){
        digits.loadFromFile(im+d,myrect->at((val/100)%10));
    } //do no matter what
    digits2.loadFromFile(im+d,myrect->at((val/10)%10));
    digits3.loadFromFile(im+d,myrect->at((val/1)%10));



}
void board :: printDigits(sf::RenderWindow *window, int num){
    sf::Sprite s;
    int val =numOfMines-num;
    if (val < 0){
        s.setTexture(digits);
        s.setPosition(0,(height-1)*32+67);
        window->draw(s);
    }
    else{
    s.setTexture(digits);
    s.setPosition(21,(height-1)*32+67);
    window->draw(s);}
    s.setTexture(digits2);
    s.setPosition(42,(height-1)*32+67);
    window->draw(s);
    s.setTexture(digits3);
    s.setPosition(63,(height-1)*32+67);
    window->draw(s);
}
void board::lost() {
    gameOver = true;
    faceLose =GetTexture("images/face_lose");
    faceSpriteHappy.setTexture(faceLose);
    faceSpriteHappy.setPosition(width/2*32, (height-1)*32+(50));
    faceNum = 3;
}
void board::victory() {
    won = true;
    faceWin = GetTexture("images/face_win");
    faceSpriteHappy.setTexture(faceWin);
    faceSpriteHappy.setPosition(width/2*32, (height-1)*32+(50));
    faceNum =2;
}
void board:: clearB(){
    faceWin = GetTexture("images/face_happy");
    faceSpriteHappy.setTexture(faceHappy);
    faceSpriteHappy.setPosition(width/2*32, (height-1)*32+(50));
    faceNum =1;
    gameOver = false;
    won= false;
    minesOnBoard=0;
    changedMines =0;
    randMines =0;
    tilesRevealed=0;
    for (int i = 0; i < tilesT.size(); ++i) {
        tilesT.at(i).clearT();
    }



}
void board:: loadTest(string filename){
    ifstream infile(filename);
    string line;
    clearB();
    int count =0;
    numOfMines =0;
    while (infile.peek() !=EOF){
        getline(infile, line);
        for (int i = 0; i < line.size(); ++i) {
            if (line.at(i) == '0')//no mine
                tilesT.at(count).hasMine =false;
            else{
                tilesT.at(count).hasMine = true;
                tilesT.at(count).tmine = GetTexture("mine");
                tilesT.at(count).mineCount++;
                tilesT.at(count).addMine();
                randMines++;
                numOfMines++;
            }
            count++;
        }
    }
    tileArr();
}
void board ::tileArr(){
////CHANGE--------------
   // tiles* arr[width][height] ;//col -rows

    tiles* **arr  = new tiles**[width];
    for(int i = 0; i < width; ++i) {
        arr[i] = new tiles*[height];
    }
/////-------------------------------------
    int count =0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            arr[j][i] = &tilesT.at(count);
            arr[j][i]->xpos = j;
            arr[j][i]->ypos =i;
            arr[j][i]->thidden= GetTexture("tile_hidden");
            arr[j][i]->trevealed= GetTexture("tile_revealed");
            arr[j][i]->createTile();
            tilesT.at(count).xpos=j;
            tilesT.at(count).ypos=i;
            tilesT.at(count).thidden = GetTexture("tile_hidden");
            tilesT.at(count).trevealed = GetTexture("tile_revealed");
            tilesT.at(count).createTile();
            count++;
        }
    }

}
void board :: getRandomMines(){
    while (randMines < numOfMines)
    {
        int randx = Random::Number(0, width);
        int randy = Random::Number(0, height);
        for (int i = 0; i < tileCount; ++i) {

            if (tilesT.at(i).xpos == randx && tilesT.at(i).ypos == randy) {
                if (tilesT.at(i).hasMine ){
                    randx = Random::Number(0, width);
                    randy = Random::Number(0, height);
                }
                else{
                    tilesT.at(i).hasMine = true;
                    tilesT.at(i).tmine = GetTexture("mine");
                    tilesT.at(i).mineCount++;
                    tilesT.at(i).addMine();
                    randMines++;
                    break;
                }
            }

        }
    }

}
void board :: changeTilesToAdjacentMines(){
    for (int i = 0; i < tileCount; ++i) {
        int numOfMines= 0;
        tilesT.at(i).adjacentTiles=tilesT.at(i).adjacentT.size();
        for (int j = 0; j < tilesT.at(i).adjacentT.size(); ++j) {
            if (tilesT.at(i).adjacentT.at(j)->hasMine){
                tilesT.at(i).adjacentMines++;
                numOfMines++;
            }
        }
        int num =tilesT.at(i).adjacentTiles; //use if u want to display the number of adjacent tiles of the board

        switch (numOfMines) {
            case 1:
                tilesT.at(i).tnumber = GetTexture("number_1");
                tilesT.at(i).addNumber();
                break;
            case 2:
                tilesT.at(i).tnumber = GetTexture("number_2");
                tilesT.at(i).addNumber();
                break;
            case 3:
                tilesT.at(i).tnumber = GetTexture("number_3");
                tilesT.at(i).addNumber();
                break;
            case 4:
                tilesT.at(i).tnumber = GetTexture("number_4");
                tilesT.at(i).addNumber();
                break;
            case 5:
                tilesT.at(i).tnumber = GetTexture("number_5");
                tilesT.at(i).addNumber();
                break;
            case 6:
                tilesT.at(i).tnumber = GetTexture("number_6");
                tilesT.at(i).addNumber();
                break;
            case 7:
                tilesT.at(i).tnumber = GetTexture("number_7");
                tilesT.at(i).addNumber();
                break;
            case 8:
                tilesT.at(i).tnumber = GetTexture("number_8");
                tilesT.at(i).addNumber();
                break;
        }

    }

}
#endif //MINESWEEPER_BOARD_H
