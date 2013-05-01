/**
 * @author Brandon Barber
 */
#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <vector>
#include <map>
#include "thing.h"

using namespace std;

/**
 * Class for a tile object
 */
class Tile : public Thing
{
	public:
		Tile();
		Tile(QGraphicsScene* parent, int tile, int x, int y,int l, QPixmap** t,vector<map<int,int> >* k);
		~Tile();
		void moveTo(int x, int y);
		int getScreenX();
		int getScreenY();
		int getGridX();
		int getGridY();
		int getTile();
		void setTile(int tile);
		void move();
		void setLevel(int l);
		
	private:
		int screenX, screenY;
		int gridX, gridY;
		int tile_;
		void setImage();
		int phase;
		int level;
		QPixmap** tiles;
		vector<map<int,int> >* keys;
};

#endif
