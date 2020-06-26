#ifndef EVENT_H
#define EVENT_H

#include "CGameObject.h"
#include <memory>

class CEvent
{
    public:
        const std::string& getPhrase() const;
        virtual ~CEvent() = default;
        
    protected:
        CEvent(CGameObject* source, CGameObject* target) : m_source(source), m_target(target)
        {}
        virtual void updateObjects() = 0;
        virtual void print() = 0;
        std::string m_phrase;
        std::string m_sourceLabel;
        std::string m_targetLabel;
        std::string m_itemLabel;
        CGameObject* m_source;
        CGameObject* m_target;
};

#endif