#pragma once
#include "qneblock.h"
#include "glm\glm.hpp"
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qlabel.h>

class Form1;

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
private:
	QTextEdit * valueTextEdit;

public:
	QNEPort * ColorBasePort;
	QNEPort * SpecularPort;
	QNEPort * NormalPort;
	QNEPort * AlphaPort;

	QNMainNode(QGraphicsItem *parent = 0);
	~QNMainNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};


/************************** CONST VALUE NODE **************************/
class QNConstFloatNode : public QNEBlock
{
private:
	float value = 0.3;
	
	QTextEdit * descTextEdit;
	QTextEdit * valueTextEdit;	


public:
	QNConstFloatNode(QGraphicsItem *parent = 0);
	~QNConstFloatNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** VECTOR 2 NODE **************************/
class QNVector2DNode : public QNEBlock
{
private:
	glm::vec2 value;
	QTextEdit * rValueTextEdit;
	QTextEdit * gValueTextEdit;
	
public:
	QNVector2DNode(QGraphicsItem *parent = 0);
	~QNVector2DNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** VECTOR 3 NODE **************************/
class QNVector3DNode : public QNEBlock
{
	private:
		glm::vec3 value;
		QTextEdit * rValueTextEdit;
		QTextEdit * gValueTextEdit;
		QTextEdit * bValueTextEdit;

	public:
		QNVector3DNode(QGraphicsItem *parent = 0);
		~QNVector3DNode();
		void Init();
		std::string Resolve();
		QGridLayout *  GetPropertiesForm();
		void HandleLostFocusMembers();
};

/************************** VECTOR 4 NODE **************************/
class QNVector4DNode : public QNEBlock
{
	private:
		glm::vec4 value;
		QTextEdit * rValueTextEdit;
		QTextEdit * gValueTextEdit;
		QTextEdit * bValueTextEdit;
		QTextEdit * aValueTextEdit;

public:
	QNVector4DNode(QGraphicsItem *parent = 0);
	~QNVector4DNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};


/************************** TEXTURE NODE **************************/
class QNTextureNode : public QNEBlock
{
public:
	QNTextureNode(QGraphicsItem *parent = 0);
	~QNTextureNode();
	void Init();
	std::string Resolve(){ return ""; };
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** ADD **************************/
class QNAddNode : public QNEBlock
{
private:
	QNEPort * APort;
	QNEPort * BPort;
public:
	QNAddNode(QGraphicsItem *parent = 0);
	~QNAddNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** SUBTRACT **************************/
class QNSubtractNode : public QNEBlock
{
private:
	QNEPort * APort;
	QNEPort * BPort;
public:
	QNSubtractNode(QGraphicsItem *parent = 0);
	~QNSubtractNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** MULTIPLY **************************/
class QNMultiplyNode : public QNEBlock
{
private:
	QNEPort * APort;
	QNEPort * BPort;
public:
	QNMultiplyNode(QGraphicsItem *parent = 0);
	~QNMultiplyNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** POWER **************************/
class QNPowerNode : public QNEBlock
{
private:
	QNEPort * ValuePort;
	QNEPort * ExpPort;
public:
	QNPowerNode(QGraphicsItem *parent = 0);
	~QNPowerNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** SQRT **************************/
class QNSqrtNode : public QNEBlock
{
private:
	QNEPort * ValPort;
public:
	QNSqrtNode(QGraphicsItem *parent = 0);
	~QNSqrtNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** LOG **************************/
class QNLogNode : public QNEBlock
{
private:
	QNEPort * ValPort;
public:
	QNLogNode(QGraphicsItem *parent = 0);
	~QNLogNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** MIN **************************/
class QNMinNode : public QNEBlock
{
private:
	QNEPort * APort;
	QNEPort * BPort;
public:
	QNMinNode(QGraphicsItem *parent = 0);
	~QNMinNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};
	
/************************** MAX **************************/
class QNMaxNode : public QNEBlock
{
private:
	QNEPort * APort;
	QNEPort * BPort;
public:
	QNMaxNode(QGraphicsItem *parent = 0);
	~QNMaxNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** ABS **************************/
class QNAbsNode : public QNEBlock
{
private:
	QNEPort * ValPort;
public:
	QNAbsNode(QGraphicsItem *parent = 0);
	~QNAbsNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** SIGN **************************/
class QNSignNode : public QNEBlock
{
private:
	QNEPort * ValPort;
public:
	QNSignNode(QGraphicsItem *parent = 0);
	~QNSignNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** MOD **************************/
class QNModNode : public QNEBlock
{
private:
	QNEPort * APort;
	QNEPort * BPort;
public:
	QNModNode(QGraphicsItem *parent = 0);
	~QNModNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** CLAMP **************************/
class QNClampNode : public QNEBlock
{
private:
	QNEPort * ValPort;
	QNEPort * MinPort;
	QNEPort * MaxPort;
public:
	QNClampNode(QGraphicsItem *parent = 0);
	~QNClampNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};

/************************** LERP **************************/
class QNLerpNode : public QNEBlock
{
private:
	QNEPort * ValXPort;
	QNEPort * ValYPort;
	QNEPort * TPort;
public:
	QNLerpNode(QGraphicsItem *parent = 0);
	~QNLerpNode();
	void Init();
	std::string Resolve();
	QGridLayout *  GetPropertiesForm();
	void HandleLostFocusMembers();
};
