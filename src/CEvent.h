#ifndef EVENT_H
#define EVENT_H

#include "CGameObject.h"


class CEvent
{
    public:
        CEvent(CGameObject* source, CGameObject* target, event_type type) : m_source(source), m_target(target), m_type(type)
        {}
        virtual ~CEvent();
        virtual void print() const;
        virtual void updateObjects();
        void pushToDisplay() const;
        CGameObject* m_source;
        CGameObject* m_target;
        event_type m_type;
};

#endif