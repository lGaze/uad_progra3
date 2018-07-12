#pragma once
#include "CVector3.h"

class CHexCell
{
public:


	CHexCell(float Centro_X, float Centro_Y);
	~CHexCell();
	float centro_X, centro_Y;
	CHexCell * Cell;
	CVector3 Vert[6];

	void CalculateVert(float radio, float cellsize);
};