/**
 * @author Brandon barber
 */
#include <QMainWindow>
#include <iostream>
#include <QGraphicsView>
#include <QLayout>
#include <QLineEdit>
#include "mainwindow.h"
#include "gamescene.h"

using namespace std;

/**
 * Constructs a main window
 */
MainWindow::MainWindow()
{
	nameLine = new QLineEdit("Kale");
	dock = new QDockWidget();
	dock->setWidget(nameLine);
	addDockWidget(Qt::TopDockWidgetArea,dock);

	menuScene = new MenuScene(this);
	menuView = new QGraphicsView(menuScene);
	menuView->setFixedSize(QSize(950,650));
	menuView->setSceneRect(menuView->frameGeometry());
	menuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	menuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setCentralWidget(menuView);
	gameScene = new GameScene(this);
	view = new QGraphicsView(gameScene);
	view->setFixedSize(QSize(950,650));
	view->setSceneRect(view->frameGeometry());
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->layout()->setSizeConstraint(QLayout::SetFixedSize);
	
	connect(gameScene,SIGNAL(gameClosing()),this,SLOT(gameOver()));
	connect(menuScene,SIGNAL(playGame()),this,SLOT(startGame()));
	connect(menuScene,SIGNAL(quitGame()),this,SLOT(closeGame()));
	connect(gameScene,SIGNAL(gameOver()),this,SLOT(gameOver()));
	connect(gameScene,SIGNAL(gameWon()),this,SLOT(gameWon()));
	gameRunning = false;
}

/**
 * Destroys the window
 */
MainWindow::~MainWindow()
{

}

/**
 * processes a key press
 * @param e key press
 */
void MainWindow::keyPressEvent(QKeyEvent* e)
{
	if(gameRunning)
	{
		gameScene->keyInput(e);
	}
}

/**
 * processes a key release
 * @param e key release
 */
void MainWindow::keyReleaseEvent(QKeyEvent* e)
{
	if(gameRunning)
	{
		gameScene->keyRelease(e);
	}
}

/**
 * Closes the game
 */
void MainWindow::closeGame()
{
	close();
}

/**
 * Starts a game
 */
void MainWindow::startGame()
{
	dock->setVisible(false);
	gameRunning = true;
	gameScene->setName(getString(nameLine));
	view = new QGraphicsView(gameScene);
	view->setFixedSize(QSize(950,650));
	view->setSceneRect(view->frameGeometry());
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setCentralWidget(view);
}

/**
 * Processes winning scenario
 */
void MainWindow::gameWon()
{
	dock->setVisible(true);
	menuScene->setTBText("Congrats! You won! ",gameScene->getName(),gameScene->getScore());
	gameRunning = false;
	menuView = new QGraphicsView(menuScene);
	menuView->setFixedSize(QSize(950,650));
	menuView->setSceneRect(menuView->frameGeometry());
	menuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	menuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setCentralWidget(menuView);
	gameScene->restartGame();
}

/**
 * Processes game over scenario
 */
void MainWindow::gameOver()
{
	dock->setVisible(true);
	menuScene->setTBText("Better luck next time. ",gameScene->getName(),gameScene->getScore());
	gameRunning = false;
	menuView = new QGraphicsView(menuScene);
	menuView->setFixedSize(QSize(950,650));
	menuView->setSceneRect(menuView->frameGeometry());
	menuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	menuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setCentralWidget(menuView);
	gameScene->restartGame();
}

/**
 * Gets the string of the QLineEdit
 * @param e the lineEdit
 * @return text contained
 */
string MainWindow::getString(QLineEdit* e)
{
	return e->text().toUtf8().constData();
}
