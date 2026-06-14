#include "Circuito.h"
#include <iostream>

void Circuito::colocarRectaEstandar()
{
	RectaEstandar* r = new RectaEstandar();
	r->inicializar(tRecta);
	r->setPosicion(cursorX, cursorZ);
	r->setRotation(cursorAngulo);
	rectaEstandar.push_back(r);

	cursorX += 0.35f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.35f * cos(glm::radians(cursorAngulo));

	ruta.push_back({ cursorX, cursorZ, cursorAngulo });
}

void Circuito::colocarMediaRecta()
{
	MediaRecta* r = new MediaRecta();
	r->inicializar(tRecta);
	r->setPosicion(cursorX, cursorZ);
	r->setRotation(cursorAngulo);
	mediaRecta.push_back(r);

	cursorX += 0.175f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.175f * cos(glm::radians(cursorAngulo));

	ruta.push_back({ cursorX, cursorZ, cursorAngulo });
}

void Circuito::colocarCuartoRecta()
{
	CuartoRecta* r = new CuartoRecta();
	r->inicializar(tRecta);
	r->setPosicion(cursorX, cursorZ);
	r->setRotation(cursorAngulo);
	cuartoRecta.push_back(r);

	cursorX += 0.0875f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.0875f * cos(glm::radians(cursorAngulo));

	ruta.push_back({ cursorX, cursorZ, cursorAngulo });
}

// ==========================================
// CURVAS INTERIORES (45 grados | Radio: 0.136f)
// ==========================================

