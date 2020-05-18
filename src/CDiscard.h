#ifndef DISCARD_H
#define DISCARD_H

#include "CEvent.h"
#include "CItem.h"

class CDiscard : public CEvent
{
    public:
        CDiscard(CPlayer* source, CGameObject* target, CItem* item) : CEvent(source, target, ITEM_DISCARD)
        {
            m_item = item;
        }
        CDiscard(CPlayer* source, CItem* item) : CEvent(source, nullptr, ITEM_DISCARD)
        {
            m_item = item;
        }
        ~CDiscard()
        {}
        void print() const override;
        void updateObjects() override;
        
    private:
        CItem* m_item;
        bool m_success;

};

#endif