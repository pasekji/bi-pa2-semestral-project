#include "CPlayer.h"
#include "CGame.h"


void CPlayer::changeForm(const char& objectForm)
{
    m_objectForm = objectForm;
}

void CPlayer::defaultStep(int & move)
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