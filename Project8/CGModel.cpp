#include "CGModel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "CGCamera.h"
#include "CGScene.h"
#include "resource.h"
#include "Circuito.h"

//
// FUNCIÓN: CGModel::initialize(int, int)
//
void CGModel::initialize(int w, int h)
{
	// Crea el programa
	program = new CGShaderProgram(IDR_SHADER1, IDR_SHADER2, -1, -1, -1);
	if (program->IsLinked() == GL_FALSE) return;

	skyboxProgram = new CGShaderProgram("shaders/VertexCube.glsl", "shaders/FragmentCube.glsl", NULL, NULL, NULL);
	if (skyboxProgram->IsLinked() == GL_FALSE) return;

	// Crea la cámara
	camera = new CGCamera();
	camera->SetMoveStep(0.2f); // Velocidad inicial

	// Posición y Dirección iniciales
	camera->SetPosition(0.0f, 2.0f, 5.0f);
	camera->SetDirection(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	// Crea la escena
	scene = new CGScene();
	skybox = new CGSkybox();

	// Asigna el viewport y el clipping volume
	resize(w, h);

	// Opciones de dibujo
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//
// FUNCIÓN: CGModel::finalize()
//
void CGModel::finalize()
{
	delete camera;
	delete scene;
	delete program;
	delete skyboxProgram;
	delete skybox;
}

//
// FUNCIÓN: CGModel::resize(int w, int h)
//
void CGModel::resize(int w, int h)
{
	double fov = glm::radians(15.0);
	double sin_fov = sin(fov);
	double cos_fov = cos(fov);
	if (h == 0) h = 1;
	GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
	GLfloat wHeight = (GLfloat)(sin_fov * 0.2 / cos_fov);
	GLfloat wWidth = wHeight * aspectRatio;

	glViewport(0, 0, w, h);
	projection = glm::frustum(-wWidth, wWidth, -wHeight, wHeight, 0.2f, 400.0f);
}

//
// FUNCIÓN: CGModel::render()
//
void CGModel::render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = camera->ViewMatrix();
	skyboxProgram->Use();
	skybox->Draw(skyboxProgram, projection, view);
	program->Use();
	scene->Draw(program, projection, view);
}

//
// FUNCIÓN: CGModel::update()
//
void CGModel::update()
{
	if (scene->miCircuito->ruta.size() < 2) return;

	
	// 1. FÍSICAS COCHE 1 (Carril Izquierdo: -0.039f)
	Circuito::Waypoint actual1 = scene->miCircuito->ruta[indiceRuta];
	Circuito::Waypoint siguiente1 = scene->miCircuito->ruta[(indiceRuta + 1) % scene->miCircuito->ruta.size()];

	float distX1 = siguiente1.x - actual1.x;
	float distZ1 = siguiente1.z - actual1.z;
	float distanciaTotal1 = sqrt(distX1 * distX1 + distZ1 * distZ1);

	if (distanciaTotal1 > 0.0f) {
		progresoRuta += (velocidadCoche / distanciaTotal1);
	}

	if (progresoRuta >= 1.0f) {
		progresoRuta = 0.0f;
		indiceRuta = (indiceRuta + 1) % scene->miCircuito->ruta.size();
		actual1 = scene->miCircuito->ruta[indiceRuta];
		siguiente1 = scene->miCircuito->ruta[(indiceRuta + 1) % scene->miCircuito->ruta.size()];
	}

	float carX1 = actual1.x + (siguiente1.x - actual1.x) * progresoRuta;
	float carZ1 = actual1.z + (siguiente1.z - actual1.z) * progresoRuta;

	float anguloRad1 = atan2(siguiente1.x - actual1.x, siguiente1.z - actual1.z);
	float carAngulo1 = glm::degrees(anguloRad1);

	float offsetX1 = cos(anguloRad1) * -0.039f; // Offset Negativo para el coche 1
	float offsetZ1 = -sin(anguloRad1) * -0.039f;

	float finalX1 = carX1 + offsetX1;
	float finalZ1 = carZ1 + offsetZ1;

	scene->f1->ResetLocation();
	scene->f1->Translate(glm::vec3(finalX1, 0.0f, finalZ1));
	scene->f1->Rotate(carAngulo1, glm::vec3(0.0f, 1.0f, 0.0f));
	scene->f1->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));


	// 2. FÍSICAS COCHE 2 (Carril Derecho: 0.039f)
	Circuito::Waypoint actual2 = scene->miCircuito->ruta[indiceRuta2];
	Circuito::Waypoint siguiente2 = scene->miCircuito->ruta[(indiceRuta2 + 1) % scene->miCircuito->ruta.size()];

	float distX2 = siguiente2.x - actual2.x;
	float distZ2 = siguiente2.z - actual2.z;
	float distanciaTotal2 = sqrt(distX2 * distX2 + distZ2 * distZ2);

	if (distanciaTotal2 > 0.0f) {
		progresoRuta2 += (velocidadCoche2 / distanciaTotal2);
	}

	if (progresoRuta2 >= 1.0f) {
		progresoRuta2 = 0.0f;
		indiceRuta2 = (indiceRuta2 + 1) % scene->miCircuito->ruta.size();
		actual2 = scene->miCircuito->ruta[indiceRuta2];
		siguiente2 = scene->miCircuito->ruta[(indiceRuta2 + 1) % scene->miCircuito->ruta.size()];
	}

	float carX2 = actual2.x + (siguiente2.x - actual2.x) * progresoRuta2;
	float carZ2 = actual2.z + (siguiente2.z - actual2.z) * progresoRuta2;

	float anguloRad2 = atan2(siguiente2.x - actual2.x, siguiente2.z - actual2.z);
	float carAngulo2 = glm::degrees(anguloRad2);

	float offsetX2 = cos(anguloRad2) * 0.039f; // Offset Positivo para el coche 2
	float offsetZ2 = -sin(anguloRad2) * 0.039f;

	float finalX2 = carX2 + offsetX2;
	float finalZ2 = carZ2 + offsetZ2;

	scene->f2->ResetLocation();
	scene->f2->Translate(glm::vec3(finalX2, 0.0f, finalZ2));
	scene->f2->Rotate(carAngulo2, glm::vec3(0.0f, 1.0f, 0.0f));
	scene->f2->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));


	// 3. SISTEMA DE CÁMARAS (F1, F2, F3)
	float targetCamX, targetCamY, targetCamZ;
	float targetMiraX, targetMiraY, targetMiraZ;

	if (modoCamara == 1)
	{
		// CÁMARA AÉREA 
		targetCamX = -1.5f;
		targetCamY = 7.0f;
		targetCamZ = 1.0f;

		targetMiraX = -1.4f;
		targetMiraY = 0.0f;
		targetMiraZ = 1.0f;
	}
	else if (modoCamara == 2)
	{
		// CÁMARA COCHE 1
		targetCamX = finalX1 - sin(anguloRad1) * 1.2f;
		targetCamY = 0.4f;
		targetCamZ = finalZ1 - cos(anguloRad1) * 1.2f;

		targetMiraX = finalX1;
		targetMiraY = 0.05f;
		targetMiraZ = finalZ1;
	}
	else if (modoCamara == 3)
	{
		// CÁMARA COCHE 2
		targetCamX = finalX2 - sin(anguloRad2) * 1.2f;
		targetCamY = 0.4f;
		targetCamZ = finalZ2 - cos(anguloRad2) * 1.2f;

		targetMiraX = finalX2;
		targetMiraY = 0.05f;
		targetMiraZ = finalZ2;
	}

	// Efecto Lerp para transición suave
	glm::vec3 currentCam = camera->GetPosition();
	float smoothSpeed = (modoCamara == 1) ? 0.05f : 0.1f;

	float newCamX = currentCam.x + (targetCamX - currentCam.x) * smoothSpeed;
	float newCamY = currentCam.y + (targetCamY - currentCam.y) * smoothSpeed;
	float newCamZ = currentCam.z + (targetCamZ - currentCam.z) * smoothSpeed;

	camera->SetPosition(newCamX, newCamY, newCamZ);

	camera->SetDirection(
		newCamX - targetMiraX,
		newCamY - targetMiraY,
		newCamZ - targetMiraZ,
		0.0f, 1.0f, 0.0f
	);
}

