/**
 * @author Brandon Barber
 */
#include <QTimer>
#include <fstream>
#include <QBrush>
#include <sstream>
#include <string>
#include <QtAlgorithms>
#include "gamescene.h"
#include "volcur.h"
#include "hpath.h"
#include "vpath.h"
#include "climber.h"
#include "chaser.h"
#include "knight.h"

using namespace std;

/**
 * Constructs and initializes the first level of the game
 * @param QMainWindow the parent of the scene
 */
GameScene::GameScene(QMainWindow* m) : QGraphicsScene(m)
{
	framerate = 24;
	name = "Kale";
	information = new string[4];
	levelTitles = new string[4];
	levelNames = new string[4];
	levelNames[1] = "Assets/testLevel2.txt";
	levelNames[0] = "Assets/testLevel.txt";
	levelNames[2] = "Assets/testLevel3.txt";
	levelNames[3] = "Assets/testLevel4.txt";
	information[0] = "The Volcurs are invading! Escape through the ruins to your horse to get out of there!";
	information[1] = "Volcurs are overrunning the stronghold. Get the sword from atop the tower and escape!";
	information[2] = "They're still after you! Quick! To the waterfall!";
	information[3] = "Shadow Knight in pursuit! Escape over the cliff! Quickly!";
	levelTitles[0] = "Nootkar";
	levelTitles[1] = "Mountain Keep";
	levelTitles[2] = "North Forest";
	levelTitles[3] = "ESCAPE!";
	
	
	paused = true;
	currentLevel = 0;
	readPixmaps();
	numLives = 3;
	movingLeft = false;
	movingRight = false;
	climbingUp = climbingDown = climbing = false;
	timer = new QTimer(this);
	timer->setInterval(1000/framerate);

	connect(timer,SIGNAL(timeout()),this,SLOT(gameLoop()));
	
	tiles = new Tile**[20];
	player = new Kale(100,350, kalePixmap);
	bg = new QGraphicsPixmapItem();
	startLevel(levelNames[currentLevel]);
	addItem(bg);
	
	gridTLY = gridTLX = 0;
	//adds tiles
	for(int x = 0; x < 20; x++)
	{
		tiles[x] = new Tile*[14];
		for(int y = 0; y < 13; y++)
		{
			tiles[x][y] = new Tile(this,numbers[x][y],x,y,currentLevel, tilePics,tileKeys);
			addItem(tiles[x][y]);
		}
	}
	//adds enemies
	for(unsigned int i = 0; i < enemies.size(); i++)
	{
		addItem(enemies[i]);
	}
	addItem(player);
	
	
	//HUD
	redBar = new QGraphicsRectItem(0,0,200,20);
	redBar->setBrush(*(new QBrush(Qt::red)));
	addItem(redBar);
	greenBar = new QGraphicsRectItem(0,0,player->getHealth()*2,20);
	greenBar->setBrush(*(new QBrush(Qt::green)));
	addItem(greenBar);
	
	//score display
	score = 0;
	QGraphicsRectItem* scoreback = new QGraphicsRectItem(0,20,200,40);
	scoreback->setBrush(*(new QBrush(Qt::gray)));
	addItem(scoreback);
	string scorestring;
	stringstream ss;
	ss << score;
	ss >> scorestring;
	scoreText = new QGraphicsSimpleTextItem();
	scoreText->setText(QString(scorestring.c_str()));
	scoreText->setPos(100,40);
	addItem(scoreText);
	
	//name display
	nameText = new QGraphicsSimpleTextItem();
	nameText->setText(QString(name.c_str()));
	nameText->setPos(0,40);
	addItem(nameText);
	
	//lives
	livesPixmap = new QPixmap(QString("Assets/Lives.png"));
	for(int i = 0; i < numLives; i++)
	{
		lives.push_back(new QGraphicsPixmapItem(*livesPixmap));
		lives[i]->setPos(200+i*50,0);
		addItem(lives[i]);
	}
	
	//Create pause menu stuff
	resumeGameButton = new QGraphicsRectItem(300,100,350,100);
	restartGameButton = new QGraphicsRectItem(300,250,350,100);
	quitGameButton = new QGraphicsRectItem(300,400,350,100);
	
	resumeGameLabel = new QGraphicsSimpleTextItem("Resume Game");
	restartGameLabel = new QGraphicsSimpleTextItem("Restart Level");
	quitGameLabel = new QGraphicsSimpleTextItem("Quit Game");
	
	resumeGameLabel->setPos(QPointF(425,150));
	restartGameLabel->setPos(QPointF(425,300));
	quitGameLabel->setPos(QPointF(425,450));
	
	QBrush b(Qt::lightGray);
	resumeGameButton->setBrush(b);
	restartGameButton->setBrush(b);
	quitGameButton->setBrush(b);
	
	
	startSplash();
}

