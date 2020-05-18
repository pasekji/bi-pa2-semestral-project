#ifndef PICKUP_H
#define PICKUP_H

#include "CEvent.h"
#include "CItem.h"

class CPickup : public CEvent
{
    public:
        CPickup(CPlayer* source, CGameObject* target) : CEvent(source, target, ITEM_PICKUP)
        {}
        ~CPickup()
        {}
        void print() const override;
        void updateObjects() override;
    
    private:
        CItem* m_item;
        bool m_success;

};

#endif