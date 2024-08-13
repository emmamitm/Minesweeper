#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Random.h"

#include "board.h"
#include "string"
#include "fstream"
#include "ostream"
#include "sstream"
#include "string"
#include "tiles.h"
#include "map"
#include "TextureManager.h"
using namespace std;

void openFile(string file, board* board){
    ifstream inFile(file, ios_base:: binary);
    string line;
    string width;
    string height;
    string mines;

        getline(inFile, line);
        stringstream stream1(line);
        getline(stream1, width);
        getline(inFile, line);
        stringstream stream2(line);
        getline(stream2, height);
        getline(inFile, line);
        stringstream stream3(line);
        getline(stream3, mines);

    board->width = stoi(width);
    board->height = stoi(height);
    board->numOfMines= stoi(mines);
    board-> tileCount = board->width*board->height;


}
void LoadFiles(){
    string im = "images/";
    LoadTexture(im +"tile_hidden");
    LoadTexture(im+ "tile_revealed");
    LoadTexture(im +"number_1");
    LoadTexture(im +"number_2");
    LoadTexture(im +"number_3");
    LoadTexture(im +"number_4");
    LoadTexture(im +"number_5");
    LoadTexture(im +"number_6");
    LoadTexture(im +"number_7");
    LoadTexture(im +"number_8");
    LoadTexture(im +"flag");
    LoadTexture(im +"mine");
    LoadTexture(im +"digits");
    LoadTexture(im +"face_happy");
    LoadTexture(im +"face_lose");
    LoadTexture(im +"face_win");
    LoadTexture(im +"test_1");
    LoadTexture(im +"test_2");
    LoadTexture(im +"test_3");
    LoadTexture(im +"debug");

}
void adjacentTiles(board *b){

    for (int i = 0; i < b->tileCount; ++i) {
        if(!b->tilesT.at(i).hasMine){ //if a tile is mine free--> have to get a mine count
            //looking for adjacent tiles
            tiles* tpt;
            try {
                if(b->tilesT.at(i).xpos ==0  ){ //if it is in the first collumn
                    throw exception();
                }
                tpt= &b->tilesT.at(i-1);
                b->tilesT.at(i).adjacentT.push_back(tpt);
            }
            catch (exception e){
            }
            try {
                if(b->tilesT.at(i).xpos ==b->width-1 ){ //if it is in the last row
                    throw exception();
                }
                tpt= &b->tilesT.at(i+1);
                b->tilesT.at(i).adjacentT.push_back(tpt);
            }
            catch (exception e){
            }
            try {
                if(b->tilesT.at(i).ypos ==b->height-1 ){ //if it is in the last row
                    throw exception();
                }
                tpt= &b->tilesT.at(i+b->width);
                b->tilesT.at(i).adjacentT.push_back(tpt);
            }
            catch (exception e){

            }
            try {
                if(b->tilesT.at(i).ypos ==b->height-1 ){ //if it is in the last row
                    throw exception();
                }
                if(b->tilesT.at(i).xpos ==0 ){ //if it is in the first collumn
                    throw exception();
                }
                tpt= &b->tilesT.at(i+b->width-1);
                b->tilesT.at(i).adjacentT.push_back(tpt);
            }
            catch (exception e){

            }
            try {
                if(b->tilesT.at(i).ypos ==b->height-1 ){ //if it is in the last row
                    throw exception();
                }
                if(b->tilesT.at(i).xpos ==b->width-1){ //if it is in the last collumn
                    throw exception();
                }

                tpt= &b->tilesT.at(i+b->width+1);
                b->tilesT.at(i).adjacentT.push_back(tpt);
            }
            catch (exception e){

            }
            try {
                if(b->tilesT.at(i).ypos ==0 ){ //if it is in the first row
                    throw exception();
                }

                tpt= &b->tilesT.at(i-b->width);
                b->tilesT.at(i).adjacentT.push_back(tpt);
            }
            catch (exception e){

            }
            try {
                if(b->tilesT.at(i).ypos ==0 ){ //if it is in the first row
                    throw exception();
                }
                if(b->tilesT.at(i).xpos ==0){ //if it is in the first collumn
                    throw exception();
                }
                tpt= &b->tilesT.at(i-b->width-1);
                b->tilesT.at(i).adjacentT.push_back(tpt);
            }
            catch (exception e){

            }
            try {
                if(b->tilesT.at(i).ypos ==0 ){ //if it is in the first row
                    throw exception();
                }
                if(b->tilesT.at(i).xpos ==b->width-1){ //if it is in the last collumn
                    throw exception();
                }

                tpt= &b->tilesT.at(i-b->width+1);
                b->tilesT.at(i).adjacentT.push_back(tpt);
            }
            catch (exception e){

            }

        }
    }


}
void createButtons(board *b){
    b->digits = GetTexture("digits");;
    b->faceHappy = GetTexture("face_happy");;
    b->test1 = GetTexture("test_1");
    b->test2 = GetTexture("test_2");
    b->test3 = GetTexture("test_3");
    b->debug = GetTexture("debug");
    b->createSprites();

}
void drawBottomButtons(sf::RenderWindow* window, board *b){
    //window->draw(b->digitsSprite);
    window->draw(b->faceSpriteHappy);
    window->draw(b->test1Sprite);
    window->draw(b->test2Sprite);
    window->draw(b->test3Sprite);
    window->draw(b->debugSprite);

}
void sw(sf::RenderWindow* window, tiles *t, int num){
    switch (num) {
        case 1:
            window->draw(t->revealed);
            window->draw(t->hidden);
            break;
        case 2:
            window->draw(t->hidden);
            window->draw(t->flag);
            break;
        case 3:
            window->draw(t->revealed);
            window->draw(t->number);
            break;
        case 4:
            window->draw(t->revealed);
            break;
        case 5:
            window->draw(t->revealed);
            window->draw(t->mine);
            break;
        case 6:
            window->draw(t->revealed);
            window->draw(t->mine);
            window->draw(t->flag);
            break;
        case 7:
            window->draw(t->revealed);
            window->draw(t->flag);
            window->draw(t->mine);
            break;


    }
} ///loop for chaning the tiles
void sw2(sf::RenderWindow* window, board* b, int num){
    switch (num) {
        case 1: //regular face
            window->draw(b->faceSpriteHappy);
            break;
        case 2:
            window->draw(b->faceSpriteHappy);
            break;
        case 3:
            window->draw(b->faceSpriteHappy);
            break;

    }
} ///loop for changing the smiley faces
tiles* getTile(board* b, int x, int y){
    for (int i = 0; i < b->tileCount; ++i) {
        if (b->tilesT.at(i).xpos ==x && b->tilesT.at(i).ypos==y){
            return &b->tilesT.at(i);
        }
    }
    return nullptr;
}
void revealedBoard(sf::RenderWindow* window, board *b){
    for (int i = 0; i < b->tileCount; ++i) {
        window->draw(b->tilesT.at(i).revealed);
        if (b->tilesT.at(i).hasMine)
            window->draw(b->tilesT.at(i).mine);
        if (b->tilesT.at(i).adjacentMines>0)
            window->draw(b->tilesT.at(i).number);
        if (b->tilesT.at(i).hasFlag)
            window->draw(b->tilesT.at(i).flag);
    }
}
void revealMines(sf::RenderWindow* window, board *b){
    for (int i = 0; i < b->tileCount; ++i) {
        if (b->tilesT.at(i).hasMine)
            window->draw(b->tilesT.at(i).mine);
    }
}
void rightClick(tiles *t, board *b){
    if (t->hasFlag == true){///removes a flag
        t->rev = true; //has already been revealed
        b->changedMines--; //the mine is no longer covered
        t->hasFlag= false;
        t->num=1;
    }
    else{///adds a flag
        t->num= 2;
        t->tflag = GetTexture("flag");
        t->addFlag();
        b->changedMines++;
        if (t->hasMine){ //if the flag is correctly placed on a mine
            b->minesOnBoard++;
        }
        t->rev = true;
    }
}
void leftClick(tiles *t, board *b){
    if (t->hasMine) {///game over
        b->lost();
    }
    if(t->hasFlag){ //do nothing
    }
    else if (t->adjacentMines > 0) { ///reveal only tile clicked on
        if (t->rev == true){ //do nothing if a tilw is already revealed

        }
        else{
            t->rev = true;
            b->tilesRevealed++;
        }
        t->num=3;
    }
    else if (t->adjacentMines ==0){ ///reveal alladjacent tiles that are not mines
        if (t->rev == true){
            //do nothing if a tile is already revealed
        }
        else{
            t->rev = true;
            b->tilesRevealed++;
        }

        t->num =4;

        for (int i = 0; i < t->adjacentT.size(); ++i) {
            //reveal all of these tiles too
            if (t->adjacentT.at(i)->rev == true){

            }
            else{
                b->tilesRevealed++;
                t->adjacentT.at(i)->rev = true;
            }

            if (t->adjacentT.at(i)->adjacentMines ==0)
                t->adjacentT.at(i)->num =4;
            else
                t->adjacentT.at(i)->num =3;
        }
    }
}