/**
 * Destroys the game scene
 */
GameScene::~GameScene()
{

}

/**
 * Operates based on the given key input
 * @param e the key input to reference
 */
void GameScene::keyInput(QKeyEvent* e)
{
	if(paused && e->key() != Qt::Key_Escape)
	{
		return;
	}
	switch(e->key())
	{
		case Qt::Key_Escape:if(!paused){pauseGame();}else{unpauseGame();} break;
		case Qt::Key_A : movingLeft = true;movingRight = false;climbingUp=false;climbingDown=false;climbing=false;break;
		case Qt::Key_D : movingLeft = false;movingRight = true;climbingUp=false;climbingDown=false;climbing=false;break;
		case Qt::Key_W : if(onLadder()){movingLeft = false;movingRight = false; climbingUp=true;climbingDown=false;climbing=true;player->touchdown();}break;
		case Qt::Key_S : if(onLadder()){movingLeft = false;movingRight = false; climbingDown=true;climbingUp=false;climbing=true;player->touchdown();}break;
		case Qt::Key_Space: if(!player->getAir()){player->jump();climbing=climbingUp=climbingDown=false;}break;
	}
}

/**
 * Operates based on the given key release
 * @param e the key release to reference
 */
void GameScene::keyRelease(QKeyEvent* e)
{
	switch(e->key())
	{
		case Qt::Key_A : movingLeft = false;break;
		case Qt::Key_D : movingRight = false;break;
		case Qt::Key_W : climbingUp=false;break;
		case Qt::Key_S : climbingDown=false;break;
		
	}
}

/**
 * Loop to execute every frame. Controls all movement and interactions
 */
void GameScene::gameLoop()
{
	if(movingLeft)
	{
		if(hasLeft())	//nothing there
		{
			if(gridTLX == 0)	//if at left side of map
			{
				//do nothing
			}
			else if(gridTLX%5 == 0 && player->getX() - (gridTLX*10) == 500)	//if fully displaying tiles
			{
				gridTLX--;
				refreshTilesLeft();
				popLeft();
			}
			else if(player->getX() - (gridTLX*10) == 500)	//shifting tiles
			{
				gridTLX--;
				shiftLeft();
			}
			player->moveLeft();
			//activate chasers
			if(numbers[player->getX()/50][player->getY()/50] == -8)
			{
				int x = (player->getX()/50)*50;
				for(unsigned int i = 0; i < chasers.size(); i++)
				{
					if(chasers[i]->getX() == x && !chasers[i]->activated())
					{
						chasers[i]->activate(player);
					}
				}
			}
		}
	}
	else if(movingRight)
	{
		if(hasRight())
		{
			if(gridTLX == mapWidth*5-100)	//if at right side of the map
			{
				//do nothing
			}
			else if(gridTLX%5 == 4 && player->getX() - (gridTLX*10) == 500)	//if evenly on tiles
			{
				gridTLX++;
				refreshTiles();
				popRight();
			}
			else if(player->getX() - (gridTLX*10) == 500)	//shift tiles
			{
				gridTLX++;
				shiftRight();
			}
			player->moveRight();
			//activate chasers
			if(numbers[player->getX()/50][player->getY()/50] == -8)
			{
				int x = ((player->getX()+49)/50)*50;
				for(unsigned int i = 0; i < chasers.size(); i++)
				{
					if(chasers[i]->getX() == x && !chasers[i]->activated())
					{
						chasers[i]->activate(player);
					}
				}
			}
		}
	}
	//falling
	if(!climbing && (isFalling() || player->isJumping()))
	{
		checkJump();
		player->fall();
	}
	else if(climbing)	//climbing
	{
		if(climbingUp && canClimbUp())
		{
			player->climbUp();
		}
		else if(climbingDown && canClimbDown())
		{
			player->climbDown();
		}
	}
	else
	{
		player->touchdown();
		player->normalizeY();
	}
	player->setPos(player->getX()-(gridTLX*10),player->getY());
	//check enemies
	for(unsigned int i = 0; i < enemies.size(); i++)
	{
		if(!player->invulnerable() && hitTest(enemies[i]))
		{
			QRectF r (enemies[i]->boundingRect());
			player->damage(10);
			player->setInvulnerable(10+10*(1.5*currentLevel));
			if(player->getHealth() >= 0)
			{
				QRectF rect(greenBar->rect());
				rect.moveBottomRight(QPointF(player->getHealth()*2,20));
				greenBar->setRect(rect);
			}
		}
		enemies[i]->move();
		enemies[i]->setPos(enemies[i]->getX()-(gridTLX*10),enemies[i]->getY());
	
	}
	//if dead
	if(player->getHealth() == 0)
	{
		resetLevel();
		numLives--;
		if(numLives > 0)
		{
			removeItem(lives.back());
			lives.pop_back();
		}
		else
		{
			timer->stop();
			emit gameOver();
			return;
		}
	}
	player->exhaustInvulnerable();
	//if at goal
	if(numbers[player->getX()/50][player->getY()/50] == -5)
	{
		score+=numLives*1000;
		score+=player->getHealth()*10;
		framerate *= 1.5;
		timer->setInterval(1000/framerate);
		string scorestring;
		stringstream ss;
		ss << score;
		ss >> scorestring;
		scoreText->setText(QString(scorestring.c_str()));

		currentLevel++;
		if(currentLevel == 4)
		{
			timer->stop();
			emit gameWon();
			return;
		}
		startLevel(levelNames[currentLevel]);
		
		for(int x = 0; x < 20; x++)
		{
			for(int y = 0; y < 13; y++)
			{
				tiles[x][y]->setLevel(currentLevel);
			}
		}
		resetLevel();
		for(unsigned int i = 0; i < enemies.size(); i++)
		{
			addItem(enemies[i]);
		}
		
		paused = true;
		startSplash();
		timer->stop();
		return;
	}
	timer->start();
}

