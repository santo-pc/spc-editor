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

public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void cleanup();
	void RebuildShader(const std::string & fragment);


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

private:
	glm::vec3 initialCameraPos;
	glm::vec3 initialCameraTarget;
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

	/*bool m_core;
	
	
	Logo m_logo;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_logoVbo;
	QOpenGLShaderProgram *m_program;
	int m_projMatrixLoc;
	int m_mvMatrixLoc;
	int m_normalMatrixLoc;
	int m_lightPosLoc;
	QMatrix4x4 m_proj;
	QMatrix4x4 m_camera;
	QMatrix4x4 m_world;
	bool m_transparent;*/

	Mesh * mesh = new Mesh();
	Shader * shader;
	Shader * errorShader;
	
};

#endif
