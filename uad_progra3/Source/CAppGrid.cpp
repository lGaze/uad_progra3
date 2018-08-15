#include "..\Include\CAppGrid.h"
#include "../Include/LoadTGA.h"


CAppGrid::CAppGrid():
	m_CmPosition(-5,-5,-7)
{
	cout << "Constructor: CAppGrid()" << endl;

	m_pWorld = new CWorld();
}

/* */
CAppGrid::CAppGrid(int window_width, int window_height) :
	CApp(window_width, window_height)
{
	cout << "Constructor: CAppGrid(int window_width, int window_height)" << endl;

	m_pWorld = new CWorld();
}

CAppGrid::~CAppGrid()
{
	cout << "Destructor: ~CAppGrid()" << endl;
}

bool CAppGrid::loadTexture(const char * filename, unsigned int * newTextureID)
{
	TGAFILE tgaFile;
	tgaFile.imageData = nullptr;

	if (filename == nullptr || newTextureID == nullptr)
	{
		return false;
	}

	*newTextureID = 0;

	if (LoadTGAFile(filename, &tgaFile))
	{
		if (tgaFile.imageData == nullptr ||
			tgaFile.imageHeight < 0 ||
			tgaFile.imageWidth < 0)
		{
			if (tgaFile.imageData != nullptr)
			{
				delete[] tgaFile.imageData;
			}

			return false;
		}

		// Create a texture object for the menu, and copy the texture data to graphics memory
		if (!getOpenGLRenderer()->createTextureObject(
			newTextureID,
			tgaFile.imageData,
			tgaFile.imageWidth,
			tgaFile.imageHeight
		))
		{
			return false;
		}

		// Texture data is stored in graphics memory now, we don't need this copy anymore
		if (tgaFile.imageData != nullptr)
		{
			delete[] tgaFile.imageData;
		}
	}
}

bool CAppGrid::initializeMenu()
{
	cout << "CAppGrid::initializeMenu()" << endl;

	return true;
}

void CAppGrid::initialize()
{	
	
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

			m_pWorld->initialize(getOpenGLRenderer());
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
		m_pWorld->render(m_CmPosition);		/*
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
		float moveX = -deltaX * DEFAULT_CAMERA_MOVE_SPEED;
		float moveZ = -deltaY * DEFAULT_CAMERA_MOVE_SPEED;

		float currPos[3];
		m_CmPosition.getValues(currPos);
		currPos[0] += moveX;
		currPos[2] += moveZ;
		m_CmPosition.setValues(currPos);
	}
}

void CAppGrid::moveCamera(float direction)
{
	if (getOpenGLRenderer() != NULL)
	{
		getOpenGLRenderer()->moveCamera(direction);
	}
}