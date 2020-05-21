#include "CGameObject.h"
#include "CGame.h"

extern CGame game;

CGameObject::CGameObject(WINDOW * objectSpace, int posY, int posX) : m_objectSpace(objectSpace), m_posY(posY), m_posX(posX)
{}

CGameObject::CGameObject(WINDOW * objectSpace, int posY, int posX, char & objectForm) : m_objectSpace(objectSpace), m_posY(posY), m_posX(posX), m_objectForm(objectForm)
{}

void CGameObject::objectRender()
{ 
    mvwaddch(m_objectSpace, m_posY, m_posX, m_objectForm);
}

void CGameObject::cameraUp()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posY -= 1;
}

void CGameObject::cameraDown()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posY += 1;
}

void CGameObject::cameraLeft()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posX -= 2;
}

void CGameObject::cameraRight()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posX += 2;
}