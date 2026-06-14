#pragma once

#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

class Car : public CGObject {
private:
	CGMaterial* mtl[7];
	CGPiece* pieces[72];

public:
	Car();
	~Car();
	virtual int GetNumPieces();
	virtual CGPiece* GetPiece(int i);
};

