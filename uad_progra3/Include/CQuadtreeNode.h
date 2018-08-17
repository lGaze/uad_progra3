#pragma once

#include <iostream>
#include "CVector3.h"
#include <vector>
#include "..\Include\CHexCell.h"

#define LIMITOFCELLS 4

using namespace std;

class CQuadTreeNode
{
private:

	CVector3 Edges[4];
	vector<CHexCell*> Cells;
	void render();
	CVector3 centro;
	float width;
	float hight;
	CQuadTreeNode * Children[4];
	vector<CVector3> positions;

public:

	CQuadTreeNode(CVector3 centro, float x, float y);
	~CQuadTreeNode();
	void subdivide();
	bool isInside(CVector3 pos);
    void insert(CHexCell * celda, CVector3 pos);
	bool isDivided = false;

	

};