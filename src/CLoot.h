#ifndef LOOT_H
#define LOOT_H

#include "CGameObject.h"
#include "CAttack.fwd.h"
#include "CPickup.fwd.h"
#include "CLoot.fwd.h"
#include <map>
#include <vector>
#include <random>

class CLoot : public CGameObject
{
    public:
        CLoot(WINDOW* objectSpace, int posY, int posX) : CGameObject(objectSpace, posY, posX)
        {
            m_objectForm = 'H';
            std::default_random_engine randomGenerator(rand());
            std::uniform_int_distribution<unsigned> rollSize(0, 4);
            m_items = rollSize(randomGenerator);
        }

        ~CLoot()
        {}

        bool pick()
        {
            if(m_items != 0)
            {
                m_items--;
                return true;
            }
            else 
                return false;
        }

        unsigned getItemsCount() const
        {
            return m_items;
        }


        bool acceptSource(CAttack* attack) override
        {
            return false;
        }

        bool updateSource(CAttack* attack) override
        {
            return false;
        }

        bool updateTarget(CAttack* attack) override
        {
            return false;
        }

        virtual string getTypeName()
        {
            return "CLoot";
        }

        void save(ofstream& os) override
        {
            os << getTypeName() << endl;
        }

        bool acceptTarget(CAttack* attack) override
        {
            return false;
        }

        void getLabel(std::string & label) const override
        {
            label = "BOX";
            return;
        } 

        void showStats() const override
        {
            return;
        }

        bool acceptSource(CPickup* pickup) override
        {
            return false;
        }
        bool acceptTarget(CPickup* pickup) override;
        bool updateSource(CPickup* pickup) override
        {
            return false;
        }

    private:
        unsigned m_items;
};

#endif