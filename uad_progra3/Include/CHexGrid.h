#pragma once
#include <iostream>
#include "CVector3.h"
#include <vector>
#include "CHexCell.h"
#include "COpenGLRenderer.h"
#include "CWideStringHelper.h"
#include "Globals.h"
using namespace std;
#define GRID_SIZE 1

class CHexGrid
{
public:

	
	CHexGrid();
	~CHexGrid();
	void buildGrid(float cellsize); //cellsize - s
	bool initialize(COpenGLRenderer* render);
	
	unsigned int* getWireframeID();
	unsigned int* getArrayID();


private:

	float * Vertex;
	int First_CenterX, First_CenterY;
	CHexCell * m_pCeldas[GRID_SIZE][GRID_SIZE];
	unsigned short vindex[4 * 3 * GRID_SIZE*GRID_SIZE];
	unsigned int WireframeID;
	unsigned int ArrayID;
	void reset();
};