#include "..\Include\CQuadtree.h"


CQuadtree::CQuadtree()
{
}

CQuadtree::~CQuadtree()
{
}

void CQuadtree::buildQuadtree()
{
	CVector3 pos;
	pos.setValues(0.0f, 0.0f, 0.0f);

	root = new CQuadTreeNode(pos,100.0f,100.0f);
}

void CQuadtree::render()
{
}