int main() {
    board b;
    tiles t;
    openFile("boards/config.cfg", &b); ///opening the data to create the board
    LoadFiles(); ///loading in the texture files
    createButtons(&b);
    for (int i = 0; i < b.tileCount; ++i){
        ///adding tiles to the board object
        b.tilesT.push_back(t);
    }
    b.tileArr();


    ///Creating the window
    sf::RenderWindow window(sf::VideoMode(b.width*32, b.height*32+100), "MINESWEEPER");
    bool start = true;
    bool debug = false;
    bool test = false;
    string testName;
    int number =1;

    while (window.isOpen()){

        sf:: Event e;
        tiles *t;
        window.clear(sf::Color:: White);
        if (b.gameOver || b.won){
        drawBottomButtons(&window, &b); ///draws the bottom of the window where the user can edit the game
        b.digitsReturn(b.changedMines);
        b.printDigits(&window, b.changedMines);
            for (int i = 0; i < b.tileCount; ++i) {
                if (b.gameOver){
                    if (b.tilesT.at(i).hasMine){
                        if (b.tilesT.at(i).hasFlag){
                            b.tilesT.at(i).num = 7;
                        } else
                        b.tilesT.at(i).num = 5;
                    }

                }
                sw(&window, &b.tilesT.at(i),b.tilesT.at(i).num);
            }
        }

        while (window.pollEvent(e)){
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type ==sf::Event :: MouseButtonReleased){
                sf::Mouse mouse;
                bool tile= false;
                int x = mouse.getPosition(window).x / 32;
                int y = mouse.getPosition(window).y / 32;
                for (int i = 0; i < b.tileCount; ++i) {
                    if (b.tilesT.at(i).xpos == x && b.tilesT.at(i).ypos == y){
                        t = getTile(&b, x,y);
                        tile = true;
                        break;
                    }
                }
                if (tile) {
                    if (e.mouseButton.button == sf::Mouse::Right) {
                        if (b.gameOver || b.won){}
                        else
                        rightClick(t, &b);
                    }
                    if (e.mouseButton.button == sf::Mouse::Left) {
                        if(b.gameOver || b.won){

                        }
                        else
                        {
                            if(t->hasFlag){

                            }
                            else{
                                leftClick(t, &b);
                            }
                        }


                    }
                }
                else{
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    int x1= pixelPos.x/32;
                    int y1 = pixelPos.y/32;

                    if (e.mouseButton.button == sf::Mouse::Left) {
                        if (x1>=b.width/2 &&x1<b.width*3/4-3 && y1 >= (b.height-1)){ //reset
                            start= true;
                        }
                        if (x1>b.width*3/4-3&&x1<=b.width*3/4-1 && y1 > (b.height-1)){ //test 1
                            test = true;
                            testName = "boards/testboard1.brd";
                            cout<<"test1";
                        }
                        if (x1>b.width*3/4-1 &&x1<=b.width*3/4+1 && y1 > (b.height-1)){ //test 2
                            test = true;
                            testName = "boards/testboard2.brd";
                            cout<<"test2";
                        }
                        if (x1>b.width*3/4+1&& x1<=b.width*3/4+3 && y1 > (b.height-1)){ //test 3
                            test = true;
                            testName = "boards/testboard3.brd";
                        }
                        if (x1>b.width*3/4 && y1 > (b.height-1)){ //debug button
                            if (debug== true){ //turn off debug
                                //will hide all of the exposed tiles if clicked on twice
                                for (int i = 0; i < b.tileCount; ++i) {
                                    if (b.tilesT.at(i).hasMine){
                                        b.tilesT.at(i).num =1;
                                        if (b.tilesT.at(i).hasFlag)
                                            b.tilesT.at(i).num =2;
                                    }
                                }
                                debug= false;
                            }
                            else{ //turn on debug
                                debug = true;}
                        }
                    }
                }

            }

        }



        if(b.minesOnBoard== b.numOfMines &&(b.tileCount-b.numOfMines)==b.tilesRevealed){
            b.victory();
        }
        if (start){ ///RESTART GAME
            if (number!=1){
                b.clearB();
                openFile("boards/config.cfg", &b); ///opening the data to create the board
                LoadFiles(); ///loading in the texture files
                createButtons(&b);
                b.digitsReturn(b.changedMines);
                b.printDigits(&window, b.changedMines);
            }
            number++;
            b.getRandomMines(); ///adding random mines to the board
            adjacentTiles(&b); ///looping through all of the tiles and adding pointers to their adjacent tiles
            b.changeTilesToAdjacentMines(); ///changes the board so that the hidden values are the number of adjacent mines to every tile
            sw2(&window, &b, b.faceNum);
            drawBottomButtons(&window, &b); ///draws the bottom of the window where the user can edit the game
            b.digitsReturn(b.changedMines);
            b.printDigits(&window, b.changedMines);
            for (int i = 0; i < b.tileCount; ++i) {
                sw(&window, &b.tilesT.at(i),b.tilesT.at(i).num);
            }
            sw2(&window, &b, b.faceNum);
            start= false;
        }
        else if (b.won){/////WINNER
            sw2(&window, &b, b.faceNum);
        }
        else if (b.gameOver){/////LOSER
            sw2(&window, &b, b.faceNum);
        }
        else if(debug){ ///DEBUG
            //will display all of the mines
            for (int i = 0; i < b.tileCount; ++i) {
                if (b.tilesT.at(i).hasMine){
                    b.tilesT.at(i).num =5;
                    if (b.tilesT.at(i).hasFlag){
                        b.tilesT.at(i).num =7;
                    }

                }

            }
            for (int i = 0; i < b.tileCount; ++i) {
                sw(&window, &b.tilesT.at(i),b.tilesT.at(i).num);
            }
            drawBottomButtons(&window, &b); ///draws the bottom of the window where the user can edit the game
            b.digitsReturn(b.changedMines);
            b.printDigits(&window, b.changedMines);
        }
        else if(test){///TESTS
            //running a test board
            b.loadTest(testName);
            adjacentTiles(&b); ///looping through all of the tiles and adding pointers to their adjacent tiles
            b.changeTilesToAdjacentMines(); ///changes the board so that the hidden values are the number of adjacent mines to every tile
            drawBottomButtons(&window, &b); ///draws the bottom of the window where the user can edit the game
            //counter
            b.digitsReturn(b.changedMines);
            b.printDigits(&window, b.changedMines);

            //printing the tile
            for (int i = 0; i < b.tileCount; ++i) {
                sw(&window, &b.tilesT.at(i),b.tilesT.at(i).num);
            }
            sw2(&window, &b, b.faceNum);
            test = false;
        }
        else{ ///RUNNING THE WINDOW
            //bottom buttons
            drawBottomButtons(&window, &b); ///draws the bottom of the window where the user can edit the game
            //counter
            b.digitsReturn(b.changedMines);
            b.printDigits(&window, b.changedMines);
            //printing the tiles
            for (int i = 0; i < b.tileCount; ++i) {
                sw(&window, &b.tilesT.at(i),b.tilesT.at(i).num);
            }
            //no restarting the board
            start= false;
        }

        // end the current frame
        window.display();

    }

    return 0;
}
