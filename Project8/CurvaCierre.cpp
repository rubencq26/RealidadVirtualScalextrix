#include "CurvaCierre.h"
#include <vector>
#include <cmath>

CurvaCierre::CurvaCierre()
{
	VAO = 0; VBO = 0; texturaID = 0;
	posX = 0.0f; posZ = 0.0f; rotacionY = 0.0f; escalaX = 1.0f;
	numVertices = 60; // 10 segmentos * 2 triangulos * 3 vertices
}

void CurvaCierre::inicializar(unsigned int idTextura, float curX, float curZ, float curAngulo, bool esDerecha)
{
	texturaID = idTextura;
	std::vector<float> vertices;

	// 1. Distancia que falta para llegar al origen (0,0) en GLOBAL
	float deltaX = -curX;
	float deltaZ = -curZ;

	// 2. Rotamos esa distancia para entenderla en el espacio LOCAL de la pieza
	// ---> ¡CORRECCIÓN! El curAngulo va en POSITIVO <---
	float rad = glm::radians(curAngulo);

	float localX = deltaX * cos(rad) - deltaZ * sin(rad);
	float localZ = deltaX * sin(rad) + deltaZ * cos(rad);

	// 3. Si la curva es hacia la derecha, el efecto espejo invierte la X
	if (esDerecha) {
		localX = -localX;
	}

	// 4. Calculamos los dos radios de la ELIPSE usando la fórmula correcta
	float c = cos(glm::radians(45.0f));
	float s = sin(glm::radians(45.0f));

	float Rmx = localX / (c - 1.0f);
	float Rmz = localZ / s;

	float ancho = 0.156f;

	// Radios internos y externos elípticos
	float R_inx = Rmx - ancho / 2.0f;
	float R_inz = Rmz - ancho / 2.0f;
	float R_outx = Rmx + ancho / 2.0f;
	float R_outz = Rmz + ancho / 2.0f;

	int segmentos = 10;
	float incrementoAngulo = glm::radians(45.0f) / segmentos;

	for (int i = 0; i < segmentos; i++)
	{
		float alpha0 = i * incrementoAngulo;
		float alpha1 = (i + 1) * incrementoAngulo;

		// Punto A (Interno Inicio)
		float ax = (R_inx * cos(alpha0)) - Rmx;
		float az = R_inz * sin(alpha0);
		// Punto B (Externo Inicio)
		float bx = (R_outx * cos(alpha0)) - Rmx;
		float bz = R_outz * sin(alpha0);
		// Punto C (Interno Fin)
		float cx = (R_inx * cos(alpha1)) - Rmx;
		float cz = R_inz * sin(alpha1);
		// Punto D (Externo Fin)
		float dx = (R_outx * cos(alpha1)) - Rmx;
		float dz = R_outz * sin(alpha1);

		float v0 = (float)i / segmentos;
		float v1 = (float)(i + 1) / segmentos;

		// Triangulo 1
		vertices.push_back(ax); vertices.push_back(0.0f); vertices.push_back(az); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(v0);
		vertices.push_back(bx); vertices.push_back(0.0f); vertices.push_back(bz); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(v0);
		vertices.push_back(cx); vertices.push_back(0.0f); vertices.push_back(cz); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(v1);

		// Triangulo 2
		vertices.push_back(bx); vertices.push_back(0.0f); vertices.push_back(bz); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(v0);
		vertices.push_back(dx); vertices.push_back(0.0f); vertices.push_back(dz); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(v1);
		vertices.push_back(cx); vertices.push_back(0.0f); vertices.push_back(cz); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(v1);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CurvaCierre::dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view, glm::mat4 shadowViewMatrix)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(posX, 0.0f, posZ));
	model = glm::rotate(model, glm::radians(rotacionY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(escalaX, 1.0f, 1.0f));
	glm::mat4 modelView = view * model;
	glm::mat4 mvp = proj * modelView;

	program->SetUniformMatrix4("MVP", mvp);
	program->SetUniformMatrix4("ViewMatrix", view);
	program->SetUniformMatrix4("ModelViewMatrix", modelView);
	program->SetUniformMatrix4("ShadowMatrix", shadowViewMatrix * model);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaID);
	program->SetUniformI("BaseTex", 0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}