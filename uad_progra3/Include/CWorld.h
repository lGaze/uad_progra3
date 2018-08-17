#pragma once
#include "CHexGrid.h"

class CWorld
{
public:
	CWorld();
	~CWorld();
	bool initialize(COpenGLRenderer * renderer);
	void render(CVector3 CamPosition);

	bool initializeTexture();
	bool loadTexture(const char *filename, unsigned int *newTextureID);
	void initializeHexTexture();

private:

	unsigned int ShaderProgramID;
	unsigned int m_TextureID;
	CHexGrid * Grid;
	COpenGLRenderer* renderer;
};
