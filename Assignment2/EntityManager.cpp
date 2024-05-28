#include "EntityManager.h"

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	for (auto e : vec)
	{
		if (!e->isAcitve())
		{
			std::erase(vec, e);
		}
	}
}

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
	for	(auto e:m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}
	removeDeadEntities(m_entities);
	for ( auto& [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto e = std::shared_ptr<Entity> (new Entity(m_totalEntities++, tag));
	m_entitiesToAdd.push_back(e);
	return e;
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
