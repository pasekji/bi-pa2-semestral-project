#ifndef NOTICE_H
#define NOTICE_H

#include "CEvent.h"
#include <string>

class CNotice : public CEvent
{
    public:
        CNotice(CGameObject* source, const std::string & notice) : CEvent(source, nullptr)
        {
            m_notice = notice;
        }
        ~CNotice()
        {}
        void print() const override;
        void updateObjects() override;
        
    private:
        const std::string m_notice;
};

#endif