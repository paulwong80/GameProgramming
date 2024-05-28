#include "Game.h"
#include <fstream>
#include "Input.h"
#define ROTATION 1.5
void Game::init(const std::string& path)
{
	// TODO: read the config file here
	std::ifstream fin(path);
	std::string temp;
	bool isFullScreen=false;
	while (fin>>temp)
	{
		if (temp == "Window")
		{
			fin >> width >> height >> frameRate >> isFullScreen;
		}
		if (temp == "Player")
		{
			fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR 
				>> m_playerConfig.FG >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG 
				>> m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V;
		}
		if (temp == "Enemy")
		{
			fin >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG
				>> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX
				>> m_enemyConfig.L >> m_enemyConfig.SI ;
		}
		if (temp == "Bullet")
		{
			fin >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR >> m_bulletConfig.FG
				>> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB
				>> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L ;
		}
	}
	// glfwCreate window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	if (isFullScreen)
	{
		m_window = glfwCreateWindow(width, height, "Assignment2", glfwGetPrimaryMonitor(), NULL);
	}
	else {
		m_window = glfwCreateWindow(width, height, "Assignment2", NULL, NULL);
	}
	glfwMakeContextCurrent(m_window);
	glewInit();
	glfwSetKeyCallback(m_window, KeyCallback);
	glfwSetCursorPosCallback(m_window, MouseCallback);
	m_entities = EntityManager();
	spawnPlayer();
}

void Game::sMovement()
{
}

void Game::sLifespan()
{
}

void Game::spawnPlayer()
{
	auto e = m_entities.addEntity("Player");
	e->cTransform = std::make_shared<CTransform>(Vec2(0,0), Vec2(0,0), 10.0f);
	e->cShape = std::make_shared<CShape>(m_playerConfig.SR/float(width/2), m_playerConfig.V, Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OG), m_playerConfig.OT);

}

void Game::sEnemySpawner()
{
}

void Game::sCollision()
{
}

void Game::sUserInput()
{
	auto e = m_entities.getEntities("Player");
	float speed = m_playerConfig.S;
	Vec2 temp = e[0]->cShape->ptr_Mesh->getPosition();
	if (keys[GLFW_KEY_W] )
	{
		e[0]->cShape->ptr_Mesh->setPosition(temp.x, temp.y + speed * 0.002);
	}
	if (keys[GLFW_KEY_S] )
	{
		e[0]->cShape->ptr_Mesh->setPosition(temp.x, temp.y - speed * 0.002);
	}
	if (keys[GLFW_KEY_A] )
	{
		e[0]->cShape->ptr_Mesh->setPosition(temp.x - speed * 0.002, temp.y );
	}
	if (keys[GLFW_KEY_D])
	{
		e[0]->cShape->ptr_Mesh->setPosition(temp.x + speed * 0.002, temp.y);
	}
}

void Game::sGUI()
{
}

void Game::sRender()
{
	for  (auto e : m_entities.getEntities())
	{
		float t = glfwGetTime() * ROTATION;
		e->cShape->ptr_Mesh->setRotation(t);
		e->cShape->ptr_Mesh->Draw();
	}
}

void Game::setPaused(bool paused)
{
}

void Game::spawnEnemy()
{
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> e)
{
}

Game::Game(const std::string& config)
{
	init(config);
}

void Game::run()
{
	//TODO: add pause functionality in here rendering should pause but movement input not
	const char* glsl_version = "#version 330";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(m_window, &screenWidth, &screenHeight);
	while (m_running && !glfwWindowShouldClose(m_window) )
	{
		m_entities.update();
		glfwPollEvents();
		glViewport(0, 0, screenWidth, screenHeight);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (m_ui_window)
		{
			ImGui::Begin("Shape Properties", &m_ui_window);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}
		// Rendering
		ImGui::Render();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		sEnemySpawner();
		sMovement();
		sCollision();
		sUserInput();
		sRender();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_window);
	}
}
