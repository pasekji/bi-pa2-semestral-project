#ifndef EVENT_H
#define EVENT_H

#include "CGameObject.h"

class CEvent
{
    public:
        virtual void print() const = 0;

    protected:
        CEvent(CGameObject* source, CGameObject* target) : m_source(source), m_target(target)
        {}
        virtual ~CEvent()
        {}
        virtual void updateObjects() = 0;
        void pushToDisplay() const;
        CGameObject* m_source;
        CGameObject* m_target;
};

#endif