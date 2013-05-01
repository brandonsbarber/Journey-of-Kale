/**
 * @author Brandon barber
 */
#include <string>
#include <sstream>
#include "menuscene.h"

using namespace std;


/**
 * Creates a new MenuScene
 * @param window the window this is held in
 */
MenuScene::MenuScene(QMainWindow* window)
{
	(void)window;
	bgItem = new QGraphicsPixmapItem();
	bgItem->setPixmap(QPixmap(QString("Assets/menuBG.png")));
	addItem(bgItem);
	
	playGameBut = new QGraphicsRectItem(475,300,200,100);
	quitGameBut = new QGraphicsRectItem(475,450,200,100);
	
	QBrush b(Qt::lightGray);
	playGameBut->setBrush(b);
	quitGameBut->setBrush(b);
	
	addItem(playGameBut);
	addItem(quitGameBut);
	
	playText = new QGraphicsSimpleTextItem("Play Game");
	quitText = new QGraphicsSimpleTextItem("Quit Game");
	playText->setPos(QPointF(550,350));
	quitText->setPos(QPointF(550,500));
	addItem(playText);
	addItem(quitText);
	
	talkBack = new QGraphicsSimpleTextItem("");
	addItem(talkBack);
	talkBack->setPos(QPointF(0,500));
}

/**
 * Deletes the MenuScene
 */
MenuScene::~MenuScene()
{

}

/**
 * Processes mouse press
 * @param e mouse press event
 */
void MenuScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
	if(playGameBut->rect().contains(e->scenePos()))
	{
		emit playGame();
	}
	else if(quitGameBut->rect().contains(e->scenePos()))
	{
		emit quitGame();
	}
}

/**
 * Sets text of the talkback display
 * @param text default text
 * @param name to show
 * @param score the score to display
 */
void MenuScene::setTBText(string text,string name, int score)
{
	talkBack->setBrush(QBrush(Qt::white));
	stringstream ss;
	string scoreS;
	ss << score;
	ss >> scoreS;
	text.append("You, "+name+", scored: "+scoreS);
	
	talkBack->setText(text.c_str());
}
