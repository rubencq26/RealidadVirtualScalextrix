#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"
#include "CGLight.h"
#include "CGObject.h"
#include "Circuito.h"
#include "Car.h"


class CGScene {
public:
    CGScene();
    ~CGScene();
    void Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view, glm::mat4 shadowViewMatrix);
    Car* f1;
    Car* f2;
    Circuito* miCircuito;
    glm::mat4 GetLightViewMatrix();

private:
    CGLight* light;
    CGMaterial* matRecta;
    CGMaterial* matCurvaInt;
    CGMaterial* matCurvaEst;
    CGMaterial* matCurvaExt;

    
};
