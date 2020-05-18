#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <cstdlib>
#include "CCharacter.h"


class CItem
{
    protected:
        item_type m_type;
        std::string m_name;
        std::string m_lable;
        std::size_t m_price;
        std::size_t m_useability;            // count of possible uses

        virtual bool itemApply() = 0;

        CItem(item_type type, const std::string & name, const std::string & lable, std::size_t price, std::size_t useability) : m_type(type), m_name(name), m_lable(lable), m_price(price), m_useability(useability)
        {}
        virtual ~CItem()
        {}

};

#endif