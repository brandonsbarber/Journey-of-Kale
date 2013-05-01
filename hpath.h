/**
 * @author Brandon Barber
 */
#ifndef HPATH_H
#define HPATH_H

/**
 * Class for representing a horizontal path to be traversed by an enemy
 */
class HPath
{
	public:
		/**
		 * Constructs a new HPath
		 * @param l the left bound
		 * @param r the right bound
		 * @ param y the y position
		 */
		HPath(int l,int r, int y){left = l;right = r;y_ = y;}
		
		/**
		 * Destroys the HPath
		 */
		~HPath(){}
		
		/**
		 * Gets the left x of the path
		 * @return the left x
		 */
		int getLeft(){return left;}
		
		/**
		 * Gets the right x of the path
		 * @return the right x
		 */
		int getRight(){return right;}
		
		/**
		 * Sets the right x to the given x
		 * @param r the new right
		 */
		void setRight(int r){right = r;}
		
		/**
		 * Sets the y to the given value
		 * @param y the new y
		 */
		void setY(int y){y_ = y;}
		
		/**
		 * Gets the y of the path
		 * @return y of the path
		 */
		int getY(){return y_;}
	private:
		int left;
		int right;
		int y_;
};

#endif
