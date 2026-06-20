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
    glm::vec3 Ldir = glm::vec3(0.4f, -0.85f, 0.4f);
    Ldir = glm::normalize(Ldir);
    light = new CGLight();
    light->SetLightDirection(Ldir);
    light->SetAmbientLight(glm::vec3(0.35f, 0.35f, 0.35f));
    light->SetDifusseLight(glm::vec3(1.0f, 1.0f, 1.0f));
    light->SetSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));

    matRecta = new CGMaterial();
    matRecta->InitTexture("RectaStd.png");
    matRecta->SetAmbientReflect(1.0f, 1.0f, 1.0f);
    matRecta->SetDifusseReflect(1.0f, 1.0f, 1.0f);
    matRecta->SetSpecularReflect(0.5f, 0.5f, 0.5f);
    matRecta->SetShininess(32.0f);

    matCurvaInt = new CGMaterial();
    matCurvaInt->InitTexture("RectaStd.png");
    matCurvaInt->SetAmbientReflect(1.0f, 1.0f, 1.0f);
    matCurvaInt->SetDifusseReflect(1.0f, 1.0f, 1.0f);
    matCurvaInt->SetSpecularReflect(0.5f, 0.5f, 0.5f);
    matCurvaInt->SetShininess(32.0f);

    matCurvaEst = new CGMaterial();
    matCurvaEst->InitTexture("RectaStd.png");
    matCurvaEst->SetAmbientReflect(1.0f, 1.0f, 1.0f);
    matCurvaEst->SetDifusseReflect(1.0f, 1.0f, 1.0f);
    matCurvaEst->SetSpecularReflect(0.5f, 0.5f, 0.5f);
    matCurvaEst->SetShininess(32.0f);

    matCurvaExt = new CGMaterial();
    matCurvaExt->InitTexture("RectaStd.png");
    matCurvaExt->SetAmbientReflect(1.0f, 1.0f, 1.0f);
    matCurvaExt->SetDifusseReflect(1.0f, 1.0f, 1.0f);
    matCurvaExt->SetSpecularReflect(0.5f, 0.5f, 0.5f);
    matCurvaExt->SetShininess(32.0f);

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
void CGScene::Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view, glm::mat4 shadowViewMatrix)
{
    light->SetUniforms(program);
    
    matRecta->SetUniforms(program);
    matCurvaEst->SetUniforms(program);
    matCurvaExt->SetUniforms(program);
    matCurvaInt->SetUniforms(program);

    miCircuito->dibujar(program, proj, view, shadowViewMatrix);

    f1->Draw(program, proj, view, shadowViewMatrix);
    f2->Draw(program, proj, view, shadowViewMatrix);
}


glm::mat4 CGScene::GetLightViewMatrix()
{
    glm::vec3 Zdir = -(light->GetLightDirection());
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Xdir = glm::normalize(glm::cross(Up, Zdir));
    glm::vec3 Ydir = glm::cross(Zdir, Xdir);
    glm::vec3 Zpos = 150.0f * Zdir;
    glm::vec3 Center = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 view = glm::lookAt(Zpos, Center, Ydir);
    return view;
}
