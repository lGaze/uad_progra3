#pragma once
#include "CHexGrid.h"

class CWorld
{
public:
	CWorld();
	~CWorld();
	bool initialize(COpenGLRenderer * renderer);
	void render();
private:
	CHexGrid * Grid;
	COpenGLRenderer* renderer;
};
