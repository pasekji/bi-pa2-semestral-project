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
        CLoot(int posY, int posX);

        virtual ~CLoot() = default;

        bool pick();

        unsigned getItemsCount() const;

        bool acceptSource(CAttack* attack) override;

        bool updateSource(CAttack* attack) override;

        bool updateTarget(CAttack* attack) override;

        virtual string getTypeName();
        
        bool acceptTarget(CAttack* attack) override;

        void getLabel(std::string & label) const override;

        void showStats() const override;

        bool acceptSource(CPickup* pickup) override;

        bool acceptSource(CEquip* equip) override;

        bool acceptTarget(CPickup* pickup) override;
        bool updateSource(CPickup* pickup) override;

        CLoot* getPtr();

        virtual void save(std::ofstream & os);

    private:
        CLoot* m_sharedThis;
        unsigned m_items;
};

#endif