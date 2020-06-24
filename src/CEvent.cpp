#include "CEvent.h"
#include "CApplication.h"

extern CApplication application;

const std::string& CEvent::getPhrase() const
{
    return m_phrase;
}


