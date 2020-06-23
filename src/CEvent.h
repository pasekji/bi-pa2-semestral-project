#ifndef EVENT_H
#define EVENT_H

#include "CGameObject.h"

class CEvent
{
    public:
        const std::string& getPhrase() const;
        
    protected:
        CEvent(CGameObject* source, CGameObject* target) : m_source(source), m_target(target)
        {}
        virtual ~CEvent()
        {}
        virtual void updateObjects() = 0;
        virtual void print() = 0;
        void pushToDisplay();
        std::string m_phrase;
        CGameObject* m_source;
        CGameObject* m_target;
};

#endif