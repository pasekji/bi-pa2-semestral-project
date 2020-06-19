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

        bool acceptSource(CAttack* attack) override
        {
            return false;
        }

        bool acceptTarget(CAttack* attack) override
        {
            return false;
        }

        void showStats() const override
        {
            return;
        }
        
        void getLable(std::string & lable) const override
        {
            return;
        } 
        virtual string getTypeName()
        {
            return "CDoor";
        }
};

#endif