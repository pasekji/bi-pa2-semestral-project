#ifndef TALK_H
#define TALK_H

#include "CEvent.h"
#include <string>

class CTalk : public CEvent
{
    public:
        CTalk(CGameObject* source, CGameObject* target) : CEvent(source, target, TALK)
        {}
        ~CTalk()
        {}
        void print() const override;
        void updateObjects() override;

    private:
        std::string m_greeting;
        std::string m_answer;

};

#endif