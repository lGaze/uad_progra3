#include "..\Include\CQuadtreeNode.h"
#include "..\Include\MathHelper.h"

void CQuadTreeNode::render()
{
	//aqui se renderea de forma recursiva 

	if (isDivided)
	{
		for (int i = 0; i < 4; i++)
		{
			Children[i]->render();
		}
	}
	else
	{
		for (int i = 0; i < Cells.size(); i++)
		{
			//rendereado...
		}
	}
}

CQuadTreeNode::CQuadTreeNode(CVector3 centro, float x, float y)
{
	this->centro = centro;
	this->width = x;
	this->hight = y;
}

CQuadTreeNode::~CQuadTreeNode()
{
	

}

void CQuadTreeNode::subdivide()
{
	CVector3 newCenter;
	
	float wSize = width / 2;
	float hSize = hight / 2;
	newCenter = centro + CVector3(-width / 4, 0.0f, hight / 4);
	Children[0] = new CQuadTreeNode(newCenter, wSize, hSize);
	newCenter = centro + CVector3(width / 4, 0.0f, hight / 4);
	Children[1] = new CQuadTreeNode(newCenter, wSize, hSize);
	newCenter = centro + CVector3(-width / 4, 0.0f, -hight / 4);
	Children[2] = new CQuadTreeNode(newCenter, wSize, hSize);
	newCenter = centro + CVector3(width / 4, 0.0f, -hight / 4);
	Children[3] = new CQuadTreeNode(newCenter, wSize, hSize);
	isDivided = true;

	for (int i = 0; i < Cells.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Children[j]->isInside(positions[i]))
			{
				Children[j]->insert(Cells[i], positions[i]);
				break;
			}
		}
	}
}

bool CQuadTreeNode::isInside(CVector3 pos)
{
	return (pos.X >= centro.X - width / 2 &&
		pos.X < centro.X + width / 2 &&
		pos.Y >= centro.Y - hight / 2 &&
		pos.Y < centro.Y + hight / 2);
		
}

void CQuadTreeNode::insert(CHexCell * celda, CVector3 pos)
{
	if (Cells.size() >= LIMITOFCELLS)
	{
		if (!isDivided)
		{
			subdivide();
		}

		for (int i = 0; i < 4; i++)
		{
			if (Children[i]->isInside(pos))
			{
				Children[i]->insert(celda, pos);
				break;
			}
		}

	}
	else
	{
		Cells.push_back(celda);
		positions.push_back(pos);
	}
	
}
