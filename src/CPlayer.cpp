#include "CPlayer.h"
#include "CApplication.h"

extern CApplication application;

void CPlayer::changeForm(const char & objectForm)
{
    m_objectForm = objectForm;
}

void CPlayer::defaultStep(int & move)       // basic player movement, every class has it..
{
    int tmpmove;
    int delay = 0;
    if((move = wgetch(m_objectSpace)) != ERR)
    {
        do
        {
            if(delay == 3)
                break;
                
            tmpmove = wgetch(m_objectSpace);
            delay++;
        } 
        while((tmpmove == move) || (tmpmove != ERR));
    }

}

bool CPlayer::defaultMove(int & move)
{
    // if default speed and delay move up, down etc...

    int tmppos, tmpstep;
    direction tmpdir;
    std::pair<int, int> pair;
    bool used = false;

    switch (move) 
    {
        case KEY_UP:
            tmpstep = 1;

            while((!application.getGame().getMap()->collisionDetect(pair = std::make_pair(tmppos = m_posY - tmpstep, m_posX))) && (tmpstep <=  m_speed))
                tmpstep++;

            tmpstep--;
            moveUp(tmpstep);
            m_posY_real -= tmpstep;
            application.getGame().getMap()->staticCamera(tmpdir = UP, tmpstep);
            changeForm('^');
            used = true;
            break;

        case KEY_DOWN:
            tmpstep = 1;

            while((!application.getGame().getMap()->collisionDetect(pair = std::make_pair(tmppos = m_posY + tmpstep, m_posX))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveDown(tmpstep);
            m_posY_real += tmpstep;
            application.getGame().getMap()->staticCamera(tmpdir = DOWN, tmpstep);
            changeForm('v');
            used = true;
            break;

        case KEY_LEFT:
            tmpstep = 1;

            while((!application.getGame().getMap()->collisionDetect(pair = std::make_pair(m_posY, tmppos = m_posX - tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveLeft(tmpstep);
            m_posX_real -= tmpstep;
            application.getGame().getMap()->staticCamera(tmpdir = LEFT, tmpstep);
            changeForm('<');
            used = true;
            break;

        case KEY_RIGHT:
            tmpstep = 1;

            while((!application.getGame().getMap()->collisionDetect(pair = std::make_pair(m_posY, tmppos = m_posX + tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveRight(tmpstep);
            m_posX_real += tmpstep;
            application.getGame().getMap()->staticCamera(tmpdir = RIGHT, tmpstep);
            changeForm('>');
            used = true;
            break;

        default:
            break;
    }

    return used;
}

