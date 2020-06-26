#include "CDagger.h"
#include "CPlayer.h"

CDagger::CDagger()
{
    m_sharedThis.reset(this);
    m_compatible = ROGUE;
    m_damage = 8;
    m_chance_of_block = 0.25f;
}

std::string CDagger::getLabel() const
{
    return "DAGGER";
}

bool CDagger::itemApply(CPlayer* player)
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