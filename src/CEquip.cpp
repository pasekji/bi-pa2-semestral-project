#include "CEquip.h"
#include "CPlayer.h"

CEquip::CEquip(std::shared_ptr<CGameObject> source, std::shared_ptr<CItem> item) : CEvent(source, nullptr)
{
    m_sharedThis.reset(this);
    m_item = item;
    if(m_item == nullptr)
        print();
    else
    {
        m_isSomething = true;
        m_itemLabel = m_item->getLabel();
        if(!(m_source->acceptSource(m_sharedThis)))
            print();
    }
}

std::shared_ptr<CEquip> CEquip::getPtr()
{
    return m_sharedThis;
}

void CEquip::print()
{
    if(m_isSomething)
    {
        if(m_success)
            m_phrase = m_sourceLabel + " used " + m_itemLabel + ".";
        else
            m_phrase = m_sourceLabel + " can't use " + m_itemLabel + "!";
    }
    else
        m_phrase = "There is nothing!";
    
    return;
}

void CEquip::visitSource(std::shared_ptr<CPlayer> player)
{
    player->getLabel(m_sourceLabel);
    evaluateEquip(player);
    return;
}

void CEquip::evaluateEquip(std::shared_ptr<CPlayer> player)
{
    if(m_isSomething)
    {
        if(m_item->itemApply(player))
            m_success = true;
    }

    updateObjects();
    return;
}

void CEquip::updateObjects()
{
    print();
    return;
}