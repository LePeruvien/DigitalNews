#ifndef IVYBINDER_HPP
#define IVYBINDER_HPP

#include <QtCore/QDebug>

#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <unistd.h>
#include <QApplication>

#include <Ivy/Ivycpp.h>
#include <Ivy/IvyApplication.h>

//#include "IvyLoop.hpp"

class IvyBinder : public QObject, public IvyApplicationCallback, public IvyMessageCallback{
	Q_OBJECT

public:
	IvyBinder();

	Ivy *bus;
	void IvyStart();
	void OnApplicationConnected(IvyApplication *app);
	void OnApplicationDisconnected(IvyApplication *app);
	void OnApplicationCongestion(IvyApplication *app);
	void OnApplicationDecongestion(IvyApplication *app);
	void OnApplicationFifoFull(IvyApplication *app);
	void OnMessage(IvyApplication *app, int argc, const char **argv);
	//static void myOwnCB1 ( IvyApplication *app, void *user_data, int argc, const char **argv );

private:
	static void ivyAppConnCb(IvyApplication *app ) {};
	static void ivyAppDiscConnCb(IvyApplication *app ) {};

	//IvyLoop *loop;

signals:
	void scrollUpgesture();
	void scrollDownGesture();
	void closeGesture();
};

#endif // IVYBINDER_HPP
