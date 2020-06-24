#include "CPickup.h"
#include "CLoot.h"
#include "CPlayer.h"
#include "CPlayerPaladin.h"
#include "CPlayerMage.h"
#include "CPlayerRogue.h"

CPickup::CPickup(std::shared_ptr<CGameObject> source, std::shared_ptr<CGameObject> target) : CEvent(source, target)
{
    m_sharedThis.reset(this);
    source->acceptSource(m_sharedThis);
    if(!(target->acceptTarget(m_sharedThis)))
        m_accessTarget = false;
    else
        m_accessTarget = true;

    updateObjects();
}

void CPickup::visitTarget(std::shared_ptr<CLoot> loot)
{
    loot->getLabel(m_targetLabel);
    if(loot->pick())
        m_canPick = true;           // to znamena ze mohu zkusit vygenerovat item 
    return;
}

void CPickup::visitSource(std::shared_ptr<CPlayerPaladin> paladin)
{
    paladin->getLabel(m_sourceLabel);
    return;
}

void CPickup::visitSource(std::shared_ptr<CPlayerRogue> rogue)
{
    rogue->getLabel(m_sourceLabel);
    return;
}

void CPickup::visitSource(std::shared_ptr<CPlayerMage> mage)
{
    mage->getLabel(m_sourceLabel);
    return;
}

void CPickup::updateSource(std::shared_ptr<CPlayerPaladin> paladin)
{
    if(paladin->m_inventory->getItem(paladin, m_sharedThis))
        m_success = true;
    else
        m_success = false;    
    return;
}

void CPickup::updateSource(std::shared_ptr<CPlayerRogue> rogue)
{
    if(rogue->m_inventory->getItem(rogue, m_sharedThis))
        m_success = true;
    else
        m_success = false;    
    return;
}

void CPickup::updateSource(std::shared_ptr<CPlayerMage> mage)
{
    if(mage->m_inventory->getItem(mage, m_sharedThis))
        m_success = true;
    else
        m_success = false;    
    return;
}

void CPickup::updateObjects()
{
    if(m_accessTarget && m_canPick)
        m_source->updateSource(m_sharedThis);

    print();
    
    return;
}

void CPickup::print()
{
    if(!m_accessTarget)
    {
        m_phrase = "Nothing to pick up from!";
        return;
    }
    if(!m_canPick)
    {
        m_phrase = "No items found in " + m_targetLabel + "!";
        return;
    }
    if(!m_success)
    {
        m_phrase = "No space in inventory!";
        return;
    }

    m_phrase = m_sourceLabel + " picked up " + m_itemLabel + " from the " + m_targetLabel + ".";
    return;
}