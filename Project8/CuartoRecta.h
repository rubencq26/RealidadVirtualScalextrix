#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CGShaderProgram.h"
class CuartoRecta
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texturaID;
	int numVertices;

	float ancho;
	float largo;

	float posX, posZ;
	float rotacionY;

public:
	CuartoRecta();

	void inicializar(unsigned int idTextura);

	void dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view);

	void setPosicion(float x, float z) { posX = x; posZ = z; }
	void setRotation(float grados) { rotacionY = grados; }
};

