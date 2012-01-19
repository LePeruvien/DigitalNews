#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "IvyLoop.hpp"
#include <Ivy/ivydebug.h>

#include <QtCore/QSocketNotifier>
#include <QtCore/QDebug>

IvyLoop::IvyLoop (struct _channel *chan, QObject *parent): QObject(parent),
							   channel (chan)
{
  id_read = new QSocketNotifier(channel->fd, QSocketNotifier::Read, this);
  id_read->setEnabled(false);
  connect(id_read, SIGNAL(activated(int)), SLOT(ivyRead(int)));

  id_delete = new QSocketNotifier(channel->fd, QSocketNotifier::Exception, this);
  id_delete->setEnabled(false);
  connect(id_delete, SIGNAL(activated(int)), SLOT(ivyDelete(int)));

  id_write = new QSocketNotifier(channel->fd, QSocketNotifier::Write, this);
  id_write->setEnabled(false);
  connect(id_write, SIGNAL(activated(int)), SLOT(ivyWrite(int)));
}

IvyLoop::~IvyLoop()
{
  //pas besoin de detruire les objets enfants, qt s'en charge
}


void IvyLoop::startNotifiersRead()
{
  id_read->setEnabled(true);
  id_delete->setEnabled(true);
}

void IvyLoop::startNotifiersWrite()
{
  printf ("DEBUG>  IvyLoop::startNotifiersWrite\n");
  id_write->setEnabled(true);
}

void IvyLoop::removeNotifiersWrite()
{
  id_write->setEnabled(false);
}

void IvyLoop::removeNotifiersRead()
{
  id_read->setEnabled(false);
  id_delete->setEnabled(false);
}


void IvyLoop::ivyRead (int fd)
{
  //TRACE("Handle Channel read %d\n",fd );
  (*channel->handle_read)(channel,fd,channel->data);
	qDebug() << "blabla: " << channel->data << " - " << channel->fd << " - " << channel->ivyQt << " - " << channel->ivyQt->userData(channel->fd);
}

void IvyLoop::ivyWrite (int fd)
{
  printf ("DEBUG>  IvyLoop::ivyWrite\n");
  //  TRACE("Handle Channel write %d\n",fd );
  (*channel->handle_write)(channel,fd,channel->data);
}

void IvyLoop::ivyDelete (int fd)
{
  //  TRACE("Handle Channel delete %d\n",*source );
  (*channel->handle_delete)(channel->data);
}



void IvyChannelInit(void)
{
}

void IvyChannelRemove( Channel channel )
{

  if ( channel->handle_delete )
	(*channel->handle_delete)( channel->data );
  channel->ivyQt->removeNotifiersRead();
}



Channel IvyChannelAdd(IVY_HANDLE fd, void *data,
			  ChannelHandleDelete handle_delete,
			  ChannelHandleRead handle_read,
			  ChannelHandleWrite handle_write
			  )
{
  Channel channel;

  channel = (Channel) malloc (sizeof (struct _channel));
  if ( !channel ) {
	fprintf(stderr,"NOK Memory Alloc Error\n");
	exit(0);
  }

  channel->handle_delete = handle_delete;
  channel->handle_read = handle_read;
  channel->handle_write = handle_write;
  channel->data = data;
  channel->fd = fd;
  channel->ivyQt =  new IvyLoop(channel);
  channel->ivyQt->startNotifiersRead();

  return channel;
}




void IvyChannelAddWritableEvent(Channel channel)
{
   channel->ivyQt->startNotifiersWrite ();
}

void IvyChannelClearWritableEvent(Channel channel)
{
   channel->ivyQt->removeNotifiersWrite ();
}


void
IvyChannelStop ()
{
  // not yet implemented
}
