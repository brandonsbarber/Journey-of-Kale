/**
 * @author Brandon Barber
 */
#include <QtGui/QApplication>
#include <iostream>
#include "mainwindow.h"

/**
 * Runs the game
 * @param argc number of args
 * @param argv all arguments
 */
int main(int argc, char* argv [])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
