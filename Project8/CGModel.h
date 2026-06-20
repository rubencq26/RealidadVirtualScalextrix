#pragma once

#include <GL/glew.h>
#include "CGShaderProgram.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CGSkybox.h"

class CGModel
{
public:
	void initialize(int w, int h);
	void finalize();
	void render();
	void update();
	void key_pressed(int key);
	void mouse_button(int button, int action);
	void mouse_move(double xpos, double ypos);
	void resize(int w, int h);
	bool InitShadowMap();


private:
	CGShaderProgram* program;
	CGShaderProgram* skyboxProgram;
	CGScene* scene;
	CGCamera* camera;
	float velocidadCoche = 0.0f;
	int indiceRuta = 0;
	float progresoRuta = 0.0f;
	int indiceRuta2 = 0;
	float progresoRuta2 = 0.0f;
	float velocidadCoche2 = 0.0f;

	int modoCamara = 1;

	CGSkybox* skybox;
	glm::mat4 projection;


	GLsizei wndWidth;
	GLsizei wndHeight;
	GLuint shadowFBO;
	GLuint depthTexId;


	
};


