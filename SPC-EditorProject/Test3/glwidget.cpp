#include "glwidget.h"
#include <QtGui\qevent.h>
#include <QtGui\qopenglshaderprogram.h>
#include <QtCore\qcoreapplication.h>
#include <math.h>
#include <iostream>
#include "Mesh.h"
#include "qmessagebox.h"
#include "ShaderComposer.h"
#include "TextureManager.h"
#include "NodesManager.h"
#include "QNEditorNodes.h"
GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent),//,
/*  m_xRot(0),
  m_yRot(0),
  m_zRot(0),
  m_program(0)*/
  camera(glm::vec3(), 0, 0, 0, 0)
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
	qNormalizeAngle(angle);
	if (angle != m_xRot)
	{
		m_xRot = angle;
		glm::vec3 vecRot = glm::vec3(angle, transform.GetRot()->y, transform.GetRot()->z);
		transform.SetRot(vecRot);
		emit xRotationChanged(angle);
		update();
	}
}

void GLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_yRot) 
	{
		m_yRot = angle;
		glm::vec3 vecRot = glm::vec3(transform.GetRot()->x, angle, transform.GetRot()->z);
		transform.SetRot(vecRot);
		emit yRotationChanged(angle);
		update();
	}
}

void GLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_zRot) 
	{
		m_zRot = angle;
		glm::vec3 vecRot = glm::vec3(transform.GetRot()->x, transform.GetRot()->y, angle);
		transform.SetRot(vecRot);
		emit zRotationChanged(angle);
		update();
	}
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
	TEXTURE_MANAGER->SetStandarMode();

	/*GLOBAL_CONTAIER->GlobalErrorShader = new Shader("../../Resources/Shaders/errorShader");*/
	//mesh->LoadMesh("../../Resources/Models/sphere.obj");
	mesh->LoadMesh("../../Resources/Models/cruz.obj");
	probar finalmente lo hecho con los nodos a ver

	
	initialCameraPos = glm::vec3(0.0, 0.0, -6.0);
	fov = 80;
	aspecRatio = 16 / 9;

	camera = Camera(initialCameraPos, fov, aspecRatio, 0.1, 1000);


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

	
	GLOBAL_CONTAIER->GlobalShader->Update(transform, camera);
	GLOBAL_CONTAIER->GlobalShader->Bind();
	TEXTURE_MANAGER->DrawTextures1();
	TEXTURE_MANAGER->DrawTextures2();
	
	/*QMessageBox box; 
	box.setText("ShaderCreado"); 
	box.exec();*/

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
	/*QMessageBox msgBox;
	msgBox.setText("MoousePress");
	msgBox.exec();*/
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();
	int speedFactor = 4;

	if (event->buttons() & Qt::LeftButton) 
	{
		setXRotation(m_xRot - speedFactor * dy);
		setYRotation(m_yRot - speedFactor * dx);
	} 
	else if (event->buttons() & Qt::RightButton) 
	{
		//setXRotation(m_xRot + speedFactor * dy);
		//setZRotation(m_zRot + speedFactor * dx);
		if (abs(dy) > 50)  dy = glm::sign(dy) * 1;

		float value = camera.GetPos().z + 0.02 * dy;
		
		/*if (abs(value) >= 3.0)
			value = camera.GetPos().z;*/

		//cout << "Value = " << value << endl;
		camera.SetPos(glm::vec3(camera.GetPos().x, camera.GetPos().y, value));
		update();
	}
	cout << "DX = "<< dx << endl;
	m_lastPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent * event)
{
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;

	camera.SetFov(camera.GetFov() + numSteps);
	update();
	cout << "Num Steps= " << numSteps << endl;
	

	event->accept();
}

void GLWidget::leaveEvent(QEvent * event)
{
	m_lastPos = QPoint(0, 0);
}


void GLWidget::RebuildShader(const std::string & fragment)
{
	
	QString fragmentCode(fragment.c_str());

	delete GLOBAL_CONTAIER->GlobalShader;

	GLOBAL_CONTAIER->GlobalShader = new Shader(fragment, true);

	int unitCounter = 0;
	
	for (std::map<int, string>::iterator it = SHADER_COMPOSER->listNodeMemberNamesStringTextures.begin();
		it != SHADER_COMPOSER->listNodeMemberNamesStringTextures.end(); ++it)
	{
		
		QNTextureNode * nodeTexture = dynamic_cast<QNTextureNode*>(MANAGER->GetNodeFromID((*it).first));
		
		if (nodeTexture)
			TEXTURE_MANAGER->AddTexture(unitCounter, unitCounter, (*it).second, nodeTexture->path);
		
		unitCounter++;
	}

	

}


