#ifndef EQUIP_H
#define EQUIP_H

#include "CEvent.h"
#include "CItem.h"
#include "CWeapon.fwd.h"
#include "CConsumable.h"

class CEquip : public CEvent
{
    public:
        CEquip(CGameObject* source, CItem* item);
        virtual ~CEquip() = default;
        void print() override;
        void updateObjects() override;

        void visitSource(CPlayer* player);

        CEquip* getPtr();

    private:

        void evaluateEquip(CPlayer* player);
        CItem* m_item;
        bool m_success = false;
        bool m_isSomething = false;
        int m_forceBenefit;
        int m_healthBenefit;
        int m_energyRegainBenefit;
        int m_energyForStepLoss;

};

#endif