#include "EntityManager.h"

void EntityManager::removeDeadEntities(EntityVec& vec)
{
}

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	return std::shared_ptr<Entity>();
}

const EntityVec& EntityManager::getEntities()
{
	// TODO: insert return statement here
	return m_entities;
}

const EntityVec& EntityManager::getEntities(const std::string& tag)
{
	// TODO: insert return statement here
	return m_entityMap[tag];
}

const std::map<std::string, EntityVec>& EntityManager::getEntityMap()
{
	// TODO: insert return statement here
	return m_entityMap;
}
