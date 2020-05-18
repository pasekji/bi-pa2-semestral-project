#ifndef DEQUIP_H
#define DEQUIP_H

#include "CEvent.h"
#include "CItem.h"

class CDequip : public CEvent
{
    public:
        CDequip(CPlayer* source, CItem* item) : CEvent(source, nullptr, DEQUIP)
        {
            m_item = item;
        }
        ~CDequip()
        {}
        void print() const override;
        void updateObjects() override;

    private:
        CItem* m_item;
        bool m_success;
};

#endif