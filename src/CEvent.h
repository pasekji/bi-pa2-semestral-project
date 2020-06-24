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
        CEvent(std::shared_ptr<CGameObject> source, std::shared_ptr<CGameObject> target) : m_source(source), m_target(target)
        {}
        virtual void updateObjects() = 0;
        virtual void print() = 0;
        std::string m_phrase;
        std::string m_sourceLabel;
        std::string m_targetLabel;
        std::string m_itemLabel;
        std::shared_ptr<CGameObject> m_source;
        std::shared_ptr<CGameObject> m_target;
};

#endif