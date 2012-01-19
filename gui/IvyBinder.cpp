#include "IvyBinder.hpp"

IvyBinder::IvyBinder() {
	//loop = new IvyLoop(new _channel);
	//loop->startNotifiersRead();
	IvyStart();
}

void IvyBinder::IvyStart() {
	bus = new Ivy( "PoisonIvy", "PoisonIvy started",
			   BUS_APPLICATION_CALLBACK(  ivyAppConnCb, ivyAppDiscConnCb ),false);
	bus->BindMsg( "(.*)", this );
	bus->start("192.168.6.255");
}

void IvyBinder::OnMessage(IvyApplication *app, int argc, const char **argv) {
	qDebug() << app->GetName() << " sent ";
	for (int i = 0; i < argc; i++) {
	  qDebug() << "'" << argv[i] << "'";
	  if (strcmp("ivyKinect Gesture=ScrollUp", argv[i]) == 0)
		  emit scrollUpgesture();
	  else if (strcmp("ivyKinect Gesture=ScrollDown", argv[i]) == 0)
		  emit scrollDownGesture();
	  else if (strcmp("ivyKinect Gesture=Close", argv[i]) == 0)
		  emit closeGesture();
	}
}

void IvyBinder::OnApplicationConnected(IvyApplication *app) {
	const char *appname;
	const char *host;
	appname = app->GetName();
	host = app->GetHost();

	qDebug() << appname << " disconnected from " << host;
}

void IvyBinder::OnApplicationDisconnected(IvyApplication *app) {
	const char *appname;
	const char *host;
	appname = app->GetName ();
	host = app->GetHost();

	qDebug() << appname << " disconnected from " << host;
}

void IvyBinder::OnApplicationCongestion(IvyApplication *app) {
	qDebug() << "Ivy Congestion notififation";
}
void IvyBinder::OnApplicationDecongestion(IvyApplication *app) {
	qDebug() << "Ivy Decongestion notififation";
}
void IvyBinder::OnApplicationFifoFull(IvyApplication *app) {
	qDebug() << "Ivy FIFO Full  notififation : MESSAGE WILL BE LOST";
}
