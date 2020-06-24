#include "CSword.h"
#include "CPlayer.h"

CSword::CSword()
{
    m_sharedThis.reset(this);
    m_compatible = PALADIN;
    m_damage = 10;
    m_chance_of_block = 0.2f;
}

std::string CSword::getLabel() const
{
    return "SWORD";
}

bool CSword::itemApply(std::shared_ptr<CPlayer> player)
{
    if(player->m_weaponEquiped == nullptr)
    {
        player->m_weaponEquiped = m_sharedThis;
        player->addForce(m_damage);
        player->m_chanceOfBlock += m_chance_of_block;
        m_used = true;
        return true;
    }
    else
        return false;  
}