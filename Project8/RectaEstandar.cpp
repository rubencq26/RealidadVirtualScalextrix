#include "RectaEstandar.h"

RectaEstandar::RectaEstandar()
{
	VAO = 0;
	VBO = 0;
	texturaID = 0;
	numVertices = 6;
	posX = 0.0f;
	posZ = 0.0f;
	rotacionY = 0.0f;
	ancho = 0.156f;
	largo = 0.350f;
}

void RectaEstandar::inicializar(unsigned int idTextura)
{
	texturaID = idTextura;

	float m = ancho / 2.0f;

	float vertices[] = {
		// Triangulo 1
		-m, 0.0f, 0.0f,		0.0f, 0.0f, // Abajo izquierda
		 m, 0.0f, 0.0f,		1.0f, 0.0f, // Abajo derecha
		-m, 0.0f, largo,	0.0f, 1.0f, // Arriba izquierda

		// Triangulo 2
		 m, 0.0f, 0.0f,		1.0f, 0.0f, // Abajo derecha
		 m, 0.0f, largo,	1.0f, 1.0f, // Arriba derecha
		-m, 0.0f, largo,	0.0f, 1.0f  // Arriba Izquierda
	};


	// Reservamos espacio en la VRAM de la grafica
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Activamos nuestro VAO
	glBindVertexArray(VAO);

	// Subimos los datos a la VRAM de la grafica

	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	// Aqui le decimos a OpenGL como leer estos datos,
	// Leer posicion X,Y,Z, : Empieza en el byte 0 salta de 5 en 5 numeros
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0 );
	glEnableVertexAttribArray(0);

	// Leer Textura (U, V):
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Desvinculamos buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void RectaEstandar::dibujar(unsigned int shaderProgramID)
{
	// Creamos una natriz identidad
	glm::mat4 model = glm::mat4(1.0f);

	// Trasladamos la piea a su posicion en el mundo
	model = glm::translate(model, glm::vec3(posX, 0.0f, posZ));

	// Rotamos la pieza sobre el eje Y 
	model = glm::rotate(model, glm::radians(rotacionY), glm::vec3(0.0f, 1.0f, 0.0f));

	// Buscamos donde esta la variabke nodel dentro del VertexShader
	unsigned int modelLoc = glGetUniformLocation(shaderProgramID, "model");

	// Le pasmos la matriz transformada a la targeta gráfica usando glm::value_ptr
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// Activamos la textura del asfalto
	glActiveTexture(GL_TEXTURE0); // Texture 0 porque puedes poner mas de una textura en un mismo lugar 
	glBindTexture(GL_TEXTURE_2D, texturaID);

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


