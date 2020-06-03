#ifndef CHARACTER_H
#define CHARACTER_H

#include "CGameObject.h"
#include "enums.h"


class CCharacter : public CGameObject
{
    protected:    

        CCharacter(WINDOW* objectSpace, int posY, int posX) : CGameObject(objectSpace, posY, posX)
        {}
        ~CCharacter(){}

        int m_speed;
        int m_health;
        int m_energy;
        float m_chanceOfBlock;

    public:
        virtual int getAction() = 0;
};

#endif