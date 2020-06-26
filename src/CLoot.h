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

        bool acceptSource(std::shared_ptr<CAttack> attack) override;

        bool updateSource(std::shared_ptr<CAttack> attack) override;

        bool updateTarget(std::shared_ptr<CAttack> attack) override;

        virtual string getTypeName();
        
        bool acceptTarget(std::shared_ptr<CAttack> attack) override;

        void getLabel(std::string & label) const override;

        void showStats() const override;

        bool acceptSource(std::shared_ptr<CPickup> pickup) override;

        bool acceptSource(std::shared_ptr<CEquip> equip) override;

        bool acceptTarget(std::shared_ptr<CPickup> pickup) override;
        bool updateSource(std::shared_ptr<CPickup> pickup) override;

        std::shared_ptr<CLoot> getPtr();

        virtual void save(std::ofstream & os);

    private:
        std::shared_ptr<CLoot> m_sharedThis;
        unsigned m_items;
};

#endif