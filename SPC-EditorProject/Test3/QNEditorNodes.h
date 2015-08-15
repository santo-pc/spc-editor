#pragma once
#include "qneblock.h"

/*
	HERE ARE DECLARED ALL THE NODES THAT COMPOUND THE 
	NODE-BASED MATERIAL EDITOR.

*/

class SPNodesManager
{
	private:
	public:

};


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
	std::string Resolve();
};


/************************** CONST VALUE NODE **************************/
class QNConstFloatNode : public QNEBlock
{
public:
	QNConstFloatNode(QGraphicsItem *parent = 0);
	~QNConstFloatNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** VECTOR 2 NODE **************************/
class QNVector2DNode : public QNEBlock
{
public:
	QNVector2DNode(QGraphicsItem *parent = 0);
	~QNVector2DNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** VECTOR 3 NODE **************************/
class QNVector3DNode : public QNEBlock
{
	public:
		QNVector3DNode(QGraphicsItem *parent = 0);
		~QNVector3DNode();
		void Init();
		std::string Resolve(){ return ""; };
};

/************************** VECTOR 4 NODE **************************/
class QNVector4DNode : public QNEBlock
{
public:
	QNVector4DNode(QGraphicsItem *parent = 0);
	~QNVector4DNode();
	void Init();
	std::string Resolve(){ return ""; };
};


/************************** TEXTURE NODE **************************/
class QNTextureNode : public QNEBlock
{
public:
	QNTextureNode(QGraphicsItem *parent = 0);
	~QNTextureNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** ADD **************************/
class QNAddNode : public QNEBlock
{
public:
	QNAddNode(QGraphicsItem *parent = 0);
	~QNAddNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** SUBTRACT **************************/
class QNSubtractNode : public QNEBlock
{
public:
	QNSubtractNode(QGraphicsItem *parent = 0);
	~QNSubtractNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** MULTIPLY **************************/
class QNMultiplyNode : public QNEBlock
{
public:
	QNMultiplyNode(QGraphicsItem *parent = 0);
	~QNMultiplyNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** POWER **************************/
class QNPowerNode : public QNEBlock
{
public:
	QNPowerNode(QGraphicsItem *parent = 0);
	~QNPowerNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** SQRT **************************/
class QNSqrtNode : public QNEBlock
{
public:
	QNSqrtNode(QGraphicsItem *parent = 0);
	~QNSqrtNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** LOG **************************/
class QNLogNode : public QNEBlock
{
public:
	QNLogNode(QGraphicsItem *parent = 0);
	~QNLogNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** MIN **************************/
class QNMinNode : public QNEBlock
{
public:
	QNMinNode(QGraphicsItem *parent = 0);
	~QNMinNode();
	void Init();
	std::string Resolve(){ return ""; };
};
	
/************************** MAX **************************/
class QNMaxNode : public QNEBlock
{
public:
	QNMaxNode(QGraphicsItem *parent = 0);
	~QNMaxNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** ABS **************************/
class QNAbsNode : public QNEBlock
{
public:
	QNAbsNode(QGraphicsItem *parent = 0);
	~QNAbsNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** SIGN **************************/
class QNSignNode : public QNEBlock
{
public:
	QNSignNode(QGraphicsItem *parent = 0);
	~QNSignNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** MOD **************************/
class QNModNode : public QNEBlock
{
public:
	QNModNode(QGraphicsItem *parent = 0);
	~QNModNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** CLAMP **************************/
class QNClampNode : public QNEBlock
{
public:
	QNClampNode(QGraphicsItem *parent = 0);
	~QNClampNode();
	void Init();
	std::string Resolve(){ return ""; };
};

/************************** LERP **************************/
class QNLerpNode : public QNEBlock
{
public:
	QNLerpNode(QGraphicsItem *parent = 0);
	~QNLerpNode();
	void Init();
	std::string Resolve(){ return ""; };
};