/**
 * Returns if the player is falling
 * @return if the player is falling (has 0 underneath)
 */
bool GameScene::isFalling()
{
	return numbers[player->getX()/50][(player->getY()+51)/50] <= 0 && numbers[(player->getX()+49)/50][(player->getY()+51)/50] <= 0;
}

/**
 * Returns if the player can move left
 * @return if the player can move left
 */
bool GameScene::hasLeft()
{
	return player->getX() != 0 && !(numbers[(player->getX()-1)/50][player->getY()/50] > 0);
}

/**
 * Returns if the player can move right
 * @return if the player can move right
 */
bool GameScene::hasRight()
{
	return player->getX() < mapWidth*50 && !(numbers[(player->getX()+50)/50][player->getY()/50] > 0);
}

/**
 * Checks to see if the player can jump
 */
void GameScene::checkJump()
{
	if(numbers[player->getX()/50][(player->getY()+player->getVspeed())/50] > 0 || numbers[(player->getX()+49)/50][(player->getY()+player->getVspeed())/50] > 0)
	{
		player->setVspeed(0);
	}
}

/**
 * Updates the tiles to display part of the map
 */
void GameScene::refreshTiles()
{
	for(int x = 0; x < 20; x++)
	{
		for(int y = 0; y < 13; y++)
		{
			tiles[x][y]->setTile(numbers[x+gridTLX/5][y+gridTLY/5]);
		}
	}
}

/**
 * Refreshes the tiles based on moving left
 */
void GameScene::refreshTilesLeft()
{
	for(int x = 0; x < 20; x++)
	{
		for(int y = 0; y < 13; y++)
		{
			tiles[x][y]->setTile(numbers[x+gridTLX/5][y+gridTLY/5]);
		}
	}
}

/**
 * Shifts the tile positions while moving right
 */
void GameScene::popRight()
{
	for(int x = 0; x < 20; x++)
	{
		for(int y = 0; y < 13; y++)
		{
			tiles[x][y]->moveTo(tiles[x][y]->getGridX()*50,tiles[x][y]->getGridY()*50);
		}
	}
}

/**
 * Shifts the tile positions while moving left
 */
void GameScene::popLeft()
{
	for(int x = 0; x < 20; x++)
	{
		for(int y = 0; y < 13; y++)
		{
			tiles[x][y]->moveTo((tiles[x][y]->getGridX()-1)*50,tiles[x][y]->getGridY()*50);
		}
	}
}

/**
 * slides right a little
 */
