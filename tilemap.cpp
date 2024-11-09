#include "Tilemap.hpp"
#include <fstream>
#include <iostream> // For debug prints

Tilemap::Tilemap(const std::string& jsonFile) {
    LoadFromJson(jsonFile);
    tileTexture = LoadTexture("assets/spritesheet_ground.png"); // Assuming you have a tile.png file
    if (tileTexture.id == 0) {
        std::cerr << "Failed to load tile texture!" << std::endl;
    }
}

void Tilemap::LoadFromJson(const std::string& jsonFile) {
    std::ifstream file(jsonFile);
    nlohmann::json jsonData;
    file >> jsonData;

    tileWidth = jsonData["tileWidth"];
    tileHeight = jsonData["tileHeight"];
    auto jsonMap = jsonData["map"].get<std::vector<std::vector<int>>>();
    auto jsonTypes = jsonData["types"].get<std::vector<std::vector<int>>>();

    for (size_t y = 0; y < jsonMap.size(); ++y) {
        std::vector<Tile> row;
        for (size_t x = 0; x < jsonMap[y].size(); ++x) {
            Tile tile;
            tile.id = jsonMap[y][x];
            tile.type = jsonTypes[y][x]; // Set the type from JSON data

            // Calculate sourceRect based on type
            int column = tile.type % 7;
            int rowIndex = tile.type / 7; // Renamed to rowIndex to avoid conflict
            tile.sourceRect = {column * 128.0f, rowIndex * 128.0f, 128.0f, 128.0f};

            tile.destRect = {x * 32.0f, y * 32.0f, 32.0f, 32.0f}; // Desired size on the screen
            row.push_back(tile);
            std::cout << "Loaded tile at (" << x << ", " << y << ") with id " << tile.id << " and type " << tile.type << std::endl; // Debug print
        }
        map.push_back(row);
    }
}

void Tilemap::Draw() {
    for (const auto& row : map) {
        for (const auto& tile : row) {
            if (tile.id == 1) { // Assuming 1 represents a tile
                DrawTexturePro(tileTexture, tile.sourceRect, tile.destRect, {0, 0}, 0.0f, WHITE);
                std::cout << "Drawing tile at (" << tile.destRect.x << ", " << tile.destRect.y << ")" << std::endl; // Debug print
            }
        }
    }
}

bool Tilemap::IsColliding(const Rectangle& rect) const {
    for (const auto& row : map) {
        for (const auto& tile : row) {
            if (tile.id == 1 && CheckCollisionRecs(rect, tile.destRect)) { // Assuming 1 represents a solid tile
                return true;
            }
        }
    }
    return false;
}
Vector2 Tilemap::GetLastTilePosition() const {
    if (map.empty()) {
        return {0, 0};
    }
    const auto& lastRow = map.back();
    if (lastRow.empty()) {
        return {0, 0};
    }
    const auto& lastTile = lastRow.back();
    return {lastTile.destRect.x, lastTile.destRect.y};
}