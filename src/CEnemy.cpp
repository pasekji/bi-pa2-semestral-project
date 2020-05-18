#include "CEnemy.h"
#include "CGame.h"


extern CGame game;

int CEnemy::getAction()     // just demo testing - TODO - AI 
{
    int action = rand() % 5;
    int tmppos;
    switch (action) 
    {
        case 0:
            break;
        case 1:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY - m_speed, m_posX))
                moveUp();
            break;
        case 2:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY + m_speed, m_posX))
                moveDown();
            break;
        case 3:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX - (m_speed + 1)))
                moveLeft();
            break;
        case 4:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX + (m_speed + 1)))
                moveRight();
        default:
            break;
    }

    return action;
}

bool CEnemy::interactWith()
{
    //TODO
    return false;
}
