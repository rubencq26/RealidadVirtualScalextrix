#include "CGScene.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CGShaderProgram.h"
#include "CGObject.h"
#include "CGLight.h"
#include "resource.h"


//
// FUNCIÓN: CGScene::CGScene()
//
// PROPÓSITO: Construye el objeto que representa la escena
//
CGScene::CGScene()
{
    glm::vec3 Ldir = glm::vec3(1.0f, -0.8f, -1.0f);
    Ldir = glm::normalize(Ldir);
    light = new CGLight();
    light->SetLightDirection(Ldir);
    light->SetAmbientLight(glm::vec3(0.5f, 0.5f, 0.5f));
    light->SetDifusseLight(glm::vec3(0.7f, 0.7f, 0.7f));
    light->SetSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));

    matRecta = new CGMaterial();
    matRecta->InitTexture("RectaStd.png");

    matCurvaInt = new CGMaterial();
    matCurvaInt->InitTexture("RectaStd.png");

    matCurvaEst = new CGMaterial();
    matCurvaEst->InitTexture("RectaStd.png");

    matCurvaExt = new CGMaterial();
    matCurvaExt->InitTexture("RectaStd.png");

    miCircuito = new Circuito(matRecta->GetTexture(), matCurvaEst->GetTexture(), matCurvaInt->GetTexture() ,matCurvaExt->GetTexture());
    miCircuito->construirCircuito();

    f1 = new Car();
    f1->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    f1->Translate(glm::vec3(0.0f, 0.0f, 0.0f));

    f2 = new Car();
    f2->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    f2->Translate(glm::vec3(0.0f, 0.0f, 0.0f));

}

//
// FUNCIÓN: CGScene3:~CGScene()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
CGScene::~CGScene()
{
    delete light;
    delete miCircuito;
    delete matRecta;
    delete matCurvaInt;
    delete matCurvaEst;
    delete matCurvaExt;
}

//
// FUNCIÓN: CGScene::Draw()
//
// PROPÓSITO: Dibuja la escena
//
void CGScene::Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view)
{
    light->SetUniforms(program);
    
    matRecta->SetUniforms(program);
    matCurvaEst->SetUniforms(program);
    matCurvaExt->SetUniforms(program);
    matCurvaInt->SetUniforms(program);

    miCircuito->dibujar(program, proj, view);

    f1->Draw(program, proj, view);
    f2->Draw(program, proj, view);

}
