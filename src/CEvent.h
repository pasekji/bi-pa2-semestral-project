#ifndef EVENT_H
#define EVENT_H

#include "CGameObject.h"


class CEvent
{
    public:
        CEvent(CGameObject* source, CGameObject* target) : m_source(source), m_target(target)
        {}
        virtual ~CEvent();
        virtual void print() const;
        virtual void updateObjects();
        void pushToDisplay() const;
        CGameObject* m_source;
        CGameObject* m_target;
};

#endif