/**
 * @author Brandon Barber
 */
#include "chaser.h"
/**
 * Creates a new chaser object with access to the map
 * @param x the x to spawn at
 * @param y the y to spawn at
 * @param m the map to reference
 * @param img the image to display
 */
Chaser::Chaser(int x, int y, int** m, QPixmap* img)
{
	setX(x);
	setY(y);
	map = m;
	setPos(QPointF(getX(),getY()));
	image = img;
	setPixmap(*image);
	player = NULL;
	vspeed = 0;
	setWidth(50);
}

/**
 * Destroys the chaser
 */
Chaser::~Chaser()
{

}

/**
 * Moves the chaser
 */
void Chaser::move()
{
	// if it doesn't have a player to chase
	if(!activated())
	{
		return;
	}
	
	if(player->getX() > getX())
	{
		if(canMoveRight())
		{
			setX(getX()+7);
		}
		else
		{
			jump();
		}
	}
	else if(player->getX() < getX())
	{
		if(canMoveLeft())
		{
			setX(getX()-7);
		}
		else
		{
			jump();
		}
	}
	fall();
}

/**
 * Gives the chaser a pointer to the player
 * @param p the player to reference
 */
void Chaser::activate(Kale* p)
{
	player = p;
}

/**
 * Returns if the chaser has a player yet
 * @return if the chaser has a target
 */
bool Chaser::activated()
{
	return player != NULL;
}

/**
 * Makes the chaser jump
 */
void Chaser::jump()
{	
	vspeed = -15;
}

/**
 * Makes the chaser fall
 */
void Chaser::fall()
{
	if((vspeed < 0 && map[getX()/50][(getY()+vspeed)/50] <= 0 && map[(getX()+49)/50][(getY()+vspeed)/50] <= 0) || (map[getX()/50][(getY()+50)/50] <= 0 && map[(getX()+49)/50][(getY()+50)/50] <= 0))
	{
		setY(getY()+vspeed++);
	}
	else
	{
		setY(getY()/50*50);
		vspeed = 0;
	}
}

/**
 * Returns if chaser can move left
 * @return if chaser can move left
 */
bool Chaser::canMoveLeft()
{
	return map[(getX()-7)/50][getY()/50] <= 0;
}

/**
 * Returns if chaser can move right
 * @return if chaser can move right
 */
bool Chaser::canMoveRight()
{
	return map[(getX()+56)/50][getY()/50] <= 0;
}
