#ifndef ARMOR_H
#define ARMOR_H

#include "CItem.h"

class CArmor : public CItem
{
    public:
        CArmor(const std::string & name, const std::string & lable, std::size_t price, std::size_t useability, int armor, int chance_of_block, body_part body) : CItem(name, lable, price, useability)
        {
            m_armor = armor;
            m_chance_of_block = chance_of_block;
            m_body = body;
        }
        ~CArmor()
        {}
        bool itemApply();

        bool is_equiped;

    private:
        body_part m_body;
        int m_armor;
        float m_chance_of_block;
};

#endif