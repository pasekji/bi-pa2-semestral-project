#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <cstdlib>
#include "CItem.fwd.h"
#include "CPlayer.fwd.h"
#include "enums.h"
#include <memory>


class CItem
{
    public:
        virtual std::string getLabel() const = 0;

        CItem() = default;
        virtual ~CItem() = default;

        virtual bool itemApply(CPlayer* player) = 0;

        bool m_used = false;    
};

#endif