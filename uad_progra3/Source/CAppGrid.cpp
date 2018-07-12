#include "..\Include\CAppGrid.h"




CAppGrid::CAppGrid()
{
	cout << "Constructor: CAppGrid()" << endl;
}

/* */
CAppGrid::CAppGrid(int window_width, int window_height) :
	CApp(window_width, window_height)
{
	cout << "Constructor: CAppGrid(int window_width, int window_height)" << endl;
}

CAppGrid::~CAppGrid()
{
	cout << "Destructor: ~CAppGrid()" << endl;
}

bool CAppGrid::initializeMenu()
{
	cout << "CAppGrid::initializeMenu()" << endl;

	return true;
}

void CAppGrid::initialize()
{
	// initialize del world
	m_pWorld = new CWorld();
	//m_pWorld->initialize();
}

void CAppGrid::update(double deltaTime)
{
}

void CAppGrid::run()
{
	initialize();

	// Check if CGameWindow object and window library been initialized
	if (canRun())
	{
		// Create the Window 
		if (getGameWindow()->create(CAPPHEXGRID_WINDOW_TITLE))
		{
			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.15f, 0.75f, 0.75f);
			// Initialize window width/height in the renderer
			getOpenGLRenderer()->setWindowWidth(getGameWindow()->getWidth());
			getOpenGLRenderer()->setWindowHeight(getGameWindow()->getHeight());
			// Initialize a test cube
			getOpenGLRenderer()->initializeTestObjects();

			// Create our menu (add all menu items)
			if (!initializeMenu())
			{
				return;
			}

			// Enter main loop
			cout << "Entering Main loop" << endl;
			getGameWindow()->mainLoop(this);
		}
	}
}

void CAppGrid::render()
{
	CGameMenu *menu = getMenu();

	// If menu is active, render menu
	if (menu != NULL && menu->isInitialized() && menu->isActive())
	{
		menu->render(getOpenGLRenderer());
	}
	else // Otherwise, render active object if loaded (or test cube if no object is loaded)
	{
		// White 
		float color[3] = { 1.0f, 1.0f, 1.0f };

		// render del world

		/*
		if (m_p3DModel != NULL && m_p3DModel->isInitialized())
		{
			// convert total degrees rotated to radians;
			double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;

			// Get a matrix that has both the object rotation and translation
			MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, m_objectPosition);

			getOpenGLRenderer()->renderObject(
				m_p3DModel->getShaderProgramId(),
				m_p3DModel->getGraphicsMemoryObjectId(),
				m_p3DModel->getTextureObjectId(),
				m_p3DModel->getNumFaces(),
				color,
				&modelMatrix,
				COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
				false
			);
		}*/
	}
}

void CAppGrid::executeMenuAction()
{
	if (getMenu() != NULL)
	{
	}
}

void CAppGrid::onMouseMove(float deltaX, float deltaY)
{
	if (deltaX < 100.0f && deltaY < 100.0f)
	{
	}
}