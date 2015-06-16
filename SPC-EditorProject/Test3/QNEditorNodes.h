#pragma once
#include "qneblock.h"

/*
	HERE ARE DECLARED ALL THE NODES THAT COMPOUND THE 
	NODE-BASED MATERIAL EDITOR.

*/

/************************** CONST VALUE NODE **************************/
class QNConstFloatNode : public QNEBlock
{
public:
	QNConstFloatNode(QGraphicsItem *parent = 0);
	~QNConstFloatNode();
	void Init();
};

/************************** VECTOR 2 NODE **************************/
class QNVector2DNode : public QNEBlock
{
public:
	QNVector2DNode(QGraphicsItem *parent = 0);
	~QNVector2DNode();
	void Init();
};

/************************** VECTOR 3 NODE **************************/
class QNVector3DNode : public QNEBlock
{
	public:
		QNVector3DNode(QGraphicsItem *parent = 0);
		~QNVector3DNode();
		void Init();
};

/************************** VECTOR 4 NODE **************************/
class QNVector4DNode : public QNEBlock
{
public:
	QNVector4DNode(QGraphicsItem *parent = 0);
	~QNVector4DNode();
	void Init();
};


/************************** TEXTURE NODE **************************/
class QNTextureNode : public QNEBlock
{
public:
	QNTextureNode(QGraphicsItem *parent = 0);
	~QNTextureNode();
	void Init();
};

/************************** ADD **************************/
class QNAddNode : public QNEBlock
{
public:
	QNAddNode(QGraphicsItem *parent = 0);
	~QNAddNode();
	void Init();
};

/************************** SUBTRACT **************************/
class QNSubtractNode : public QNEBlock
{
public:
	QNSubtractNode(QGraphicsItem *parent = 0);
	~QNSubtractNode();
	void Init();
};

/************************** MULTIPLY **************************/
class QNMultiplyNode : public QNEBlock
{
public:
	QNMultiplyNode(QGraphicsItem *parent = 0);
	~QNMultiplyNode();
	void Init();
};

/************************** POWER **************************/
class QNPowerNode : public QNEBlock
{
public:
	QNPowerNode(QGraphicsItem *parent = 0);
	~QNPowerNode();
	void Init();
};

/************************** SQRT **************************/
class QNSqrtNode : public QNEBlock
{
public:
	QNSqrtNode(QGraphicsItem *parent = 0);
	~QNSqrtNode();
	void Init();
};

/************************** LOG **************************/
class QNLogNode : public QNEBlock
{
public:
	QNLogNode(QGraphicsItem *parent = 0);
	~QNLogNode();
	void Init();
};

/************************** MIN **************************/
class QNMinNode : public QNEBlock
{
public:
	QNMinNode(QGraphicsItem *parent = 0);
	~QNMinNode();
	void Init();
};
	
/************************** MAX **************************/
class QNMaxNode : public QNEBlock
{
public:
	QNMaxNode(QGraphicsItem *parent = 0);
	~QNMaxNode();
	void Init();
};

/************************** ABS **************************/
class QNAbsNode : public QNEBlock
{
public:
	QNAbsNode(QGraphicsItem *parent = 0);
	~QNAbsNode();
	void Init();
};

/************************** SIGN **************************/
class QNSignNode : public QNEBlock
{
public:
	QNSignNode(QGraphicsItem *parent = 0);
	~QNSignNode();
	void Init();
};

/************************** MOD **************************/
class QNModNode : public QNEBlock
{
public:
	QNModNode(QGraphicsItem *parent = 0);
	~QNModNode();
	void Init();
};

/************************** CLAMP **************************/
class QNClampNode : public QNEBlock
{
public:
	QNClampNode(QGraphicsItem *parent = 0);
	~QNClampNode();
	void Init();
};

/************************** LERP **************************/
class QNLerpNode : public QNEBlock
{
public:
	QNLerpNode(QGraphicsItem *parent = 0);
	~QNLerpNode();
	void Init();
};
