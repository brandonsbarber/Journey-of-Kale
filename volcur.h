/**
 * @author Brandon Barber
 */
#ifndef VOLCUR_H
#define VOLCUR_H

#include <QGraphicsPixmapItem>
#include "thing.h"
#include "hpath.h"

/**
 * Class for representing a patrolling volcur
 */
class Volcur : public Thing
{
	public:
		Volcur();
		Volcur(HPath* p,QPixmap* img);
		~Volcur();
		void move();
	private:
		bool left,right;
		HPath* path;
		QPixmap* image;
};

#endif
