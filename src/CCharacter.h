#ifndef CHARACTER_H
#define CHARACTER_H

#include "CGameObject.h"

class CCharacter : public CGameObject
{
    protected:    

        CCharacter(WINDOW* objectSpace, int posY, int posX) : CGameObject(objectSpace, posY, posX)
        {}
        ~CCharacter(){}

        int m_speed;
        int m_currentHealth;
        int m_health;
        int m_currentEnergy;
        int m_energy;
        float m_chanceOfBlock;

    public:
        virtual int getAction() = 0;
};

#endif