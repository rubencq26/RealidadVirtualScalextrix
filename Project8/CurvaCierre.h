#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CGShaderProgram.h"

class CurvaCierre
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texturaID;
	int numVertices;

	float posX, posZ;
	float rotacionY;
	float escalaX;

public:
	CurvaCierre();

	void setDireccionDerecha(bool esDerecha) {
		if (esDerecha) escalaX = -1.0f;
		else escalaX = 1.0f;
	}

	// ¡NUEVO! Le pasamos dónde está el cursor para que calcule la elipse
	void inicializar(unsigned int idTextura, float curX, float curZ, float curAngulo, bool esDerecha);

	void dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view);
	void setPosicion(float x, float z) { posX = x; posZ = z; }
	void setRotation(float grados) { rotacionY = grados; }
};