void Circuito::colocarCurvaInteriorIzquierda()
{
	CurvaInterior* c = new CurvaInterior();
	c->inicializar(tInterior);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(false); // Curva normal
	curvaInterior.push_back(c);

	float radioMedio = 0.136f;
	int segmentos = 10;
	for (int i = 1; i <= segmentos; i++) {
		float alpha = glm::radians(45.0f) * ((float)i / segmentos);
		float localX = radioMedio * cos(alpha) - radioMedio;
		float localZ = radioMedio * sin(alpha);
		float rad = glm::radians(cursorAngulo);
		float mundoX = localX * cos(rad) + localZ * sin(rad);
		float mundoZ = -localX * sin(rad) + localZ * cos(rad);
		ruta.push_back({ cursorX + mundoX, cursorZ + mundoZ, cursorAngulo - glm::degrees(alpha) });
	}

	float localX = radioMedio * cos(glm::radians(45.0f)) - radioMedio;
	float localZ = radioMedio * sin(glm::radians(45.0f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo -= 45.0f; // Giramos a la izquierda (+)
}

void Circuito::colocarCurvaInteriorDerecha()
{
	CurvaInterior* c = new CurvaInterior();
	c->inicializar(tInterior);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(true); // Efecto espejo
	curvaInterior.push_back(c);

	float radioMedio = 0.136f;
	

	int segmentos = 10;
	for (int i = 1; i <= segmentos; i++) {
		float alpha = glm::radians(45.0f) * ((float)i / segmentos);
		float localX = -(radioMedio * cos(alpha) - radioMedio); // Invertimos X por ser derecha
		float localZ = radioMedio * sin(alpha);

		float rad = glm::radians(cursorAngulo);
		float mundoX = localX * cos(rad) + localZ * sin(rad);
		float mundoZ = -localX * sin(rad) + localZ * cos(rad);

		ruta.push_back({ cursorX + mundoX, cursorZ + mundoZ, cursorAngulo + glm::degrees(alpha) });
	}

	// Invertimos la X para que el cursor salga por la derecha
	float localX = -(radioMedio * cos(glm::radians(45.0f)) - radioMedio);
	float localZ = radioMedio * sin(glm::radians(45.0f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo += 45.0f; // Giramos a la derecha (-)
}

// ==========================================
// CURVAS ESTÁNDAR (45 grados | Radio: 0.292f)
// ==========================================

void Circuito::colocarCurvaEstandarIzquierda()
{
	CurvaEstandar* c = new CurvaEstandar();
	c->inicializar(tStd);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(false);
	curvaEstandar.push_back(c);

	float radioMedio = 0.292f;

	int segmentos = 10;
	for (int i = 1; i <= segmentos; i++) {
		float alpha = glm::radians(45.0f) * ((float)i / segmentos);
		float localX = radioMedio * cos(alpha) - radioMedio;
		float localZ = radioMedio * sin(alpha);

		float rad = glm::radians(cursorAngulo);
		float mundoX = localX * cos(rad) + localZ * sin(rad);
		float mundoZ = -localX * sin(rad) + localZ * cos(rad);

		ruta.push_back({ cursorX + mundoX, cursorZ + mundoZ, cursorAngulo - glm::degrees(alpha) });
	}


	float localX = radioMedio * cos(glm::radians(45.0f)) - radioMedio;
	float localZ = radioMedio * sin(glm::radians(45.0f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo -= 45.0f;
}

void Circuito::colocarCurvaEstandarDerecha()
{
	CurvaEstandar* c = new CurvaEstandar();
	c->inicializar(tStd);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(true);
	curvaEstandar.push_back(c);

	float radioMedio = 0.292f;

	int segmentos = 10;
	for (int i = 1; i <= segmentos; i++) {
		float alpha = glm::radians(45.0f) * ((float)i / segmentos);
		float localX = -(radioMedio * cos(alpha) - radioMedio); // Invertimos X por ser derecha
		float localZ = radioMedio * sin(alpha);

		float rad = glm::radians(cursorAngulo);
		float mundoX = localX * cos(rad) + localZ * sin(rad);
		float mundoZ = -localX * sin(rad) + localZ * cos(rad);

		ruta.push_back({ cursorX + mundoX, cursorZ + mundoZ, cursorAngulo + glm::degrees(alpha) });
	}

	float localX = -(radioMedio * cos(glm::radians(45.0f)) - radioMedio);
	float localZ = radioMedio * sin(glm::radians(45.0f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo += 45.0f;
}

void Circuito::colocarCurvaCierreIzquierda()
{
	CurvaCierre* c = new CurvaCierre();

	// ¡NUEVO! Pasamos el ángulo y 'false' (izquierda)
	c->inicializar(tStd, cursorX, cursorZ, cursorAngulo, false);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(false);

	curvaCierre.push_back(c);

	float deltaX = -cursorX;
	float deltaZ = -cursorZ;
	float radCursor = glm::radians(cursorAngulo);
	float localX = deltaX * cos(radCursor) - deltaZ * sin(radCursor);
	float localZ = deltaX * sin(radCursor) + deltaZ * cos(radCursor);

	float cos45 = cos(glm::radians(45.0f));
	float sin45 = sin(glm::radians(45.0f));
	float Rmx = localX / (cos45 - 1.0f);
	float Rmz = localZ / sin45;

	int segmentos = 10;
	for (int i = 1; i <= segmentos; i++) {
		float alpha = glm::radians(45.0f) * ((float)i / segmentos);
		float wX = (Rmx * cos(alpha)) - Rmx;
		float wZ = Rmz * sin(alpha);

		float mundoX = wX * cos(radCursor) + wZ * sin(radCursor);
		float mundoZ = -wX * sin(radCursor) + wZ * cos(radCursor);

		ruta.push_back({ cursorX + mundoX, cursorZ + mundoZ, cursorAngulo - glm::degrees(alpha) });
	}

	float mundoX = -cursorX;
	float mundoZ = -cursorZ;

	cursorX += mundoX; // El cursor se queda matemáticamente en 0.0f
	cursorZ += mundoZ; // El cursor se queda matemáticamente en 0.0f
	cursorAngulo -= 45.0f;
}

void Circuito::colocarCurvaCierreDerecha()
{
	CurvaCierre* c = new CurvaCierre();

	// ¡NUEVO! Pasamos el ángulo y 'true' (derecha)
	c->inicializar(tStd, cursorX, cursorZ, cursorAngulo, true);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(true);

	curvaCierre.push_back(c);

	float deltaX = -cursorX;
	float deltaZ = -cursorZ;
	float radCursor = glm::radians(cursorAngulo);
	float localX = deltaX * cos(radCursor) - deltaZ * sin(radCursor);
	float localZ = deltaX * sin(radCursor) + deltaZ * cos(radCursor);

	// Efecto espejo local
	localX = -localX;

	float cos45 = cos(glm::radians(45.0f));
	float sin45 = sin(glm::radians(45.0f));
	float Rmx = localX / (cos45 - 1.0f);
	float Rmz = localZ / sin45;

	int segmentos = 10;
	for (int i = 1; i <= segmentos; i++) {
		float alpha = glm::radians(45.0f) * ((float)i / segmentos);
		float wX = -(Rmx * cos(alpha) - Rmx); // Negativo por simetría derecha
		float wZ = Rmz * sin(alpha);

		float mundoX = wX * cos(radCursor) + wZ * sin(radCursor);
		float mundoZ = -wX * sin(radCursor) + wZ * cos(radCursor);

		ruta.push_back({ cursorX + mundoX, cursorZ + mundoZ, cursorAngulo + glm::degrees(alpha) });
	}

	float mundoX = -cursorX;
	float mundoZ = -cursorZ;

	cursorX += mundoX; // El cursor se queda matemáticamente en 0.0f
	cursorZ += mundoZ; // El cursor se queda matemáticamente en 0.0f
	cursorAngulo += 45.0f;
}
// ==========================================
// CURVAS EXTERIORES (22.5 grados | Radio: 0.448f)
// ==========================================

void Circuito::colocarCurvaExteriorIzquierda()
{
	CurvaExterior* c = new CurvaExterior();
	c->inicializar(tExterior);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(false);
	curvaExterior.push_back(c);

	float radioMedio = 0.448f;
	int segmentos = 5; // Tienen menos segmentos por ser más cortas
	for (int i = 1; i <= segmentos; i++) {
		float alpha = glm::radians(22.5f) * ((float)i / segmentos); // ¡22.5 grados!
		float localX = radioMedio * cos(alpha) - radioMedio;
		float localZ = radioMedio * sin(alpha);
		float rad = glm::radians(cursorAngulo);
		float mundoX = localX * cos(rad) + localZ * sin(rad);
		float mundoZ = -localX * sin(rad) + localZ * cos(rad);
		ruta.push_back({ cursorX + mundoX, cursorZ + mundoZ, cursorAngulo - glm::degrees(alpha) });
	}

	float localX = radioMedio * cos(glm::radians(22.5f)) - radioMedio;
	float localZ = radioMedio * sin(glm::radians(22.5f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo -= 22.5f;
}

void Circuito::colocarCurvaExteriorDerecha()
{
	CurvaExterior* c = new CurvaExterior();
	c->inicializar(tExterior);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(true);
	curvaExterior.push_back(c);

	float radioMedio = 0.448f;
	int segmentos = 5;
	for (int i = 1; i <= segmentos; i++) {
		float alpha = glm::radians(22.5f) * ((float)i / segmentos);
		float localX = -(radioMedio * cos(alpha) - radioMedio); // Negativo por ser Derecha
		float localZ = radioMedio * sin(alpha);

		float rad = glm::radians(cursorAngulo);
		float mundoX = localX * cos(rad) + localZ * sin(rad);
		float mundoZ = -localX * sin(rad) + localZ * cos(rad);

		ruta.push_back({ cursorX + mundoX, cursorZ + mundoZ, cursorAngulo + glm::degrees(alpha) });
	}

	float localX = -(radioMedio * cos(glm::radians(22.5f)) - radioMedio);
	float localZ = radioMedio * sin(glm::radians(22.5f));

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo += 22.5f;
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

	ruta.clear();
	ruta.push_back({ 0.0f, 0.0f, 0.0f });

	for (int i = 0; i < 8; i++) {
		colocarRectaEstandar();
	}

	// --- PRIMERA CURVA (Giro a la derecha en el plano original) ---
	colocarCurvaInteriorIzquierda();
	colocarCurvaEstandarIzquierda();
	colocarCurvaEstandarIzquierda();
	colocarCurvaExteriorIzquierda();

	colocarRectaEstandar();

	for (int i = 0; i < 3; i++) {
		colocarCurvaExteriorDerecha();
	}

	colocarMediaRecta();

	for (int i = 0; i < 5; i++) {
		colocarCurvaExteriorDerecha();
	}

	colocarRectaEstandar();

	colocarCurvaExteriorIzquierda();
	colocarCurvaEstandarIzquierda();
	colocarCurvaEstandarIzquierda();

	colocarRectaEstandar();

	colocarCurvaExteriorIzquierda();
	colocarCurvaInteriorIzquierda();

	colocarRectaEstandar();
	colocarRectaEstandar();

	colocarCurvaInteriorIzquierda();
	colocarCurvaInteriorIzquierda();

	colocarCuartoRecta();

	colocarCurvaInteriorDerecha();
	colocarCurvaExteriorDerecha();

	colocarMediaRecta();

	colocarCurvaEstandarIzquierda();

	colocarMediaRecta();

	colocarCurvaEstandarIzquierda();

	for (int i = 0; i < 3; i++) {
		colocarRectaEstandar();
	}

	colocarCurvaExteriorDerecha();
	colocarCurvaEstandarDerecha();
	colocarCurvaEstandarDerecha();
	colocarCurvaInteriorDerecha();

	for (int i = 0; i < 7; i++) {
		colocarRectaEstandar();
	}

	colocarCurvaExteriorIzquierda();

	colocarCurvaEstandarIzquierda();
	colocarCurvaEstandarIzquierda();

	colocarRectaEstandar();
	colocarRectaEstandar();

	colocarCurvaInteriorIzquierda();
	colocarCurvaEstandarIzquierda();
	colocarCurvaInteriorIzquierda();

	colocarRectaEstandar();

	colocarCurvaEstandarDerecha();

	colocarRectaEstandar();
	colocarRectaEstandar();

	colocarCurvaEstandarDerecha();
	colocarCurvaEstandarDerecha();

	for (int i = 0; i < 3; i++) {
		colocarRectaEstandar();
	}

	for (int i = 0; i < 2; i++) {
		colocarCurvaEstandarIzquierda();
	}

	// --- CURVA FINAL ADAPTATIVA ---
	colocarCurvaCierreIzquierda();
	
}

void Circuito::dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view)
{
	for (size_t i = 0; i < rectaEstandar.size(); i++) {
		rectaEstandar[i]->dibujar(program, proj, view);
	}

	
	for (size_t i = 0; i < mediaRecta.size(); i++) {
		mediaRecta[i]->dibujar(program, proj, view);
	}

	
	for (size_t i = 0; i < cuartoRecta.size(); i++) {
		cuartoRecta[i]->dibujar(program, proj, view);
	}

	
	for (size_t i = 0; i < curvaInterior.size(); i++) {
		curvaInterior[i]->dibujar(program, proj, view);
	}


	for (size_t i = 0; i < curvaEstandar.size(); i++) {
		curvaEstandar[i]->dibujar(program, proj, view);
	}


	for (size_t i = 0; i < curvaExterior.size(); i++) {
		curvaExterior[i]->dibujar(program, proj, view);
	}

	for (size_t i = 0; i < curvaCierre.size(); i++) {
		curvaCierre[i]->dibujar(program, proj, view);
	}
}




