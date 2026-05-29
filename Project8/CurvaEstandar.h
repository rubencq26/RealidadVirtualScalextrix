#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CurvaEstandar
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texturaID;
	int numVertices;

	float radioInterno;
	float radioExterno;
	float ancho;
	float angulo;

	float posX, posZ;
	float rotacionY;

	float escalaX;

public:
	CurvaEstandar();

	void setDireccionDerecha(bool esDerecha) {
		if (esDerecha) escalaX = -1.0f;
		else escalaX = 1.0f;
	}

	void inicializar(unsigned int idTextura);
	void dibujar(unsigned int shaderProgramID);

	void setPosicion(float x, float z) { posX = x; posZ = z; }
	void setRotation(float grados) { rotacionY = grados; }
};

