/**
 * @author Brandon Barber
 */
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <string>
#include <vector>
#include <map>
#include "thing.h"
#include "tile.h"
#include "kale.h"
#include "chaser.h"
#include "knight.h"

/**
 * Class for a full representation of the game
 */
class GameScene : public QGraphicsScene
{
	Q_OBJECT
	public:
		GameScene(QMainWindow* m);
		~GameScene();
		void keyInput(QKeyEvent* e);
		void keyRelease(QKeyEvent* e);
		void resetLevel();
		void restartGame();
		void startLevel(std::string name);
		int getScore();
		string getName();
		void setName(string s);
		void mousePressEvent(QGraphicsSceneMouseEvent* e);
	public slots:
		void gameLoop();
	signals:
		void gameClosing();
		void gameWon();
		void gameOver();
	private:
		//Images
		void startSplash();
		void removeStart();
		void readPixmaps();
		QPixmap** tilePics;
		
		bool hitTest(Thing* t);
		//Jumping
		bool isFalling();
		void checkJump();
		//LR Movement
		bool hasLeft();
		bool hasRight();
		//LR Graphics
		void refreshTiles();
		void refreshTilesLeft();
		void popRight();
		void popLeft();
		void shiftRight();
		void shiftLeft();
		//Climbing
		bool onLadder();
		bool canClimbDown();
		bool canClimbUp();
		QTimer* timer;
		bool movingLeft;
		bool movingRight;
		bool climbingUp;
		bool climbingDown;
		bool climbing;
		Tile*** tiles;
		int gridTLX, gridTLY;
		int ** numbers;
		//int numbers[86][14];
		Kale* player;
		vector<Thing*> enemies;
		
		int mapWidth,mapHeight;
		int currentLevel;
		
		int score;
		QGraphicsSimpleTextItem* scoreText;
		
		std::string name;
		QGraphicsSimpleTextItem* nameText;
		//Healthbar
		QGraphicsRectItem* greenBar;
		QGraphicsRectItem* redBar;
		
		int numLives;
		vector<QGraphicsPixmapItem*> lives;
		//Graphics
		vector<map<int, int> >* tileKeys;
		QGraphicsPixmapItem* bg;
		QPixmap backgrounds[4];
		QPixmap* volcurPixmap;
		QPixmap* climberPixmap;
		QPixmap* kalePixmap;
		QPixmap* livesPixmap;
		QPixmap* chaserPixmap;
		//Splash screen stuff
		QGraphicsSimpleTextItem* infoText;
		QGraphicsRectItem* playGame;
		QGraphicsSimpleTextItem* playText;
		QGraphicsRectItem* graySplash;
		QGraphicsSimpleTextItem* levelTitle;
		//Pause and splash methods
		bool paused;
		bool startSplashB;
		string* information;
		string* levelTitles;
		void pauseGame();
		void unpauseGame();
		//Pause menu buttons
		QGraphicsRectItem* resumeGameButton;
		QGraphicsRectItem* restartGameButton;
		QGraphicsRectItem* quitGameButton;
		//Pause menu labels
		QGraphicsSimpleTextItem* resumeGameLabel;
		QGraphicsSimpleTextItem* restartGameLabel;
		QGraphicsSimpleTextItem* quitGameLabel;
		
		string* levelNames;
		vector<Chaser*> chasers;
		QPixmap* knightPixmap;
		int framerate;
};

#endif
