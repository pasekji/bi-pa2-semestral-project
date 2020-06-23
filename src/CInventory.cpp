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
            item = new CSword();
            break;
        case 1:
            item = new CCoffee();
            break;
        case 2:
            item = new CApple();
            break;
        case 3:
            item = new CBeer();
            break;
        case 4:
            item = new CTooth();
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
            item = new CWand();
            break;
        case 1:
            item = new CCoffee();
            break;
        case 2:
            item = new CApple();
            break;
        case 3:
            item = new CBeer();
            break;
        case 4:
            item = new CTooth();
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
            item = new CDagger();
            break;
        case 1:
            item = new CCoffee();
            break;
        case 2:
            item = new CApple();
            break;
        case 3:
            item = new CBeer();
            break;
        case 4:
            item = new CTooth();
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
