#ifndef INVENTORY_H
#define INVENTORY_H

#include "CItem.h"
#include <vector>
#include <map>
#include <stack>

class CInventory            // map of stacks
{
    public:
        CInventory(std::size_t size) : m_size(size)
        {
            for (std::size_t i = 0; i < m_size; ++i)
            {
                m_keys.push_back(i);
                m_contents[i];
            }

            m_it = m_keys.begin();
        }

        void incrementItr();
        void decrementItr();
        void useItem();
        void dumpItem();
        void pickUpItem();
        void loadItemsAfterSave();
        void saveItems();
        void getSize();

    private:
        std::size_t m_size;
        std::vector<std::size_t> m_keys;
        std::vector<std::size_t>::iterator m_it;
        std::map<size_t, std::pair<std::string, std::stack<CItem*>>> m_contents;

};

#endif