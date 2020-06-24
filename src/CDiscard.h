#ifndef DISCARD_H
#define DISCARD_H

#include "CEvent.h"
#include "CItem.h"

class CDiscard : public CEvent
{
    public:
        CDiscard(std::shared_ptr<CGameObject> source, std::shared_ptr<CItem> item);
        virtual ~CDiscard() = default;
        void print() override;
        void updateObjects() override;

        std::shared_ptr<CDiscard> getPtr()
        {
            return m_sharedThis;
        }
        
    private:
        std::shared_ptr<CItem> m_item;
        std::shared_ptr<CDiscard> m_sharedThis;
        bool m_success = false;

};

#endif