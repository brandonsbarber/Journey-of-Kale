/**
 * @author Brandon barber
 */
#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QLineEdit>
#include <QGraphicsSceneMouseEvent>
#include <string>

using namespace std;

/**
 * Class for representing the main menu
 */
class MenuScene : public QGraphicsScene
{
	Q_OBJECT
	public:
		MenuScene(QMainWindow* m);
		~MenuScene();
		void mousePressEvent(QGraphicsSceneMouseEvent* e);
		void setTBText(string text, string name, int score);
	signals:
		void playGame();
		void quitGame();
	private:
		QGraphicsPixmapItem* bgItem;
		QGraphicsRectItem* playGameBut,*quitGameBut;
		QGraphicsSimpleTextItem *playText,*quitText;
		QGraphicsSimpleTextItem *talkBack;
};

#endif
