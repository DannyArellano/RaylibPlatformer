#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "raylib.h"
#include "json.hpp"
#include <vector>
#include <string>

class Tilemap {
public:
    Tilemap(const std::string& jsonFile, const std::string& tilesheetFile, int tileWidth, int tileHeight);
    ~Tilemap();
    void LoadFromFile(const std::string& jsonFile);
    void Draw() const;
    bool CheckCollision(const Rectangle& rect) const;

private:
    struct Tile {
        Rectangle rect;
        bool isCollidable;
        int tileIndex; // Index of the tile in the tilesheet
    };

    std::vector<Tile> tiles;
    int tileWidth;
    int tileHeight;
    Texture2D tilesheet;
    int tilesheetColumns;
};

#endif // TILEMAP_HPP