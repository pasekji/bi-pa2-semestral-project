#include "CInventory.h"
#include "CItem.h"
#include "CSword.h"
#include "CWand.h"
#include "CDagger.h"
#include "CCoffee.h"
#include "CApple.h"
#include "CBeer.h"
#include "CTooth.h"
#include "CPickup.h"


CInventory::CInventory(unsigned size) : m_size(size)
{
    m_itemCount = 0;
    constructFill();
}

void CInventory::constructFill()
{
    CItem* item = nullptr;
    for(unsigned i = 0; i < m_size; i++)
        m_contents.push_back(item);

    return;
}

unsigned CInventory::getSize() const
{
    return m_size;
}

CItem* CInventory::getItemAt(unsigned i) const
{
    return m_contents[i]; 
}

void CInventory::eraseItemAt(unsigned i)
{
    m_contents[i] = emptyItem;
    std::sort(m_contents.begin(), m_contents.end(), std::greater<CItem*>());
    if(m_itemCount != 0)
        m_itemCount--;
}


bool CInventory::getItem(CPlayerPaladin* paladin, CPickup* pickup) 
{
    if(!(m_itemCount < m_size))
        return false;

    std::default_random_engine randomGenerator(rand());
    std::uniform_int_distribution<int> itemRoll(0, 4);

    int roll = itemRoll(randomGenerator);

    CItem* item = nullptr;

    switch(roll)
    {
        case 0:
            item = std::make_shared<CSword>();
            break;
        case 1:
            item = std::make_shared<CCoffee>();
            break;
        case 2:
            item = std::make_shared<CApple>();
            break;
        case 3:
            item = std::make_shared<CBeer>();
            break;
        case 4:
            item = std::make_shared<CTooth>();
            break;
        default:
            break;
    }

    if(item != nullptr)
    {
        m_contents[m_itemCount] = item;
        m_itemCount++;
        pickup->setItemLabel(item->getLabel());
    }

    return true;
}

bool CInventory::getItem(CPlayerMage* mage, CPickup* pickup) 
{
    if(!(m_itemCount < m_size))
        return false;

    std::default_random_engine randomGenerator(rand());
    std::uniform_int_distribution<int> itemRoll(0, 4);

    int roll = itemRoll(randomGenerator);

    CItem* item = nullptr;

    switch(roll)
    {
        case 0:
            item = std::make_shared<CWand>();
            break;
        case 1:
            item = std::make_shared<CCoffee>();
            break;
        case 2:
            item = std::make_shared<CApple>();
            break;
        case 3:
            item = std::make_shared<CBeer>();
            break;
        case 4:
            item = std::make_shared<CTooth>();
            break;
        default:
            break;
    }

    if(item != nullptr)
    {
        m_contents[m_itemCount] = item;
        m_itemCount++;
        pickup->setItemLabel(item->getLabel());
    }

    return true;
}

bool CInventory::getItem(CPlayerRogue* rogue, CPickup* pickup) 
{
    if(!(m_itemCount < m_size))
        return false;

    std::default_random_engine randomGenerator(rand());
    std::uniform_int_distribution<int> itemRoll(0, 4);

    int roll = itemRoll(randomGenerator);

    CItem* item = nullptr;

    switch(roll)
    {
        case 0:
            item = std::make_shared<CDagger>();
            break;
        case 1:
            item = std::make_shared<CCoffee>();
            break;
        case 2:
            item = std::make_shared<CApple>();
            break;
        case 3:
            item = std::make_shared<CBeer>();
            break;
        case 4:
            item = std::make_shared<CTooth>();
            break;
        default:
            break;
    }

    if(item != nullptr)
    {
        m_contents[m_itemCount] = item;
        m_itemCount++;
        pickup->setItemLabel(item->getLabel());
    }

    return true;
} 
