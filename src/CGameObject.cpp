#include "CGameObject.h"

void CGameObject::objectRender()
{ 
    mvwaddch(m_objectSpace, m_posY, m_posX, m_objectForm);
}