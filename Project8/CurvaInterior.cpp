#include "CurvaInterior.h"
#include <vector>
#include <cmath>

CurvaInterior::CurvaInterior()
{
	VAO = 0;
	VBO = 0;
	texturaID = 0; 

	radioInterno = 0.058f;
	radioExterno = 0.214f;
	ancho = 0.156f;
	angulo = 45;

	posX = 0.0f;
	posZ = 0.0f;
	rotacionY = 0.0f;

	escalaX = 1.0f;

	// 10 sectores * 2 triangulos * 3 vertices
	numVertices = 60;
}

void CurvaInterior::inicializar(unsigned int idTextura)
{
	texturaID = idTextura;
	std::vector<float> vertices;

	int segmentos = 10;

	float anguloMaximo = glm::radians(angulo);

	float incrementoAngulo = anguloMaximo / segmentos;

	float radioMedio = (radioInterno + radioExterno) / 2.0f;

	for (int i = 0; i < segmentos; i++)
	{
		// Angulo donde empieza este trapecio y termina
		float alpha0 = i * incrementoAngulo;
		float alpha1 = (i + 1) * incrementoAngulo;

		// Base Inicial del trapecio
		// Punto A (Borde de dentro)
		float ax = (radioInterno * cos(alpha0)) - radioMedio;
		float az = radioInterno * sin(alpha0);

		// Punto B (Borde de fuera)
		float bx = (radioExterno * cos(alpha0)) - radioMedio;
		float bz = radioExterno * sin(alpha0);

		// Base final del trapecio

		float cx = (radioInterno * cos(alpha1)) - radioMedio;
		float cz = radioInterno * sin(alpha1);

		float dx = (radioExterno * cos(alpha1)) - radioMedio;
		float dz = radioExterno * sin(alpha1);

		// Coordenadas de la textura U
		float v0 = (float)i / segmentos;
		float v1 = (float)(i + 1) / segmentos;

		// Triangulo 1
		// Punto A (Interno Inicio)
		vertices.push_back(ax); vertices.push_back(0.0f); vertices.push_back(az); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(v0);
		// Punto B (Externo Inicio)
		vertices.push_back(bx); vertices.push_back(0.0f); vertices.push_back(bz); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(v0);
		// Punto C (InternoFin)
		vertices.push_back(cx); vertices.push_back(0.0f); vertices.push_back(cz); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(v1);

		// Triangulo 2
		// Punto B (Externo Inicio)
		vertices.push_back(bx); vertices.push_back(0.0f); vertices.push_back(bz); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(v0);
		// Punto D (Externo Fin)
		vertices.push_back(dx); vertices.push_back(0.0f); vertices.push_back(dz); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(v1);
		// Punto C (Interno Fin)
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

void CurvaInterior::dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view, glm::mat4 shadowViewMatrix)
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
