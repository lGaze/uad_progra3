#pragma once
#ifndef CAPPGRID_H
#define CAPPGRID_H

#include "Globals.h"
#include "CApp.h"
#include "CVector3.h"
#include "..\Include\CWorld.h"


// Class that inherits from Base class CApp
// Base class CApp has members for: CGameWindow, CGameMenu, and COpenGLRenderer, which we can access through the public/protected methods
class CAppGrid : public CApp
{
private:
	CWorld *m_pWorld;

protected:
	// Method to initialize the menu
	bool initializeMenu();

public:
	// Constructors and destructor
	CAppGrid();
	CAppGrid(int window_width, int window_height);
	~CAppGrid();

	// Inherited methods from CApp
	// ---------------------------

	// Method to initialize any objects for this class
	void initialize();

	// Method to update any objecs based on time elapsed since last frame
	void update(double deltaTime);

	// Method to run the app
	void run();

	// Method to render the app
	void render();

	// Executes the action corresponding to the selected menu item
	void executeMenuAction();

	// Methods specific to CAppParcial2 only
	// -------------------------------------

	void onMouseMove(float deltaX, float deltaY);
};

#endif // !CAPPGRID_H
