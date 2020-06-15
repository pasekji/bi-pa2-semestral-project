#ifndef DOOR_H
#define DOOR_H

#include "CGameObject.h"

class CDoor : public CGameObject
{
    public:
        CDoor(WINDOW* objectSpace, int posY, int posX) : CGameObject(objectSpace, posY, posX)
        {
            m_objectForm = 'D';
        }
        ~CDoor()
        {}

        bool interactWith() override
        {
            return false;
        }

        bool accept(CAttack* attack) override
        {
            return false;
        }

        void showStats() const override
        {
            return;
        }


};

#endif