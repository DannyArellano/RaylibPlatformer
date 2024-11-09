#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>
#include "raylib.h"
#include "json.hpp"

struct Tile {
    int id;
    Rectangle sourceRect;
    Rectangle destRect;
    int type;
};

class Tilemap {
public:
    Tilemap(const std::string& jsonFile);
    void Draw();
    bool IsColliding(const Rectangle& rect) const;

    int GetWidth() const { return map.empty() ? 0 : map[0].size(); }
    int GetHeight() const { return map.size(); }
    int GetTileWidth() const { return tileWidth; }
    int GetTileHeight() const { return tileHeight; }
    Vector2 GetLastTilePosition() const;
private:
    std::vector<std::vector<Tile>> map;
    Texture2D tileTexture;
    int tileWidth;
    int tileHeight;

    void LoadFromJson(const std::string& jsonFile);
};

#endif // TILEMAP_HPP