void GameScene::shiftRight()
{
	for(int x = 0; x < 20; x++)
	{
		for(int y = 0; y < 13; y++)
		{
			tiles[x][y]->moveTo(tiles[x][y]->getScreenX()-10,tiles[x][y]->getScreenY());
		}
	}
}

/**
 * slides left a little
 */
void GameScene::shiftLeft()
{
	for(int x = 0; x < 20; x++)
	{
		for(int y = 0; y < 13; y++)
		{
			tiles[x][y]->moveTo(tiles[x][y]->getScreenX()+10,tiles[x][y]->getScreenY());
		}
	}
}

/**
 * Returns if the player is on a ladder
 * @param if the player is on a ladder
 */
bool GameScene::onLadder()
{
	return (numbers[player->getX()/50][player->getY()/50] == -1) || (numbers[(player->getX()+49)/50][player->getY()/50] == -1) || (numbers[player->getX()/50][(player->getY()+49)/50] == -1) || (numbers[(player->getX()+49)/50][(player->getY()+49)/50] == -1);
}

/**
 * Returns if the player can climb up (ladder above player)
 * @return if the player can climb up
 */
bool GameScene::canClimbUp()
{
	return numbers[player->getX()/50][(player->getY()-10)/50] == -1 || numbers[(player->getX()+49)/50][(player->getY()-10)/50] == -1;
}

/**
 * Returns if the player can climb down (ladder below player)
 * @return if the player can climb down
 */
bool GameScene::canClimbDown()
{
	return numbers[player->getX()/50][(player->getY()+59)/50] == -1 || numbers[(player->getX()+49)/50][(player->getY()+59)/50] == -1;
}

/**
 * Checks if player hits given thing
 * @param t the thing to check
 * @return if they touch
 */
bool GameScene::hitTest(Thing* t)
{
	return QRectF(QPointF(player->getX(),player->getY()),QPointF(player->getX()+49,player->getY()+49)).intersects(QRectF(QPointF(t->getX(),t->getY()),QPointF(t->getX()+t->getWidth(),t->getY()+t->getWidth())));
}

/**
 * Resets the current level
 */
void GameScene::resetLevel()
{
	movingLeft = false;
	movingRight = false;
	climbingUp = climbingDown = climbing = false;
	gridTLX = gridTLY = 0;
	refreshTiles();
	popRight();
	//delete player;
	player->setLoc(100,350);
	player->setHealth(100);
	player->setPos(player->getX(),player->getY());
	//addItem(player);
	QRectF rect(greenBar->rect());
	rect.moveBottomRight(QPointF(player->getHealth()*2,20));
	greenBar->setRect(rect);
}

/**
 * Loads the current level from file
 * @param levelName what file to load
 */
void GameScene::startLevel(string levelName)
{
	ifstream fin(levelName.c_str());
	
	fin >> mapWidth >> mapHeight;
	
	for(unsigned int i = 0; i < enemies.size(); i++)
	{
		removeItem(enemies[i]);
		delete enemies[i];
	}
	enemies.clear();
	
	chasers.clear();
	numbers = new int*[mapWidth];
	
	for(int x = 0 ; x < mapWidth; x++)
	{
		numbers[x] = new int[mapHeight];
	}
	
	
	for(int x = 0; x < mapHeight; x++)
	{
		for(int y = 0; y < mapWidth; y++)
		{
			
			int num;
			fin >> num;
			numbers[y][x] = num;
		}
	}
	//process map to add enemies
	for(int x = 0; x < mapWidth; x++)
	{
		for(int y = 0; y < mapHeight; y++)
		{
			if(numbers[x][y] == -3)
			{
				HPath* path = new HPath(x*50,x*50,y*50);
				int x2 = x;
				while(x2 < mapWidth && numbers[x2][y] == -3)
				{
					numbers[x2][y] = -2;
					path->setRight(x2*50);
					x2++;
				}
				Volcur* v = new Volcur(path,volcurPixmap);
				enemies.push_back(v);
			}
			else if(numbers[x][y] == -4)
			{
				VPath* path = new VPath(y*50,y*50,x*50);
				int y2 = y;
				while(y2 < mapHeight && numbers[x][y2] == -4)
				{
					numbers[x][y2] = -1;
					path->setBot(y2*50);
					y2++;
				}
				Climber* c = new Climber(path,climberPixmap);
				enemies.push_back(c);
			}
			else if(numbers[x][y] == -6)
			{
				int y2 = y;
				while(y2 < mapHeight && numbers[x][y2] == -6)
				{
					numbers[x][y2] = -8;
					y2++;
				}
				y2--;
				Chaser* c = new Chaser(x*50,y2*50,numbers,chaserPixmap);
				enemies.push_back(c);
				chasers.push_back(c);
			}
			else if(numbers[x][y] == -9)
			{
				Knight* k = new Knight(x*50,y*50,knightPixmap,player);
				enemies.push_back(k);
			}
		}
	}
	bg->setPixmap(backgrounds[currentLevel]);//n.c_str())));
}

