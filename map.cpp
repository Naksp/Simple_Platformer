#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/game.hpp"
#include "include/graphics.hpp"
#include "include/map.hpp"
#include "include/mapRect.hpp"

using boost::shared_ptr;
using std::vector;

namespace
{
    const int num_rows = 15;
    const int num_cols = 20;
}

Map* Map::createTestMap(Graphics &graphics)
{
    Map *map = new Map();

    map->tiles = vector<vector<Tile> >(
        num_rows, vector<Tile>(
            num_cols, Tile()));

    map->texture = graphics.loatTexture("./resources/map_tile.png");

    shared_ptr<sf::Sprite> sprite(new sf::Sprite(map->texture));
    Tile tile(WALL_TILE, sprite);

    const int row = 14;
    for (int col = 0; col < num_cols; col++)
    {
        map->tiles[row][col] = tile;
    }
    map->tiles[12][0] = tile;
    map->tiles[11][8] = tile;
    map->tiles[11][9] = tile;
    map->tiles[8][7] = tile;
    map->tiles[8][6] = tile;
    map->tiles[13][8] = tile;

    return map;
}

std::vector<Map::CollisionTile> Map::getCollidingTiles(const MapRect &rect) const
{
    const int first_row = rect.top() / Game::tile_size;
    const int last_row = (rect.bottom() / Game::tile_size) >= num_rows ? num_rows-1 : (rect.bottom() / Game::tile_size); // TODO Maybe find a more elegant solution to this
    const int first_col = rect.left() / Game::tile_size;
    const int last_col = rect.right() / Game::tile_size;

    /*
    std::cout << "Rect: " << rect.left()   << ", " << 
                             rect.top()    << ", " << 
                             rect.right()  << ", " << 
                             rect.bottom() << std::endl;

    std::cout << "First row: " << first_row << "\tLast row: " << last_row << std::endl;
    std::cout << "First col: " << first_col << "\tLast col: " << last_col << std::endl;
    */

    std::vector<CollisionTile> collision_tiles;
    for (int row = first_row; row <= last_row; row++)
    {
        for (int col = first_col; col <= last_col; col++)
        {
            collision_tiles.push_back(CollisionTile(row, col, tiles[row][col].tile_type));
        }
    }

    return collision_tiles;

}

void Map::draw(Graphics &graphics)
{
    for (size_t row = 0; row < tiles.size(); row++)
    {
        for (size_t col = 0; col < tiles[row].size(); col++)
        {
            if (tiles[row][col].sprite)
            {
                tiles[row][col].sprite->setPosition(col * 16, row * 16);
                graphics.window->draw(*tiles[row][col].sprite);
            }
        }
    }
}