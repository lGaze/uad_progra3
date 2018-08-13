#pragma once
#include "CHexGrid.h"

class CWorld
{
public:
	CWorld();
	~CWorld();
	bool initialize(COpenGLRenderer * renderer);
	void render(CVector3 CamPosition);

	CVector3 m_objectPosition;
private:
	CHexGrid * Grid;
	COpenGLRenderer* renderer;
};
