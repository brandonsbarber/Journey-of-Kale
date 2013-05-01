/**
 * @author Brandon Barber
 */
#ifndef KALE_H
#define KALE_H

#include <QGraphicsPixmapItem>
#include <iostream>

using namespace std;

/**
 * Class for representing a player object
 */
class Kale : public QGraphicsPixmapItem
{
	public:
		Kale();
		Kale(int x, int y,QPixmap* img);
		~Kale();
		//LRMovement
		void setLoc(int x, int y);
		void moveRight();
		void moveLeft();
		int getX();
		int getY();
		//Jumping
		void fall();
		void touchdown();
		void jump();
		bool isJumping();
		bool getAir();
		void normalizeY();
		void setVspeed(int speed);
		int getVspeed();
		//Climbing
		void climbUp();
		void climbDown();
		//Health
		bool invulnerable();
		void exhaustInvulnerable();
		void damage(int amount);
		void setHealth(int amount);
		void setInvulnerable(int amount);
		int getHealth();
	private:
		int globalX,globalY;
		int vspeed;
		int MOVE_SPEED;
		bool inAir;
		int invulnerability;
		int health;
		QPixmap* image;
};
#endif
