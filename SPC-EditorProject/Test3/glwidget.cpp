#include "glwidget.h"
#include <QtGui\qevent.h>
#include <QtGui\qopenglshaderprogram.h>
#include <QtCore\qcoreapplication.h>
#include <math.h>
#include <iostream>
#include "Mesh.h"
#include "qmessagebox.h"



GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)//,
	/*  m_xRot(0),
	  m_yRot(0),
	  m_zRot(0),
	  m_program(0)*/
{
	//m_core = QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"));
	//// --transparent causes the clear color to be transparent. Therefore, on systems that
	//// support it, the widget will become transparent apart from the logo.
	//m_transparent = QCoreApplication::arguments().contains(QStringLiteral("--transparent"));
	/*if (m_transparent)
		setAttribute(Qt::WA_TranslucentBackground);*/





}

GLWidget::~GLWidget()
{
	cleanup();
}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
	return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360 * 16)
		angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
	/*qNormalizeAngle(angle);
	if (angle != m_xRot) {
		m_xRot = angle;
		emit xRotationChanged(angle);
		update();
	}*/
}

void GLWidget::setYRotation(int angle)
{
	/*qNormalizeAngle(angle);
	if (angle != m_yRot) {
		m_yRot = angle;
		emit yRotationChanged(angle);
		update();
	}*/
}

void GLWidget::setZRotation(int angle)
{
	/*qNormalizeAngle(angle);
	if (angle != m_zRot) {
		m_zRot = angle;
		emit zRotationChanged(angle);
		update();
	}*/
}

void GLWidget::cleanup()
{
	/*makeCurrent();
	m_logoVbo.destroy();
	delete m_program;
	m_program = 0;
	doneCurrent();*/
}

void GLWidget::initializeGL()
{
	// In this example the widget's corresponding top-level window can change
	// several times during the widget's lifetime. Whenever this happens, the
	// QOpenGLWidget's associated context is destroyed and a new one is created.
	// Therefore we have to be prepared to clean up the resources on the
	// aboutToBeDestroyed() signal, instead of the destructor. The emission of
	// the signal will be followed by an invocation of initializeGL() where we
	// can recreate all resources.
	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

	initializeOpenGLFunctions();
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize" << std::endl;
		std::cerr << "Error message:  " << glewGetErrorString(status) << std::endl;
	}
	else
		std::cout << "Glew initialized successfully" << std::endl;

	printf("\nOpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	GLOBAL_CONTAIER->GlobalShader = new Shader("../../Resources/Shaders/phongNormalShader");
	GLOBAL_CONTAIER->GlobalErrorShader = new Shader("../../Resources/Shaders/errorShader");
	mesh->LoadMesh("../../Resources/Models/sphere.obj");
	
	


}

void GLWidget::setupVertexAttribs()
{

}

void GLWidget::paintGL()
{
	std::cout << "Init Paint" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	rotZ += 30.f;
	transform.SetRot(glm::vec3(0.0, 0.0, rotZ));
	GLOBAL_CONTAIER->GlobalShader->Update(transform, Camera(glm::vec3(0.0, 0.0, -6.0), 80, 16 / 9, 0.1, 1000));
	GLOBAL_CONTAIER->GlobalShader->Bind();
	mesh->Render();
	std::cout << "End Paint" << std::endl;
}

void GLWidget::resizeGL(int w, int h)
{
	//m_proj.setToIdentity();
	//m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	//m_lastPos = event->pos();
	QMessageBox msgBox;
	msgBox.setText("MoousePress");
	msgBox.exec();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	/*int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(m_xRot + 8 * dy);
		setYRotation(m_yRot + 8 * dx);
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(m_xRot + 8 * dy);
		setZRotation(m_zRot + 8 * dx);
	}
	m_lastPos = event->pos();*/
}


void GLWidget::RebuildShader(const std::string & fragment)
{
	
	QMessageBox msgBox;

	QString fragmentCode(fragment.c_str());

	
	msgBox.setText("Borrando");
	msgBox.exec();

	delete GLOBAL_CONTAIER->GlobalShader;


	/*msgBox.setText("Creando");
	msgBox.exec();
*/
	cout << "Pintando fragment: " << endl;
	cout << fragment << endl;


	cout << "Creando Shader desde widget: " << endl;
	GLOBAL_CONTAIER->GlobalShader = new Shader(fragment, true);
	

}


