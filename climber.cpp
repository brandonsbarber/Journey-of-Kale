/**
 * @author Brandon Barber
 */
#include <QPixmap>
#include <QString>
#include <cstdlib>
#include "climber.h"

/**
 * Constructs a default climber at 0,0
 */
Climber::Climber()
{
	path = NULL;
	setX(0);
	setY(0);
	setPixmap(QPixmap());
	up = false;
	down = false;
	setWidth(50);
}

/**
 * Constructs a climber who will traverse the given path
 * @param p the path to follow
 * @param img the image to use
 */
Climber::Climber(VPath* p,QPixmap* img)
{
	path = p;
	int y = 0;
	if(path != NULL && path->getTop() != path->getBot())
	{
		y = rand() % (p->getBot() - p->getTop()) + p->getTop();
	}
	else if(path != NULL)
	{
		y = path->getTop();
	}
	setX(p->getX());
	setY(y);
	image = img;
	setPixmap(*image);
	setPos(getX(),getY());
	up = rand() % 2;
	down = !up;
	setWidth(50);
}

/**
 * Destroys the climber
 */
Climber::~Climber()
{
	
}

/**
 * Moves the climber along the path
 */
void Climber::move()
{
	if(path == NULL || path->getTop() == path->getBot())
	{
		return;
	}
	if(getY() <= path->getTop())
	{
		down = true;
		up = false;
	}
	else if(getY() >= path->getBot())
	{
		down = false;
		up = true;
	}
	if(up)
	{
		setY(getY()-5);
	}
	else if(down)
	{
		setY(getY()+5);
	}
}
