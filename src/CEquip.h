#ifndef EQUIP_H
#define EQUIP_H

#include "CEvent.h"
#include "CItem.h"
#include "CWeapon.fwd.h"
#include "CConsumable.h"

class CEquip : public CEvent
{
    public:
        CEquip(std::shared_ptr<CGameObject> source, std::shared_ptr<CItem> item);
        virtual ~CEquip() = default;
        void print() override;
        void updateObjects() override;

        void visitSource(std::shared_ptr<CPlayer> player);

        std::shared_ptr<CEquip> getPtr()
        {
            return m_sharedThis;
        }

    private:

        void evaluateEquip(std::shared_ptr<CPlayer> player);
        std::shared_ptr<CEquip> m_sharedThis;
        std::shared_ptr<CItem> m_item;
        bool m_success = false;
        bool m_isSomething = false;
        int m_forceBenefit;
        int m_healthBenefit;
        int m_energyRegainBenefit;
        int m_energyForStepLoss;

};

#endif