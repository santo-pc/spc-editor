/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of STANISLAW ADASZEWSKI nor the
	  names of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "qnodeseditor.h"


//#include <QGraphicsScene>
#include <qgraphicsscene.h>
//#include <QEvent>
#include <QtGui\qevent.h>
//#include <QGraphicsSceneMouseEvent>
#include <qgraphicssceneevent.h>

#include "qneport.h"
#include "qneconnection.h"
#include "qneblock.h"
#include <qmessagebox.h>
#include <iostream>
#include "QNEditorNodes.h"

#include "Form1.h"

QNodesEditor::QNodesEditor(QObject *parent) :
	QObject(parent)
{
	conn = 0;
}

void QNodesEditor::install(QGraphicsScene *s)
{
	s->installEventFilter(this);
	scene = s;
}

QGraphicsItem* QNodesEditor::itemAt(const QPointF &pos)
{
	QList<QGraphicsItem*> items = scene->items(QRectF(pos - QPointF(1,1), QSize(3,3)));

	foreach(QGraphicsItem *item, items)
		if (item->type() > QGraphicsItem::UserType)
			return item;

	return 0;
}

bool QNodesEditor::eventFilter(QObject *o, QEvent *e)
{
	QGraphicsSceneMouseEvent *me = (QGraphicsSceneMouseEvent*) e;

	switch ((int) e->type())
	{
	case QEvent::GraphicsSceneMousePress:
	{
		/*QMessageBox box;
		box.setText("In editor");
		box.exec();*/

		switch ((int) me->button())
		{
		case Qt::LeftButton:
		{
			
			QGraphicsItem *item = itemAt(me->scenePos());
			if (item && item->type() == QNEPort::Type)
			{
				conn = new QNEConnection(0);
				scene->addItem(conn);
				conn->setPort1((QNEPort*) item);
				conn->setPos1(item->scenePos());
				conn->setPos2(me->scenePos());
				conn->updatePath();

				return true;
			} else if (item && item->type() == QNEBlock::Type)
			{
				/* if (selBlock)
					selBlock->setSelected(); */
				// selBlock = (QNEBlock*) item;
			}
			break;
		}
		case Qt::RightButton:
		{
			// si esta pulsado click derecho
			if (me->modifiers() & Qt::ControlModifier)
			{
				QGraphicsItem *item = itemAt(me->scenePos());
			
				if (item && (item->type() == QNEBlock::Type))
				{
					QNMainNode * node = NULL;
					try
					{
						printf("Crash1\n");
						node = dynamic_cast<QNMainNode*>(item);
						printf("Crash2\n");
					}
					catch (int e)
					{
						printf("Cast failed\n");
					}

					// Solo se borran los que no son Main Node
					if (!node)						
						{
							printf("Crash11\n");
							// no se borra 
							//emit connectionChanged();
							delete item;	
							item = NULL;
							printf("Crash12\n");
							
						}
				}
				printf("Crash13\n");
				if (item && (item->type() == QNEConnection::Type))
				{
					emit connectionChanged();  // Se notifica el cambio
					delete item;
					
				}
				printf("Crash14\n");
				// if (selBlock == (QNEBlock*) item)
					// selBlock = 0;
			}
			break;
		}
		}
	}
	case QEvent::GraphicsSceneMouseMove:
	{
		if (conn)
		{
			conn->setPos2(me->scenePos());
			conn->updatePath();
			return true;
		}
		break;
	}
	case QEvent::GraphicsSceneMouseRelease:
	{
		if (conn && me->button() == Qt::LeftButton)
		{
			QGraphicsItem *item = itemAt(me->scenePos());
			if (item && item->type() == QNEPort::Type)
			{
				QNEPort *port1 = conn->port1();
				QNEPort *port2 = (QNEPort*) item;

				if (port1->block() != port2->block() && port1->isOutput() != port2->isOutput() && !port1->isConnected(port2)
					&& IsLegalConnection(port1, port2))
				{
					
						conn->setPos2(port2->scenePos());
						conn->setPort2(port2);
						conn->updatePath();
						conn = 0;
						emit connectionChanged(); 
						return true;
					

				}
			}

			delete conn;
			conn = 0;
			return true;
		}
		break;
	}
	}
	return QObject::eventFilter(o, e);
}


bool QNodesEditor::IsLegalConnection(QNEPort * port1, QNEPort * port2)
{
	// Comprobar por tipos de nodos para conectar
	// Si port 1 es el output
	if (port1->isOutput())
	{
		if (!port2->acceptVector4Node && port1->portName() == "")
		{
			QMessageBox box;
			box.setText("El tipo que intenta conectar solo admite valores no compuestos como vectores, prueba conectar con tipos float o componentes de un vector como R,G o B");
			box.exec();
			return false;
		}
	}
	else // Misma pregunta pero en sentido contrario
	{
		if (port2->isOutput())
			if (!port1->acceptVector4Node && port2->portName() == "")
			{
				QMessageBox box;
				box.setText("El tipo que intenta conectar solo admite valores no compuestos como vectores, prueba conectar con tipos float o componentes de un vector como R,G o B");
				box.exec();
				return false;
				
			}
	}

	// Comprobar por numero de entradas
	if (port1->isOutput())
	{
		if (port2->connections().count() > 0) // el input tiene  ya tiene una conexion
		{
			QMessageBox box;
			box.setText("Este input ya tiene un valor establecido, pruebe eliminarlo para crear una nueva conexion");
			box.exec();
			return false;
		}
			
	}
	else // Misma pregunta pero en sentido contrario
	{
		if (port2->isOutput())
		{
			if (port1->connections().count() > 1)
			{
				QMessageBox box;
				box.setText("Este input ya tiene un valor establecido, pruebe eliminarlo para crear una nueva conexion");
				box.exec();
				return false;
			}
		}
	}


	return true;
}


void QNodesEditor::save(QDataStream &ds)
{
	foreach(QGraphicsItem *item, scene->items())
		if (item->type() == QNEBlock::Type)
		{
			ds << item->type();
			((QNEBlock*) item)->save(ds);
		}

	foreach(QGraphicsItem *item, scene->items())
		if (item->type() == QNEConnection::Type)
		{
			ds << item->type();
			((QNEConnection*) item)->save(ds);
		}
}

void QNodesEditor::load(QDataStream &ds)
{
	scene->clear();

	QMap<quint64, QNEPort*> portMap;

	while (!ds.atEnd())
	{
		int type;
		ds >> type;
		if (type == QNEBlock::Type)
		{
			QNEBlock *block = new QNEBlock(0);
			scene->addItem(block);
			block->load(ds, portMap);
		} else if (type == QNEConnection::Type)
		{
			QNEConnection *conn = new QNEConnection(0);
			scene->addItem(conn);
			conn->load(ds, portMap);
		}
	}
}
