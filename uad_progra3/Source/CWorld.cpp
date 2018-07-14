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

void CWorld::render()
{
	float c[3] = { 255.0f, 160.0f, 16.0f };
	MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)0, CVector3(-8, -8, -17));
	//MthHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, m_objectPosition);
	renderer->renderWireframeObject(
		Grid->getWireframeID(),
		Grid->getArrayID(),
		4 * GRID_SIZE*GRID_SIZE,
		c,
		&modelMatrix
	);
}
