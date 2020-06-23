#include "CCharacter.h"
#include "CApplication.h"

extern CApplication application;

CGameObject* CCharacter::defaultGetTarget()
{
    int tmppos;
    CGameObject* target = nullptr;
    std::pair<int, int> pair;

    target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(tmppos = m_posY - 1, m_posX));

    if(target == nullptr)
        target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(tmppos = m_posY + 1, m_posX));        

    if(target == nullptr)
        target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(m_posY, tmppos = m_posX - 1));

    if(target == nullptr)
        target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(m_posY, tmppos = m_posX + 1));

    return target;
}
