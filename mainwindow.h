/**
 * @author Brandon barber
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QDockWidget>
#include "gamescene.h"
#include "menuscene.h"

/**
 * Class to hold the entire game
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
		MainWindow();
		~MainWindow();
	public slots:
		void keyPressEvent(QKeyEvent* e);
		void keyReleaseEvent(QKeyEvent* e);
		void closeGame();
		void startGame();
		void gameOver();
		void gameWon();
	private:
		GameScene* gameScene;
		MenuScene* menuScene;
		QGraphicsView* view,* menuView;
		QLineEdit* nameLine;
		bool gameRunning;
		QDockWidget* dock;
		string getString(QLineEdit* e);
};

#endif
