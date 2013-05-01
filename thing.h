/**
 * @author Brandon barber
 */
#ifndef THING_H
#define THING_H

#include <QGraphicsPixmapItem>

/**
 * Class for representing a thing in the game
 */
class Thing : public QGraphicsPixmapItem
{
	public:
		/**
		 * Gets the x position of the thing
		 * @return the x position
		 */
		int getX(){return x_;}
		
		/**
		 * Gets the y position of the thing
		 * @return the y position
		 */
		int getY(){return y_;}
		
		/**
		 * Sets the x to the given value
		 * @param x the new x
		 */
		void setX(int x){x_ = x;}
		
		/**
		 * Sets the y to the given value
		 * @param y the new y
		 */
		void setY(int y){y_ = y;}
		
		/**
		 * Abstract move function
		 */
		virtual void move() = 0;
		
		/**
		 * Sets the width to the given size
		 * @param w the width to set
		 */
		void setWidth(int w){width = w;}
		
		/**
		 * Gets the width of the thing
		 * @return the width
		 */
		int getWidth(){return width;}
	private:
		int x_;
		int y_;
		int width;
};

#endif
