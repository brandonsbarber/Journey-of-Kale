/**
 * @author Brandon Barber
 */
#ifndef CHASER_H
#define CHASER_H

#include <QPixmap>
#include "thing.h"
#include "kale.h"

/**
 * Class for an enemy that chases the player
 */
class Chaser : public Thing
{
	public:
		Chaser(int x, int y, int** m, QPixmap* img);
		~Chaser();
		void move();
		void activate(Kale* p);
		bool activated();
	private:
		int** map;
		QPixmap* image;
		Kale* player;
		int vspeed;
		void jump();
		void fall();
		bool canMoveRight();
		bool canMoveLeft();
};

#endif