//
// FUNCIÓN: CGModel::key_pressed(int)
//
void CGModel::key_pressed(int key)
{
	const float VELOCIDAD_MAXIMA = 0.02f;
	const float PASO = VELOCIDAD_MAXIMA / 10.0f;

	switch (key)
	{
		// Controles Coche 1
	case GLFW_KEY_Q:
		velocidadCoche += PASO;
		if (velocidadCoche > VELOCIDAD_MAXIMA) velocidadCoche = VELOCIDAD_MAXIMA;
		break;
	case GLFW_KEY_A:
		velocidadCoche -= PASO;
		if (velocidadCoche < 0.0f) velocidadCoche = 0.0f;
		break;

		// Controles Coche 2
	case GLFW_KEY_O:
		velocidadCoche2 += PASO;
		if (velocidadCoche2 > VELOCIDAD_MAXIMA) velocidadCoche2 = VELOCIDAD_MAXIMA;
		break;
	case GLFW_KEY_L:
		velocidadCoche2 -= PASO;
		if (velocidadCoche2 < 0.0f) velocidadCoche2 = 0.0f;
		break;

		// Cambios de Cámara
	case GLFW_KEY_F1: modoCamara = 1; break;
	case GLFW_KEY_F2: modoCamara = 2; break;
	case GLFW_KEY_F3: modoCamara = 3; break;
	}
}

//
//  FUNCIÓN: CGModel:::mouse_button(int button, int action)
//
void CGModel::mouse_button(int button, int action) {}

//
//  FUNCIÓN: CGModel::mouse_move(double xpos, double ypos)
//
void CGModel::mouse_move(double xpos, double ypos) {}

//
//  FUNCIÓN: CGModel::CameraConstraints()
//
