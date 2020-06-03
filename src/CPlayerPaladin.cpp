#include "CPlayerPaladin.h"
#include "CApplication.h"


extern CApplication application;

CPlayerPaladin::CPlayerPaladin(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX)
{
    halfdelay(1);
    m_inventorySize = 20;
    m_speed = 1;
    m_inventory = new CInventory(m_inventorySize);
}

int CPlayerPaladin::getAction()
{
    int move, tmppos, tmpstep;
    direction tmpdir;
    std::pair<int, int> pair;

    defaultStep(move);                  // sprint is not availiable with paladin

    switch (move) 
    {
        case KEY_UP:
            tmpstep = 1;

            while((!application.getGame().getMap()->colisionDetect(pair = std::make_pair(tmppos = m_posY - tmpstep, m_posX))) && (tmpstep <=  m_speed))
                tmpstep++;

            tmpstep--;
            moveUp(tmpstep);
            application.getGame().getMap()->staticCamera(tmpdir = UP, tmpstep);
            changeForm('^');
            break;
        case KEY_DOWN:
            tmpstep = 1;

            while((!application.getGame().getMap()->colisionDetect(pair = std::make_pair(tmppos = m_posY + tmpstep, m_posX))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveDown(tmpstep);
            application.getGame().getMap()->staticCamera(tmpdir = DOWN, tmpstep);
            changeForm('v');
            break;
        case KEY_LEFT:
            tmpstep = 1;

            while((!application.getGame().getMap()->colisionDetect(pair = std::make_pair(m_posY, tmppos = m_posX - tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveLeft(tmpstep);
            application.getGame().getMap()->staticCamera(tmpdir = LEFT, tmpstep);
            changeForm('<');
            break;
        case KEY_RIGHT:
            tmpstep = 1;

            while((!application.getGame().getMap()->colisionDetect(pair = std::make_pair(m_posY, tmppos = m_posX + tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveRight(tmpstep);
            application.getGame().getMap()->staticCamera(tmpdir = RIGHT, tmpstep);
            changeForm('>');
            break;
        default:
            break;
    }

    return move;
}

bool CPlayerPaladin::interactWith()
{
    //TODO
    return false;
}