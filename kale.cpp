/**
 * @author Brandon Barber
 */
#include "kale.h"

/**
 * Constructs a default player with no image and at 0,0
 */
Kale::Kale()
{
	globalX = 0;
	globalY = 0;
	MOVE_SPEED = 10;
	vspeed = 0;
	setPixmap(QPixmap());
	setPos(globalX, globalY);
	inAir = false;
	invulnerability = 0;
	health = 100;
}

/**
 * Constructs a player at the given x and y
 * @param x the x for the player
 * @param y the y for the player
 */
Kale::Kale(int x, int y, QPixmap* img)
{
	globalX = x;
	globalY = y;
	MOVE_SPEED = 10;
	vspeed = 0;
	image = img;
	setPixmap(*image);
	setPos(globalX, globalY);
	inAir = false;
	invulnerability = 0;
	health = 100;
}

/**
 * Destroys the player
 */
Kale::~Kale()
{

}

/**
 * Sets the location of the player to the given points
 * @param x the new x of the player
 * @param y the new y of the player
 */
void Kale::setLoc(int x, int y)
{
	globalX = x;
	globalY = y;
}

/**
 * Moves the player right by move_speed
 */
void Kale::moveRight()
{
	globalX+=MOVE_SPEED;
}

/**
 * Moves the player left
 */
void Kale::moveLeft()
{
	globalX-=MOVE_SPEED;
}

/**
 * Gets the x of the player
 * @return player's x
 */
int Kale::getX()
{
	return globalX;
}

/**
 * Gets the y of the player
 * @return player's y
 */
int Kale::getY()
{
	return globalY;
}

/**
 * Causes the player to accelerate and fall
 */
void Kale::fall()
{
	inAir = true;
	globalY += vspeed;
	vspeed++;
	setPos(QPointF(globalX,globalY));
}

/**
 * Causes the player to stop upon hitting the ground
 */
void Kale::touchdown()
{
	inAir = false;
	vspeed = 0;
}

/**
 * Makes the player jump
 */
void Kale::jump()
{
	if(!inAir)
	{
		vspeed = -15;
	}
}

/**
 * Returns if the player is jumping (moving upward)
 * @return if the player is jumping
 */
bool Kale::isJumping()
{
	return vspeed < 0;
}

/**
 * Returns if the player is in air (jumping or falling)
 * @return if player is in air
 */
bool Kale::getAir()
{
	return inAir;
}

/**
 * Snaps the player up fully into upper square
 */
void Kale::normalizeY()
{
	globalY=(globalY/50)*50;
}

/**
 * Sets the y velocity to the given value
 * @param speed the new y speed
 */
void Kale::setVspeed(int speed)
{
	vspeed = speed;
}

/**
 * Gets the y velocity of the player
 * @return y velocity of the player
 */
int Kale::getVspeed()
{
	return vspeed;
}

/**
 * Causes the player to climb up
 */
void Kale::climbUp()
{
	globalY-=MOVE_SPEED;
}

/**
 * Causes the player to climb down
 */
void Kale::climbDown()
{
	globalY+=MOVE_SPEED;
}

/**
 * Returns if the player is invulnerable to damage
 * @return if the player is invulnerable
 */
bool Kale::invulnerable()
{
	return invulnerability != 0;
}

/**
 * Decreases invulnerability
 */
void Kale::exhaustInvulnerable()
{
	if(invulnerable())
	{
		invulnerability--;
	}
}

/**
 * Damages the player by the given amount
 * @param amount the amount to damage by
 */
void Kale::damage(int amount)
{
	health-=amount;
}

/**
 * Sets health to the given amount
 * @param amount what to set health to
 */
void Kale::setHealth(int amount)
{
	health = amount;
}

/**
 * Sets how invulnerable the player is
 * @param amount how invulnerable
 */
void Kale::setInvulnerable(int amount)
{
	invulnerability = amount;
}

/**
 * Gets the health of the player
 * @return health amount
 */
int Kale::getHealth()
{
	return health;
}
