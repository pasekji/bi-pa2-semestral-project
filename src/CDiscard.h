#ifndef DISCARD_H
#define DISCARD_H

#include "CEvent.h"
#include "CItem.h"

class CDiscard : public CEvent
{
    public:
        CDiscard(CGameObject* source, CItem* item);
        virtual ~CDiscard() = default;
        void print() override;
        void updateObjects() override;

        CDiscard* getPtr();
        
    private:
        CItem* m_item;
        bool m_success = false;

};

#endif