/**
 * Loads in all pixmaps and maps conversion values
 */
void GameScene::readPixmaps()
{
	backgrounds[0] = QPixmap(QString("Assets/level1.png"));
	backgrounds[1] = QPixmap(QString("Assets/level2.png"));
	backgrounds[2] = QPixmap(QString("Assets/level3.png"));
	backgrounds[3] = QPixmap(QString("Assets/level3.png"));
	volcurPixmap = new QPixmap(QString("Assets/Volcur.png"));
	knightPixmap = new QPixmap(QString("Assets/ShadowKnight.png"));
	climberPixmap = new QPixmap(QString("Assets/Climber.png"));
	kalePixmap = new QPixmap(QString("Assets/Kale.png"));
	chaserPixmap = new QPixmap(QString("Assets/Chaser.png"));
	
	tilePics = new QPixmap*[16];
	tilePics[0] = new QPixmap(QString("Assets/tile_0_-1.png"));
	tilePics[1] = new QPixmap(QString("Assets/tile_0_1.png"));
	tilePics[2] = new QPixmap(QString("Assets/tile_0_2.png"));
	tilePics[3] = new QPixmap(QString("Assets/tile_0_3.png"));
	tilePics[4] = new QPixmap(QString("Assets/tile_0_4.png"));
	tilePics[11] = new QPixmap(QString("Assets/tile_0_-5.png"));
	
	tilePics[5] = new QPixmap(QString("Assets/tile_1_1.png"));
	tilePics[6] = new QPixmap(QString("Assets/tile_1_2.png"));
	tilePics[7] = new QPixmap(QString("Assets/tile_1_3.png"));
	tilePics[8] = new QPixmap(QString("Assets/tile_1_4.png"));
	tilePics[9] = new QPixmap(QString("Assets/tile_1_-5.png"));
	tilePics[10] = new QPixmap(QString("Assets/tile_1_-10.png"));
	
	tilePics[12] = new QPixmap(QString("Assets/tile_2_1.png"));
	tilePics[13] = new QPixmap(QString("Assets/tile_2_2.png"));
	tilePics[14] = new QPixmap(QString("Assets/tile_2_3.png"));
	tilePics[15] = new QPixmap(QString("Assets/tile_2_4.png"));
	
	tileKeys = new vector<map<int,int> >();
	map<int,int> level0;
	level0[-1] = 0;
	level0[1]  = 1;
	level0[2]  = 2;
	level0[3]  = 3;
	level0[4]  = 4;
	level0[-5] = -1;
	level0[0] = -1;
	level0[-2] = -1;
	level0[-3] = -1;
	level0[-10] = 2;
	level0[-5] = 11;
	
	map<int,int> level1;
	level1[-1] = 0;
	level1[1]  = 5;
	level1[2]  = 6;
	level1[3]  = 7;
	level1[4]  = 6;
	level1[-5] = 9;
	level1[0] = -1;
	level1[-2] = 10;
	level1[-3] = -1;
	level1[-10] = 10;
	level1[-11] = 10;
	
	map<int,int> level2;
	level2[-1] = 0;
	level2[1]  = 12;
	level2[2]  = 13;
	level2[3]  = 14;
	level2[5]  = 15;
	level2[4]  = 6;
	level2[-5] = -1;
	level2[0]  = -1;
	level2[-2] = -1;
	level2[-3] = -1;
	level2[-10] = 10;
	level2[-11] = 10;
	level2[-6] = -1;
	level2[-7] = -1;
	level2[-8] = -1;
	level2[-9] = -1;
	
	map<int,int> level3;
	level3[-1] = 0;
	level3[1]  = 12;
	level3[2]  = 13;
	level3[3]  = 14;
	level3[5]  = 15;
	level3[4]  = 6;
	level3[-5] = -1;
	level3[0]  = -1;
	level3[-2] = -1;
	level3[-3] = -1;
	level3[-10] = 15;
	level3[-11] = 10;
	level3[-6] = -1;
	level3[-7] = -1;
	level3[-8] = -1;
	level3[-9] = -1;
	
	tileKeys->push_back(level0);
	tileKeys->push_back(level1);
	tileKeys->push_back(level2);
	tileKeys->push_back(level3);
}

