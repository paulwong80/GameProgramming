#include "Entity.h"

bool Entity::isAcitve() const
{
    return false;
}

const std::string& Entity::tag() const
{
    // TODO: insert return statement here
    return m_tag;
}

const size_t Entity::id() const
{
    return size_t();
}

void Entity::destroy()
{
}
