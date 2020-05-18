#include "CCharacter.h"

void CCharacter::moveUp()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posY -= m_speed;
    if (m_posY < 1)
    {
        m_posY = 1;
    }
}

void CCharacter::moveDown()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posY += m_speed;
    if (m_posY > m_posY_Max - 2)            // because of the border -> border is m_posY_Max - 1, so one spot before the border is m_posY_Max - 2
    {                                   
        m_posY = m_posY_Max - 2;
    }
}

void CCharacter::moveLeft()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posX -= (m_speed + 1);
    if (m_posX < 1)
    {
        m_posX = 1;
    }
}

void CCharacter::moveRight()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posX += (m_speed + 1);
    if (m_posX > m_posX_Max - 2)
    {
        m_posX = m_posX_Max - 2;
    }
}