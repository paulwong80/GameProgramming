#pragma once
#include "EntityManager.h"
#include "GLFW/glfw3.h"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };


class Game
{
	GLFWwindow* m_window;
	EntityManager m_entities;
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;
	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	bool m_running = true;
	bool m_paused;

	std::shared_ptr<Entity> m_player;

	void init(const std::string& path);
	void sMovement();
	void sLifespan();
	void spawnPlayer();
	void sEnemySpawner();
	void sCollision();
	void sUserInput();
	void sGUI();
	void sRender();
	void setPaused(bool paused);
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> e);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> e);

public:
	Game(const std::string& config);
	
	void run();

};

