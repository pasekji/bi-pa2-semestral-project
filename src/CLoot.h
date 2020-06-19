#ifndef LOOT_H
#define LOOT_H

#include "CGameObject.h"
#include "CItem.h"
#include <map>
#include <vector>

class CLoot : public CGameObject
{
    public:
        CLoot(WINDOW* objectSpace, int posY, int posX, std::size_t size) : CGameObject(objectSpace, posY, posX)
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

        ~CLoot()
        {}

        std::vector<std::size_t>::iterator m_it;
        bool is_empty();
        void loadContents();
        void popItem();

        bool acceptSource(CAttack* attack) override
        {
            return false;
        }

        virtual string getTypeName()
        {
            return "CLoot";
        }

        void save(ofstream& os) override
        {
            os << getTypeName() << endl;
        }

        bool acceptTarget(CAttack* attack) override
        {
            return false;
        }

        void getLable(std::string & lable) const override
        {
            return;
        } 

        void showStats() const override
        {
            return;
        }


    private:
        std::size_t m_size;
        std::vector<std::size_t> m_keys;
        std::map<std::size_t, CItem*> m_contents;
};

#endif