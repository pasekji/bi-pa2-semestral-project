#include "CPlayerPaladin.h"
#include "CGame.h"


extern CGame game;

int CPlayerPaladin::getAction()
{
    int move = wgetch(m_objectSpace);
    int tmppos;
    direction tmpdir;
    switch (move) 
    {
        case KEY_UP:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY - m_speed, m_posX))
            {
                moveUp();
                game.m_currentMap->staticCamera(tmpdir = UP);
            }
            changeForm('^');
            break;
        case KEY_DOWN:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY + m_speed, m_posX))
            {
                moveDown();
                game.m_currentMap->staticCamera(tmpdir = DOWN);
            }
            changeForm('v');
            break;
        case KEY_LEFT:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX - (m_speed + 1)))
            {
                moveLeft();
                game.m_currentMap->staticCamera(tmpdir = LEFT);
            }
            changeForm('<');
            break;
        case KEY_RIGHT:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX + (m_speed + 1)))
            {
                moveRight();
                game.m_currentMap->staticCamera(tmpdir = RIGHT);
            }
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