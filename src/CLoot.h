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
        CLoot(int posY, int posX) : CGameObject(posY, posX)
        {
            m_sharedThis.reset(this);
            m_objectForm = 'H';
            std::default_random_engine randomGenerator(rand());
            std::uniform_int_distribution<unsigned> rollSize(0, 4);
            m_items = rollSize(randomGenerator);
        }

        virtual ~CLoot() = default;

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


        bool acceptSource(std::shared_ptr<CAttack> attack) override
        {
            return false;
        }

        bool updateSource(std::shared_ptr<CAttack> attack) override
        {
            return false;
        }

        bool updateTarget(std::shared_ptr<CAttack> attack) override
        {
            return false;
        }

        virtual string getTypeName()
        {
            return "CLoot";
        }
        
        bool acceptTarget(std::shared_ptr<CAttack> attack) override
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

        bool acceptSource(std::shared_ptr<CPickup> pickup) override
        {
            return false;
        }

        bool acceptSource(std::shared_ptr<CEquip> equip) override
        {
            return false;
        }

        bool acceptTarget(std::shared_ptr<CPickup> pickup) override;
        bool updateSource(std::shared_ptr<CPickup> pickup) override
        {
            return false;
        }

        std::shared_ptr<CLoot> getPtr()
        {
            return m_sharedThis;
        }

        virtual void save(std::ofstream & os)
        {}

    private:
        std::shared_ptr<CLoot> m_sharedThis;
        unsigned m_items;
};

#endif