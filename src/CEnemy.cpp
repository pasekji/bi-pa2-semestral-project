#include "CEnemy.h"
#include "CApplication.h"


extern CApplication application;

int CEnemy::getAction()     // just demo testing - TODO - AI 
{
    int action = rand() % 6;
    int tmppos, tmpstep;
    std::pair<int, int> pair;


    switch (action) 
    {
        case 0:
            break;
        case 1:
            break;
        case 2:
            tmpstep = 1;

            while((!application.getGame().getMap()->colisionDetect(pair = std::make_pair(tmppos = m_posY - tmpstep, m_posX))) && (tmpstep <=  m_speed))
                tmpstep++;

            tmpstep--;
            moveUp(tmpstep);
            break;
        case 3:
            tmpstep = 1;

            while((!application.getGame().getMap()->colisionDetect(pair = std::make_pair(tmppos = m_posY + tmpstep, m_posX))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveDown(tmpstep);
            break;
        case 4:
            tmpstep = 1;

            while((!application.getGame().getMap()->colisionDetect(pair = std::make_pair(m_posY, tmppos = m_posX - tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveLeft(tmpstep);
            break;
        case 5:
            tmpstep = 1;

            while((!application.getGame().getMap()->colisionDetect(pair = std::make_pair(m_posY, tmppos = m_posX + tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveRight(tmpstep);
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
