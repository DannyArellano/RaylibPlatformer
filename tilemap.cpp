#include "Tilemap.hpp"
#include <fstream>
#include <iostream> // Add this for debug prints

Tilemap::Tilemap(const std::string& jsonFile, const std::string& tilesheetFile, int tileWidth, int tileHeight)
    : tileWidth(tileWidth), tileHeight(tileHeight) {
    tilesheet = LoadTexture(tilesheetFile.c_str());
    if (tilesheet.id == 0) {
        std::cerr << "Failed to load tilesheet: " << tilesheetFile << std::endl;
    } else {
        std::cout << "Loaded tilesheet: " << tilesheetFile << std::endl;
    }

    if (tileWidth > 0) {
        tilesheetColumns = tilesheet.width / tileWidth;
    } else {
        tilesheetColumns = 0;
    }
    LoadFromFile(jsonFile);
}

Tilemap::~Tilemap() {
    UnloadTexture(tilesheet);
}

void Tilemap::LoadFromFile(const std::string& jsonFile) {
    std::ifstream file(jsonFile);
    if (!file.is_open()) {
        std::cerr << "Failed to open tilemap file: " << jsonFile << std::endl;
        return;
    }

    nlohmann::json jsonData;
    file >> jsonData;

    for (const auto& tileData : jsonData["tiles"]) {
        Tile tile;
        tile.rect = { tileData["x"], tileData["y"], static_cast<float>(tileWidth), static_cast<float>(tileHeight) };
        tile.isCollidable = tileData["isCollidable"];
        tile.tileIndex = tileData["tileIndex"];
        tiles.push_back(tile);

        // Debug print for each tile
        std::cout << "Loaded tile at (" << tile.rect.x << ", " << tile.rect.y << ") with tileIndex " << tile.tileIndex << " and isCollidable " << tile.isCollidable << std::endl;
    }

    // Debug print
    std::cout << "Loaded " << tiles.size() << " tiles from " << jsonFile << std::endl;
}

void Tilemap::Draw() const {
    if (tilesheetColumns == 0) {
        std::cerr << "Tilesheet columns is zero, cannot draw tiles." << std::endl;
        return; // Avoid division by zero
    }

    for (const auto& tile : tiles) {
        int tileX = (tile.tileIndex % tilesheetColumns) * tileWidth;
        int tileY = (tile.tileIndex / tilesheetColumns) * tileHeight;
        Rectangle sourceRect = { static_cast<float>(tileX), static_cast<float>(tileY), static_cast<float>(tileWidth), static_cast<float>(tileHeight) };
        DrawTexturePro(tilesheet, sourceRect, tile.rect, {0, 0}, 0.0f, WHITE);
    }
}

bool Tilemap::CheckCollision(const Rectangle& rect) const {
    for (const auto& tile : tiles) {
        if (tile.isCollidable && CheckCollisionRecs(rect, tile.rect)) {
            return true;
        }
    }
    return false;
}