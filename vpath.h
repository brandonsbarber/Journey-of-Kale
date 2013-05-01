/**
 * @author Brandon Barber
 */
#ifndef VPATH_H
#define VPATH_H

/**
 * Class for representing a vertical path
 */
class VPath
{
	public:
		/**
		 * Creates a new vertical path
		 * @param t the top val
		 * @param b the bot val
		 * @param x the x val
		 */
		VPath(int t,int b, int x){top = t;bot = b;x_ = x;}
		
		/**
		 * Destroys the path
		 */
		~VPath(){}
		
		/**
		 * Gets the top value
		 * @return the top value
		 */
		int getTop(){return top;}
		
		/**
		 * Gets the bottom value
		 * @return the bottom value
		 */
		int getBot(){return bot;}
		
		/**
		 * Sets the bottom value
		 * @param b the new bottom
		 */
		void setBot(int b){bot = b;}
		
		/**
		 * Sets the x value
		 * @param x the new x
		 */
		void setX(int x){x_ = x;}
		
		/**
		 * Gets the x of the path
		 * @return the x
		 */
		int getX(){return x_;}
	private:
		int top;
		int bot;
		int x_;
};

#endif
