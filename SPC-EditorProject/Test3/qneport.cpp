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

#include "qneport.h"

//#include <QGraphicsScene>
#include <qgraphicsscene.h>
//#include <QFontMetrics>
#include <qfontmetrics.h>

//#include <QPen>
#include <qpen.h>

#include "qneconnection.h"
#include <iostream>
#include <qmessagebox.h>

QNEPort::QNEPort(QGraphicsItem *parent, QString name):
	QGraphicsPathItem(parent)
{
	label = new QGraphicsTextItem(this);

	/*radius_ = 5;*/
	margin = 5;
	radius_ = 10.5;

	QPainterPath p;
	if (name == "R")
	{
		radius_ = 7.5;	
		setPen(QPen(QColor(191, 4, 17)));
		setBrush(QBrush(QColor(191, 4, 17))); // Fondo
	}else
	if (name == "G")
	{
		radius_ = 7.5;
		setPen(QPen(QColor(57, 191, 4)));
		setBrush(QBrush(QColor(57, 191, 4))); // Fondo
	}else
	if (name == "B")
	{
		radius_ = 7.5;
		setPen(QPen(QColor(4, 66, 191)));
		setBrush(QBrush(QColor(4, 66, 191))); // Fondo
	}else
	if (name == "A")
	{
		radius_ = 7.5;
		setPen(QPen(QColor(255, 253, 109)));
		setBrush(QBrush(QColor(255, 253, 109))); // Fondo
	}
	else
	{
		radius_ = 9.5;
		setPen(QPen(QColor(222, 222, 222)));
		setBrush(QBrush(QColor(222, 222, 222))); // Fondo
	}


	p.addEllipse(-radius_, -radius_, 2 * radius_, 2 * radius_);
	
	setPath(p);

	setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

	m_portFlags = 0;
}

QNEPort::~QNEPort()
{
	foreach(QNEConnection *conn, m_connections)
		delete conn;
}

void QNEPort::setNEBlock(QNEBlock *b)
{
	m_block = b;
}

void QNEPort::setName(const QString &n)
{
	name = n;
	label->setPlainText(n);
}

void QNEPort::setIsOutput(bool o)
{
	isOutput_ = o;
	QFont font("Arial", 12, QFont::Light, false);
	QFontMetrics fm(font);
	QRect r = fm.boundingRect(name);

	if (isOutput_)
		label->setPos(-radius_ - margin - label->boundingRect().width(), -label->boundingRect().height()/2);
	else
		label->setPos(radius_ + margin, -label->boundingRect().height()/2);
}

int QNEPort::radius()
{
	return radius_;
}

bool QNEPort::isOutput()
{
	return isOutput_;
}

QVector<QNEConnection*>& QNEPort::connections()
{
	return m_connections;
}

void QNEPort::setPortFlags(int f)
{
	/*QMessageBox box;
	box.setText("SetPortFlags");
	box.exec();
*/
	m_portFlags = f;

	if (m_portFlags & TypePort)
	{
		//QFont font("times", 12);
		QFont font("Arial", 62, QFont::Light, false);
		label->setFont(font);
		setPath(QPainterPath());

	} else 
		if (m_portFlags & NamePort)
		{
			//QFont font("times", 12);
			QFont font("Arial", 12, QFont::Bold, true);		
			label->setFont(font);
			setPath(QPainterPath());
		}
}

QNEBlock* QNEPort::block() const
{
	return m_block;
}

quint64 QNEPort::ptr()
{
	return m_ptr;
}

void QNEPort::setPtr(quint64 p)
{
	m_ptr = p;
}

bool QNEPort::isConnected(QNEPort *other)
{
	foreach(QNEConnection *conn, m_connections)
		if (conn->port1() == other || conn->port2() == other)
			return true;

	return false;
}

QVariant QNEPort::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemScenePositionHasChanged)
	{
		foreach(QNEConnection *conn, m_connections)
		{
			conn->updatePosFromPorts();
			conn->updatePath();
		}
	}
	return value;
}

void QNEPort::SetLabelColor(QColor color)
{
	//label->setDefaultTextColor(color);

}