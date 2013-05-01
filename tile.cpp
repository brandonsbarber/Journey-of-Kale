/**
 * @author Brandon Barber
 */
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include "tile.h"

using namespace std;

/**
 * Constructs a new tile
 */
Tile::Tile()
{
	tile_ = 0;
	screenX = gridX = screenY = gridY = phase = level =0;
	setWidth(50);
	tiles = NULL;
	keys = NULL;
}

/**
 * Constructs a new tile at the given x and y with data
 * @param parent the parent
 * @param tile the numeric representation
 * @param x the x
 * @param y the y
 * @param l the level
 * @param t the array of tiles to display
 * @param k conversion chart for values
 */
Tile::Tile(QGraphicsScene* parent, int tile, int x, int y,int l, QPixmap** t,vector< map<int,int> >* k)
{
	(void)parent;
	tile_ = tile;
	tiles = t;
	gridX = x;
	gridY = y;
	screenX = x*50;
	screenY = y*50;
	phase = 0;
	setPos(screenX,screenY);
	setWidth(50);
	level = l;
	keys = k;
	setImage();
}

/**
 * Destroys the tile
 */
Tile::~Tile() {}

/**
 * Moves the tile to the given space
 * @param x the new x
 * @param y the new y
 */
void Tile::moveTo(int x, int y)
{
	screenX = x;
	screenY = y;
	setPos(x,y);
}

/**
 * Sets the image based on the level and value
 */
void Tile::setImage()
{
	if(tiles == NULL || keys == NULL)
	{
		return;
	}
	int index = (keys->at(level)).find(tile_)->second;
	if(index == -1)
	{
		setPixmap(QPixmap());
		return;
	}
	setPixmap(*tiles[index]);
}

/**
 * Gets where x is shown on screen
 * @return x screen position
 */
int Tile::getScreenX()
{
	return screenX;
}

/**
 * Gets where y is shown on screen
 * @return y screen position
 */	
int Tile::getScreenY()
{
	return screenY;
}

/**
 * Gets where the x of the tile is in grid 
 * @return where the x of the tile is in grid 
 */
int Tile::getGridX()
{
	return gridX;
}

/**
 * Gets where the y of the tile is in grid 
 * @return where the y of the tile is in grid 
 */
int Tile::getGridY()
{
	return gridY;
}

/**
 * Gets the value held by the tile
 * @return value of the tile
 */
int Tile::getTile()
{
	return tile_;
}

/**
 * Sets tile to the given value
 * @param tile tile value to represent
 */
void Tile::setTile(int tile)
{
	tile_ = tile;
	setImage();
}

/**
 * Does nothing
 */
void Tile::move()
{
	return;
}

/**
 * Sets the level to the given value
 * @param l the level to set
 */
void Tile::setLevel(int l)
{
	level = l;
}
