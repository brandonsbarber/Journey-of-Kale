/**
 * @author Brandon Barber
 */
#ifndef CLIMBER_H
#define CLIMBER_H

#include "thing.h"
#include "vpath.h"

/**
 * Class for a climbing enemy
 */
class Climber : public Thing
{
	public:
		Climber();
		Climber(VPath * p,QPixmap* img);
		~Climber();
		void move();
	private:
		bool up, down;
		VPath* path;
		QPixmap* image;

};

#endif
