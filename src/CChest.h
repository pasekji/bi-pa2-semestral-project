#ifndef CHEST_H
#define CHEST_H

#include "CGameObject.h"
#include "CItem.h"
#include <map>
#include <vector>

class CChest : public CGameObject
{
    public:
        CChest(WINDOW* objectSpace, int posY, int posX, std::size_t size) : CGameObject(objectSpace, posY, posX)
        {
            m_objectForm = 'H';
            m_size = size;
            for (std::size_t i = 0; i < m_size; ++i)
            {
                m_keys.push_back(i);
                m_contents[i];
            }

            m_it = m_keys.begin();
        }
        std::vector<std::size_t>::iterator m_it;
        bool is_empty();
        bool is_full();
        void loadContents();
        void popItem();
        void pushItem(CItem * item);

        bool interactWith() override
        {
            return false;
        }

    private:
        std::size_t m_size;
        std::vector<std::size_t> m_keys;
        std::map<std::size_t, CItem*> m_contents;
};

#endif