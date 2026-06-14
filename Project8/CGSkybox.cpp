#include "CGSkybox.h"
#include <GL/glew.h>
#include <Windows.h>
#include "resource.h"
#include <FreeImage.h>



CGSkybox::CGSkybox()
{
	InitCubemap();
	InitCube();
}

CGSkybox::~CGSkybox()
{
	glDeleteBuffers(2, VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &cubemap);
}

void CGSkybox::Draw(CGShaderProgram* program, glm::mat4 projection, glm::mat4 view)
{
	glm::mat3 rot3 = glm::mat3(view);
	glm::mat4 rot4 = glm::mat4(rot3);
	glm::mat4 mvp = projection * rot4;
	glm::mat4 inv = glm::inverse(mvp);

	program->SetUniformMatrix4("Inverse", inv);
	program->SetUniformI("CubemapTex", 0);

	glDepthMask(GL_FALSE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
	glDepthMask(GL_TRUE);
}


void CGSkybox::InitCube()
{
	GLfloat vertices[12] = {
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f
	};

	GLushort indexes[6] = {
		0,1,2,
		0,2,3
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 6, indexes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

}

void CGSkybox::InitCubemap()
{
	glActiveTexture(GL_TEXTURE1);

	glGenTextures(1, &cubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

	InitTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X, "textures/posx.jpg");
	InitTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "textures/negx.jpg");
	InitTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "textures/posy.jpg");
	InitTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "textures/negy.jpg");
	InitTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "textures/posz.jpg");
	InitTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "textures/negz.jpg");

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CGSkybox::InitTexture(GLuint target, const char* filename)
{
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);

	FreeImage_FlipVertical(pImage);

	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);

	glTexImage2D(target, 0, GL_RGBA8, nWidth, nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

	FreeImage_Unload(pImage);

}

void CGSkybox::InitTexture(GLuint target, int idr)
{
	HRSRC handle = FindResource(NULL, MAKEINTRESOURCE(idr), L"IMAGE");
	HGLOBAL hGlobal = LoadResource(NULL, handle);
	LPCTSTR rsc_ptr = static_cast<LPCTSTR>(LockResource(hGlobal));
	DWORD mem_size = SizeofResource(NULL, handle);
	BYTE* mem_buffer = (BYTE*)malloc((mem_size) * sizeof(BYTE));
	memcpy(mem_buffer, rsc_ptr, mem_size * sizeof(BYTE));
	FreeResource(hGlobal);

	FIMEMORY* hmem = FreeImage_OpenMemory(mem_buffer, mem_size * sizeof(BYTE));
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(hmem, 0);
	FIBITMAP* check = FreeImage_LoadFromMemory(fif, hmem, 0);
	FIBITMAP* pImage = FreeImage_ConvertTo32Bits(check);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);

	glTexImage2D(target, 0, GL_RGBA8, nWidth, nHeight,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

	FreeImage_Unload(pImage);
	FreeImage_CloseMemory(hmem);
	free(mem_buffer);
}