/**
 * Displays the start splash screen
 */
void GameScene::startSplash()
{
	startSplashB = true;
	graySplash = new QGraphicsRectItem(0,0,950,650);
	graySplash->setBrush(QBrush(Qt::gray));
	addItem(graySplash);
	
	levelTitle = new QGraphicsSimpleTextItem(levelTitles[currentLevel].c_str());
	QFont lF;
	lF.setPointSize(24);
	levelTitle->setFont(lF);
	levelTitle->setPos(QPointF(425,15));
	addItem(levelTitle);
	
	
	
	infoText = new QGraphicsSimpleTextItem(information[currentLevel].c_str());
	QFont f;
	f.setPointSize(18);
	infoText->setFont(f);
	infoText->setPos(QPointF(0,100));
	
	playGame = new QGraphicsRectItem(300,400,350,150);
	playText = new QGraphicsSimpleTextItem("Play Game");
	playGame->setBrush(QBrush(Qt::lightGray));
	playText->setPos(QPointF(445,475));
	addItem(playGame);
	addItem(playText);
	addItem(infoText);
}

/**
 * Hides the start splash screen
 */
void GameScene::removeStart()
{
	startSplashB = false;
	removeItem(graySplash);
	removeItem(levelTitle);
	removeItem(playGame);
	removeItem(playText);
	removeItem(infoText);
}

/**
 * Registers mouse click
 * @param e the mouse click
 */
void GameScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
	//splash
	if(paused && startSplashB && playGame->rect().contains(e->scenePos()))
	{
		removeStart();
		timer->start();
		paused = false;
	}
	else if(paused)//pause
	{
		if(resumeGameButton->rect().contains(e->scenePos()))
		{
			unpauseGame();
		}
		else if(restartGameButton->rect().contains(e->scenePos()))
		{
			resetLevel();
			unpauseGame();
		}
		else if(quitGameButton->rect().contains(e->scenePos()))
		{
			emit gameClosing();
		}
	}
}
/**
 * Pauses the game
 */
void GameScene::pauseGame()
{
	paused = true;
	timer->stop();
	
	addItem(resumeGameButton);
	addItem(restartGameButton);
	addItem(quitGameButton);
	addItem(resumeGameLabel);
	addItem(restartGameLabel);
	addItem(quitGameLabel);
}

/**
 * Unpauses the game
 */
void GameScene::unpauseGame()
{
	paused = false;
	timer->start();
	removeItem(resumeGameButton);
	removeItem(restartGameButton);
	removeItem(quitGameButton);
	removeItem(resumeGameLabel);
	removeItem(restartGameLabel);
	removeItem(quitGameLabel);
}

/**
 * Restarts the game
 */
void GameScene::restartGame()
{
	framerate = 24;
	timer->setInterval(1000/framerate);
	
	currentLevel = 0;
	gridTLX = 0;
	score = 0;
	for(int i = numLives; i < 3; i++)
	{
		lives.push_back(new QGraphicsPixmapItem(*livesPixmap));
		lives[i]->setPos(200+i*50,0);
		addItem(lives[i]);
	}
	numLives = 3;
	scoreText->setText("0");
	if(paused)
	{
		unpauseGame();
	}
	paused = true;
	timer->stop();
	player->setPos(100,350);
	player->setHealth(100);
	startLevel(levelNames[currentLevel]);
	for(int x = 0; x < 20; x++)
	{
		for(int y = 0; y < 13; y++)
		{
			tiles[x][y]->setLevel(currentLevel);
		}
	}
	resetLevel();
	for(unsigned int i = 0; i < enemies.size(); i++)
	{
		addItem(enemies[i]);
	}
		
	paused = true;
	startSplash();
	timer->stop();
}

/** Gets the score of the game
 * @return the score
 */
int GameScene::getScore()
{
	return score;
}

/**
 * Sets the name to be displayed
 * @param s the name to be displayed
 */
void GameScene::setName(string s)
{
	name = s;
	nameText->setText(name.c_str());
}

/**
 * Gets the display name
 * @return display name
 */
string GameScene::getName()
{
	return name;
}
