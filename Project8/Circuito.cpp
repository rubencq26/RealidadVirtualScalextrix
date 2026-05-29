#include "Circuito.h"

void Circuito::colocarRectaEstandar()
{
	RectaEstandar r;
	r.inicializar(tRecta);
	r.setPosicion(cursorX, cursorZ);
	r.setRotation(cursorAngulo);
	rectaEstandar.push_back(r);

	cursorX += 0.35f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.35f * cos(glm::radians(cursorAngulo));
}

void Circuito::colocarMediaRecta()
{
	MediaRecta r;
	r.inicializar(tRecta);
	r.setPosicion(cursorX, cursorZ);
	r.setRotation(cursorAngulo);
	mediaRecta.push_back(r);

	cursorX += 0.175f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.175f * cos(glm::radians(cursorAngulo));
}

void Circuito::colocarCuartoRecta()
{
	CuartoRecta r;
	r.inicializar(tRecta);
	r.setPosicion(cursorX, cursorZ);
	r.setRotation(cursorAngulo);
	cuartoRecta.push_back(r);

	cursorX += 0.0875f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.0875f * cos(glm::radians(cursorAngulo));
}

// ==========================================
// CURVAS INTERIORES (45 grados | Radio: 0.136f)
// ==========================================

void Circuito::colocarCurvaInteriorIzquierda()
{
	CurvaInterior c;
	c.inicializar(tInterior);
	c.setPosicion(cursorX, cursorZ);
	c.setRotation(cursorAngulo);
	c.setDireccionDerecha(false); // Curva normal
	curvaInterior.push_back(c);

	float radioMedio = 0.136f;
	float localX = radioMedio * cos(glm::radians(45.0f)) - radioMedio;
	float localZ = radioMedio * sin(glm::radians(45.0f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo += 45.0f; // Giramos a la izquierda (+)
}

void Circuito::colocarCurvaInteriorDerecha()
{
	CurvaInterior c;
	c.inicializar(tInterior);
	c.setPosicion(cursorX, cursorZ);
	c.setRotation(cursorAngulo);
	c.setDireccionDerecha(true); // Efecto espejo
	curvaInterior.push_back(c);

	float radioMedio = 0.136f;
	// Invertimos la X para que el cursor salga por la derecha
	float localX = -(radioMedio * cos(glm::radians(45.0f)) - radioMedio);
	float localZ = radioMedio * sin(glm::radians(45.0f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo -= 45.0f; // Giramos a la derecha (-)
}

// ==========================================
// CURVAS ESTÁNDAR (45 grados | Radio: 0.292f)
// ==========================================

void Circuito::colocarCurvaEstandarIzquierda()
{
	CurvaEstandar c;
	c.inicializar(tStd);
	c.setPosicion(cursorX, cursorZ);
	c.setRotation(cursorAngulo);
	c.setDireccionDerecha(false);
	curvaEstandar.push_back(c);

	float radioMedio = 0.292f;
	float localX = radioMedio * cos(glm::radians(45.0f)) - radioMedio;
	float localZ = radioMedio * sin(glm::radians(45.0f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo += 45.0f;
}

void Circuito::colocarCurvaEstandarDerecha()
{
	CurvaEstandar c;
	c.inicializar(tStd);
	c.setPosicion(cursorX, cursorZ);
	c.setRotation(cursorAngulo);
	c.setDireccionDerecha(true);
	curvaEstandar.push_back(c);

	float radioMedio = 0.292f;
	float localX = -(radioMedio * cos(glm::radians(45.0f)) - radioMedio);
	float localZ = radioMedio * sin(glm::radians(45.0f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo -= 45.0f;
}

// ==========================================
// CURVAS EXTERIORES (22.5 grados | Radio: 0.448f)
// ==========================================

void Circuito::colocarCurvaExteriorIzquierda()
{
	CurvaExterior c;
	c.inicializar(tExterior);
	c.setPosicion(cursorX, cursorZ);
	c.setRotation(cursorAngulo);
	c.setDireccionDerecha(false);
	curvaExterior.push_back(c);

	float radioMedio = 0.448f;
	float localX = radioMedio * cos(glm::radians(22.5f)) - radioMedio;
	float localZ = radioMedio * sin(glm::radians(22.5f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo += 22.5f;
}

void Circuito::colocarCurvaExteriorDerecha()
{
	CurvaExterior c;
	c.inicializar(tExterior);
	c.setPosicion(cursorX, cursorZ);
	c.setRotation(cursorAngulo);
	c.setDireccionDerecha(true);
	curvaExterior.push_back(c);

	float radioMedio = 0.448f;
	float localX = -(radioMedio * cos(glm::radians(22.5f)) - radioMedio);
	float localZ = radioMedio * sin(glm::radians(22.5f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo -= 22.5f;
}

Circuito::Circuito(unsigned int r, unsigned int s, unsigned int i, unsigned int e)
{
	cursorX = 0.0f;
	cursorZ = 0.0f;
	cursorAngulo = 0.0f;

	tRecta = r;
	tStd = s;
	tInterior = i;
	tExterior = e;
}

void Circuito::construirCircuito()
{
	cursorX = 0.0f;
	cursorZ = 0.0f;
	cursorAngulo = 0.0f;

	for (int i = 0; i < 8; i++) {
		colocarRectaEstandar();
	}

	colocarCurvaInteriorDerecha();
	colocarCurvaEstandarDerecha();
	colocarCurvaEstandarDerecha();
	colocarCurvaExteriorDerecha();

	colocarRectaEstandar();

	for (int i = 0; i < 3; i++) {
		colocarCurvaExteriorIzquierda();
	}

	colocarMediaRecta();

	for (int i = 0; i < 5; i++) {
		colocarCurvaExteriorIzquierda();
	}

	colocarRectaEstandar();

	colocarCurvaExteriorDerecha();
	colocarCurvaEstandarDerecha();
	colocarCurvaEstandarDerecha();

	colocarRectaEstandar();

	colocarCurvaExteriorDerecha();
	colocarCurvaInteriorDerecha();

	colocarRectaEstandar();
	colocarRectaEstandar();

	colocarCurvaInteriorDerecha();
	colocarCurvaInteriorDerecha();

	colocarCuartoRecta();

	colocarCurvaInteriorIzquierda();
	colocarCurvaExteriorIzquierda();
	
	colocarMediaRecta();

	colocarCurvaEstandarDerecha();

	colocarMediaRecta();

	colocarCurvaEstandarDerecha();

	for (int i = 0; i < 3; i++) {
		colocarRectaEstandar();
	}

	colocarCurvaExteriorIzquierda();
	colocarCurvaEstandarIzquierda();
	colocarCurvaEstandarIzquierda();
	colocarCurvaInteriorIzquierda();

	for (int i = 0; i < 7; i++) {
		colocarRectaEstandar();
	}

	colocarCurvaExteriorDerecha();

	colocarCurvaEstandarDerecha();
	colocarCurvaEstandarDerecha();

	colocarRectaEstandar();
	colocarRectaEstandar();

	colocarCurvaInteriorDerecha();
	colocarCurvaEstandarDerecha();
	colocarCurvaInteriorDerecha();

	colocarRectaEstandar();

	colocarCurvaEstandarIzquierda();

	colocarRectaEstandar();
	colocarRectaEstandar();

	colocarCurvaEstandarIzquierda();
	colocarCurvaEstandarIzquierda();

	for (int i = 0; i < 3; i++) {
		colocarRectaEstandar();
	}

	for (int i = 0; i < 3; i++) {
		colocarCurvaEstandarDerecha();
	}
}

void Circuito::dibujar(unsigned int shaderProgramID)
{
	for (size_t i = 0; i < rectaEstandar.size(); i++) {
		rectaEstandar[i].dibujar(shaderProgramID);
	}

	
	for (size_t i = 0; i < mediaRecta.size(); i++) {
		mediaRecta[i].dibujar(shaderProgramID);
	}

	
	for (size_t i = 0; i < cuartoRecta.size(); i++) {
		cuartoRecta[i].dibujar(shaderProgramID);
	}

	
	for (size_t i = 0; i < curvaInterior.size(); i++) {
		curvaInterior[i].dibujar(shaderProgramID);
	}


	for (size_t i = 0; i < curvaEstandar.size(); i++) {
		curvaEstandar[i].dibujar(shaderProgramID);
	}


	for (size_t i = 0; i < curvaExterior.size(); i++) {
		curvaExterior[i].dibujar(shaderProgramID);
	}
}




