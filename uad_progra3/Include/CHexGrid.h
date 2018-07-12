#pragma once
#include <iostream>
#include "CVector3.h"
#include <vector>
#include "CHexCell.h"
#include "COpenGLRenderer.h"
#include "CWideStringHelper.h"
#include "Globals.h"
using namespace std;
#define GRID_SIZE 3

class CHexGrid
{
public:

	
	CHexGrid();
	~CHexGrid();
	void buildGrid(float cellsize); //cellsize - s
	void initialize(COpenGLRenderer* render);
private:

	float * Vertex;
	int First_CenterX, First_CenterY;
	CHexCell * m_pCeldas[GRID_SIZE][GRID_SIZE];
	unsigned int WireframeID;
	unsigned int ArrayID;
	int vindex[4 * 3 * GRID_SIZE*GRID_SIZE];
};