#pragma once
#include <vector>
#include "MediaRecta.h"
#include "RectaEstandar.h"
#include "CuartoRecta.h"
#include "CurvaInterior.h"
#include "CurvaEstandar.h"
#include "CurvaExterior.h"
class Circuito
{
private:
	float cursorX;
	float cursorZ;
	float cursorAngulo;

	unsigned int tRecta;
	unsigned int tStd;
	unsigned int tInterior;
	unsigned int tExterior;

	std::vector<RectaEstandar> rectaEstandar;
	std::vector<MediaRecta> mediaRecta;
	std::vector<CuartoRecta> cuartoRecta;
	std::vector<CurvaInterior> curvaInterior;
	std::vector<CurvaExterior> curvaExterior;
	std::vector<CurvaEstandar> curvaEstandar;
	
	void colocarRectaEstandar();
	void colocarMediaRecta();
	void colocarCuartoRecta();
	void colocarCurvaInteriorIzquierda();
	void colocarCurvaExteriorIzquierda();
	void colocarCurvaEstandarIzquierda();
	void colocarCurvaInteriorDerecha();
	void colocarCurvaExteriorDerecha();
	void colocarCurvaEstandarDerecha();

public:
	Circuito(unsigned int r, unsigned int s, unsigned int i, unsigned int e);
	
	void construirCircuito();
	void dibujar(unsigned int shaderProgramID);
};

