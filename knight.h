/**
 * @author Brandon Barber
 */
#ifndef KNIGHT_H
#define KNIGHT_H

#include <QPixmap>
#include "thing.h"
#include "kale.h"

/**
 * Knight class for an enemy who will lunge out at the player.
 */
class Knight : public Thing
{
	public:
		Knight(int x, int y, QPixmap* img, Kale* p);
		~Knight();
		void move();
	private:
		QPixmap* image;
		Kale* player;
		bool lunging;
		int lungeCount;
};

#endif
