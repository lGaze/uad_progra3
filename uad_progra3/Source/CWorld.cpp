#include "..\Include\CWorld.h"

CWorld::CWorld()
{
	Grid = new CHexGrid();
}

CWorld::~CWorld()
{
}

bool CWorld::initialize(COpenGLRenderer* renderer)
{
	this->renderer = renderer;
	return Grid->initialize(renderer);
	
}

void CWorld::render(CVector3 CamPosition)
{
	float c[3] = { 204.0f, 0.0f, 51.0f };

	MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)0, CamPosition);

	renderer->renderWireframeObject(
		Grid->getWireframeID(),
		Grid->getArrayID(),
		4 * GRID_SIZE*GRID_SIZE,
		c,
		&modelMatrix
	);
}

