//
// Created by Emma Mitchell on 4/14/22.
//

#ifndef MINESWEEPER_TEXTUREMANAGER_H
#define MINESWEEPER_TEXTUREMANAGER_H
#pragma once
#include "SFML/Graphics.hpp"
#include "unordered_map"
#include "string"
using std::unordered_map;
using std::string;

class TextureManager {
    static unordered_map<string, sf::Texture> textures;
public:
    static void LoadTexture(string TextureName);
    static sf::Texture& GetTexture(string TextureName);
    static void clear();

};
unordered_map<string, sf::Texture> textures;
static void LoadTexture(string TextureName){
    string p= TextureName+ ".png";
    textures[TextureName].loadFromFile(p);
}
static sf::Texture& GetTexture(string TextureName){
    if(textures.find(TextureName)==textures.end()){
        LoadTexture(TextureName);
    }
    return textures[TextureName];
}
static void clear(){
    textures.clear();
}

#endif //MINESWEEPER_TEXTUREMANAGER_H
