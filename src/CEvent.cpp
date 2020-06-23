#include "CEvent.h"
#include "CApplication.h"

extern CApplication application;

void CEvent::pushToDisplay()
{
    application.getGame()->pushEvent(this);
}

const std::string& CEvent::getPhrase() const
{
    return m_phrase;
}


