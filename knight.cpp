/**
 * @author Brandon Barber
 */
#include <cstdlib>
#include "knight.h"
#include "kale.h"

/**
 * Creates a knight at the given location who targets the player object provided.
 * @param x the x of the knight
 * @param y the y of the knight
 * @param img the image to represent the knight
 * @param p the player for the knight to chase
 */
Knight::Knight(int x, int y, QPixmap* img, Kale* p)
{
	setX(x);
	setY(y);
	image = img;
	setPixmap(*image);
	setWidth(75);
	player = p;
	lunging = false;
	lungeCount = 0;
}

/**
 * Destroys the knight
 */
Knight::~Knight()
{

}

/**
 * Moves the knight based on random generation of a number
 */
void Knight::move()
{
	if(!lunging)
	{
		lunging = rand()%40 == 0;
		if(lunging)
		{
			lungeCount = 0;
		}
		setX(player->getX() - 200);
		setY(player->getY()-25);
	}
	else
	{
		if(lungeCount < 10)
		{
			setX(player->getX() - 200 + lungeCount * 20);
		}
		else
		{
			setX(player->getX() - (lungeCount - 10) * 20);
		}
		lungeCount++;
		if(lungeCount == 20)
		{
			lunging = false;
		}
	}
}
