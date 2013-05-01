/**
 * @author Brandon Barber
 */
#include <QPixmap>
#include <QString>
#include <cstdlib>
#include "volcur.h"

/**
 * Constructs a default Volcur at 0 0
 */
Volcur::Volcur()
{
	path = NULL;
	setX(0);
	setY(0);
	setPixmap(QPixmap());
	left = false;
	right = false;
	setWidth(50);
}

/**
 * Creates a new volcur to patrol the path
 * @param p the path to patrol
 * @param img the image to use
 */
Volcur::Volcur(HPath* p,QPixmap* img)
{
	path = p;
	int x = 0;
	if(path != NULL && path->getLeft() != path->getRight())
	{
		x = rand() % (p->getRight() - p->getLeft()) + p->getLeft();
	}
	else if(path != NULL)
	{
		x = path->getLeft();
	}
	setX(x);
	setY(p->getY());
	image = img;
	setPixmap(*image);
	setPos(getX(),getY());
	left = rand() % 2;
	right = !left;
	setWidth(50);
}

/**
 * Destroys the volcur
 */
Volcur::~Volcur()
{

}

/**
 * Moves the volcur
 */
void Volcur::move()
{
	if(path == NULL || path->getLeft() == path->getRight())
	{
		return;
	}
	if(getX() <= path->getLeft())
	{
		left = false;
		right = true;	
	}
	else if(getX() >= path->getRight())
	{
		left = true;
		right = false;
	}
	if(left)
	{
		setX(getX() - 2);
	}
	else if(right)
	{
		setX(getX() + 2);
	}
}
