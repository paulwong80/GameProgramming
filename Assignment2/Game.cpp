#include "Game.h"

void Game::init(const std::string& path)
{
	// TODO: read the config file here
	// glfwCreate window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	m_window = glfwCreateWindow(1280, 720, "Assignment2", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	glewInit();
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
}

void Game::sEnemySpawner()
{
}

void Game::sCollision()
{
}

void Game::sUserInput()
{
}

void Game::sGUI()
{
}

void Game::sRender()
{
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

	while (m_running && !glfwWindowShouldClose(m_window))
	{
		m_entities.update();
		glfwPollEvents();
		glViewport(0, 0, 1280, 720);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		sEnemySpawner();
		sMovement();
		sCollision();
		sUserInput();
		sRender();

		glfwSwapBuffers(m_window);
	}
}
