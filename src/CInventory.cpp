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
    std::shared_ptr<CItem> item = nullptr;
    for(unsigned i = 0; i < m_size; i++)
        m_contents.push_back(item);

    return;
}

bool CInventory::getItem(std::shared_ptr<CPlayerPaladin> paladin, std::shared_ptr<CPickup> pickup) 
{
    if(!(m_itemCount < m_size))
        return false;

    std::default_random_engine randomGenerator(rand());
    std::uniform_int_distribution<int> itemRoll(0, 4);

    int roll = itemRoll(randomGenerator);

    std::shared_ptr<CItem> item = nullptr;

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

bool CInventory::getItem(std::shared_ptr<CPlayerMage> mage, std::shared_ptr<CPickup> pickup) 
{
    if(!(m_itemCount < m_size))
        return false;

    std::default_random_engine randomGenerator(rand());
    std::uniform_int_distribution<int> itemRoll(0, 4);

    int roll = itemRoll(randomGenerator);

    std::shared_ptr<CItem> item = nullptr;

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

bool CInventory::getItem(std::shared_ptr<CPlayerRogue> rogue, std::shared_ptr<CPickup> pickup) 
{
    if(!(m_itemCount < m_size))
        return false;

    std::default_random_engine randomGenerator(rand());
    std::uniform_int_distribution<int> itemRoll(0, 4);

    int roll = itemRoll(randomGenerator);

    std::shared_ptr<CItem> item = nullptr;

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
