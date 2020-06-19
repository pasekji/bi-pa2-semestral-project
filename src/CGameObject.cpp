#include "CGameObject.h"
#include "CGame.h"
#include <string>

CGameObject::CGameObject(WINDOW * objectSpace, int posY, int posX) : m_objectSpace(objectSpace), m_posY(posY), m_posX(posX)
{}

CGameObject::CGameObject(WINDOW * objectSpace, int posY, int posX, const char & objectForm) : m_objectSpace(objectSpace), m_posY(posY), m_posX(posX), m_objectForm(objectForm)
{}

void CGameObject::objectRender()
{ 
    mvwaddch(m_objectSpace, m_posY, m_posX, m_objectForm);
}

void CGameObject::moveUp(int & steps)
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posY -= steps;
}

void CGameObject::moveDown(int & steps)
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posY += steps;
}

void CGameObject::moveLeft(int & steps)
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posX -= steps;
}

void CGameObject::moveRight(int & steps)
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posX += steps;
}

std::pair<int, int> & CGameObject::getPos()
{
    pair = std::make_pair(m_posY, m_posX);
    return pair;
}

CGameObject* loadGameObject(ifstream& is, WINDOW* objectSpace)
{
    string typeName;
    is >> typeName;
    if (typeName == "CProp") {
        return CProp::loadGameObject(is, objectSpace);
    }
    else if (typeName == "CEnemy")
    {
        return loadEnemy(is, objectSpace);
    }
    else if (typeName == "CPlayerMage")
    {
        return loadPlayerMage(is, objectSpace);
    }
}