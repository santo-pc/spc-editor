#pragma once
#include "qneblock.h"

/*
	HERE ARE DECLARED ALL THE NODES THAT COMPOUND THE 
	NODE-BASED MATERIAL EDITOR.

*/

/************************** MAIN NODE **************************/
class QNMainNode : public QNEBlock
{
public:
	QNEPort * ColorBasePort;
	QNEPort * SpecularPort;
	QNEPort * NormalPort;
	QNEPort * AlphaPort;

	QNMainNode(QGraphicsItem *parent = 0);
	~QNMainNode();
	void Init();
	void Resolve();
};


/************************** CONST VALUE NODE **************************/
class QNConstFloatNode : public QNEBlock
{
public:
	QNConstFloatNode(QGraphicsItem *parent = 0);
	~QNConstFloatNode();
	void Init();
	void Resolve(){};
};

/************************** VECTOR 2 NODE **************************/
class QNVector2DNode : public QNEBlock
{
public:
	QNVector2DNode(QGraphicsItem *parent = 0);
	~QNVector2DNode();
	void Init();
	void Resolve(){};
};

/************************** VECTOR 3 NODE **************************/
class QNVector3DNode : public QNEBlock
{
	public:
		QNVector3DNode(QGraphicsItem *parent = 0);
		~QNVector3DNode();
		void Init();
		void Resolve(){};
};

/************************** VECTOR 4 NODE **************************/
class QNVector4DNode : public QNEBlock
{
public:
	QNVector4DNode(QGraphicsItem *parent = 0);
	~QNVector4DNode();
	void Init();
	void Resolve(){};
};


/************************** TEXTURE NODE **************************/
class QNTextureNode : public QNEBlock
{
public:
	QNTextureNode(QGraphicsItem *parent = 0);
	~QNTextureNode();
	void Init();
	void Resolve(){};
};

/************************** ADD **************************/
class QNAddNode : public QNEBlock
{
public:
	QNAddNode(QGraphicsItem *parent = 0);
	~QNAddNode();
	void Init();
	void Resolve(){};
};

/************************** SUBTRACT **************************/
class QNSubtractNode : public QNEBlock
{
public:
	QNSubtractNode(QGraphicsItem *parent = 0);
	~QNSubtractNode();
	void Init();
	void Resolve(){};
};

/************************** MULTIPLY **************************/
class QNMultiplyNode : public QNEBlock
{
public:
	QNMultiplyNode(QGraphicsItem *parent = 0);
	~QNMultiplyNode();
	void Init();
	void Resolve(){};
};

/************************** POWER **************************/
class QNPowerNode : public QNEBlock
{
public:
	QNPowerNode(QGraphicsItem *parent = 0);
	~QNPowerNode();
	void Init();
	void Resolve(){};
};

/************************** SQRT **************************/
class QNSqrtNode : public QNEBlock
{
public:
	QNSqrtNode(QGraphicsItem *parent = 0);
	~QNSqrtNode();
	void Init();
	void Resolve(){};
};

/************************** LOG **************************/
class QNLogNode : public QNEBlock
{
public:
	QNLogNode(QGraphicsItem *parent = 0);
	~QNLogNode();
	void Init();
	void Resolve(){};
};

/************************** MIN **************************/
class QNMinNode : public QNEBlock
{
public:
	QNMinNode(QGraphicsItem *parent = 0);
	~QNMinNode();
	void Init();
	void Resolve(){};
};
	
/************************** MAX **************************/
class QNMaxNode : public QNEBlock
{
public:
	QNMaxNode(QGraphicsItem *parent = 0);
	~QNMaxNode();
	void Init();
	void Resolve(){};
};

/************************** ABS **************************/
class QNAbsNode : public QNEBlock
{
public:
	QNAbsNode(QGraphicsItem *parent = 0);
	~QNAbsNode();
	void Init();
	void Resolve(){};
};

/************************** SIGN **************************/
class QNSignNode : public QNEBlock
{
public:
	QNSignNode(QGraphicsItem *parent = 0);
	~QNSignNode();
	void Init();
	void Resolve(){};
};

/************************** MOD **************************/
class QNModNode : public QNEBlock
{
public:
	QNModNode(QGraphicsItem *parent = 0);
	~QNModNode();
	void Init();
	void Resolve(){};
};

/************************** CLAMP **************************/
class QNClampNode : public QNEBlock
{
public:
	QNClampNode(QGraphicsItem *parent = 0);
	~QNClampNode();
	void Init();
	void Resolve(){};
};

/************************** LERP **************************/
class QNLerpNode : public QNEBlock
{
public:
	QNLerpNode(QGraphicsItem *parent = 0);
	~QNLerpNode();
	void Init();
	void Resolve(){};
};
