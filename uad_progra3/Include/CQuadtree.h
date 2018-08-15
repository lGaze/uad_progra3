#pragma once

#include <iostream>
#include "../Include/CVector3.h"
#include "..\Include\CHexGrid.h"
#include "..\Include\CQuadtreeNode.h"

using namespace std;

class CQuadtree
{
public:

	CQuadtree();
	~CQuadtree();

	void buildQuadtree();
	void render();

private:
	
	CHexGrid * Hex;
	
};