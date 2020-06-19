#ifndef EQUIP_H
#define EQUIP_H

#include "CEvent.h"
#include "CItem.h"
#include "CWeapon.fwd.h"
#include "CConsumable.h"

class CEquip : public CEvent
{
    public:
        CEquip(CPlayer* source, CItem* item) : CEvent(source, nullptr)
        {
            m_item = item;
        }
        ~CEquip()
        {}
        void print() const override;
        void updateObjects() override;

        bool visist(CWeapon* weapon);
        bool visit(CConsumable* consumable);

    private:
        CItem* m_item;
        bool m_success;
};

#endif