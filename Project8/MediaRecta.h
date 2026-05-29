#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class MediaRecta
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
	MediaRecta();

	void inicializar(unsigned int idTextura);

	void dibujar(unsigned int shaderProgramID);

	void setPosicion(float x, float z) { posX = x; posZ = z; }
	void setRotation(float grados) { rotacionY = grados; }

};

