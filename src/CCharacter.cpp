#include "CCharacter.h"
#include "CApplication.h"

extern CApplication application;

std::shared_ptr<CGameObject> CCharacter::defaultGetTarget()
{
    int tmppos;
    std::shared_ptr<CGameObject> target = nullptr;
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

std::shared_ptr<CCharacter> loadCharacter(ifstream& is)
{
    string type;
    is >> type;
    if (type == "CPlayerPaladin")
        return loadPlayerPaladin(is);
    if (type == "CPlayerRogue")
        return loadPlayerRogue(is);
    if (type == "CPlayerMage")
        return loadPlayerMage(is);
    if (type == "CEnemy")
        return loadEnemy(is);
    std::shared_ptr<CCharacter> result;
    return result;
    // TODO
}