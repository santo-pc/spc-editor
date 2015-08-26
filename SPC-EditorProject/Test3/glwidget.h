#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>
#include <QtWidgets\qopenglwidget.h>
#include <GL/glew.h>
#include <QtOpenGL\qglfunctions.h>
#include <GL/glew.h>
#include <QtGui\qopenglvertexarrayobject.h>
#include <GL/glew.h>
#include <QtGui\qopenglbuffer.h>
#include <GL/glew.h>
#include <QtGui\qmatrix4x4.h>
#include <GL/glew.h>
#include "logo.h"
#include "Mesh.h"
#include "Shader.h"
#include <qevent.h>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;
	void SetLightColorR(float value);
	void SetLightColorG(float value);
	void SetLightColorB(float value);
	void SetDiffuseIntensity(float value);
	void SetAmbientIntensity(float value);


public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void cleanup();
	void RebuildShader(const std::string & fragment);

	void ActiveMeshCube();
	void ActiveMeshSphere();
	void ActiveMeshCylinder();
	void ActiveMeshTeaPot();
	void ResetScene();


signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);


protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void resizeGL(int width, int height) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void wheelEvent(QWheelEvent * event) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent * event)Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent * event)Q_DECL_OVERRIDE;

	


private:
	glm::vec3 initialCameraPos;
	glm::vec3 initialCameraTarget;
	glm::vec3 lightColor = glm::vec3(0.7, 0.7, 0.7);
	float diffuseIntensity = 0.5;
	float ambientIntensity = 0.52;
	float  fov;
	float aspecRatio;
	
	Transform transform; 
	Camera camera;
	float rotZ = 0.0;
	void setupVertexAttribs();
	QPoint m_lastPos;
	int m_xRot;
	int m_yRot;
	int m_zRot;
	float aux = 0;
	

	Mesh * mesh = new Mesh();
	Mesh * meshCube = new Mesh();
	Mesh * meshSphere = new Mesh();
	Mesh * meshCylinder = new Mesh();
	Mesh * meshTeapot = new Mesh();
	Shader * shader;
	Shader * errorShader;
	
};

#endif
