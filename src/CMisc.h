#ifndef MISC_H
#define MISC_H

#include "CItem.h"

class CMisc : public CItem          // could be stackable
{
    public:
        CMisc(const std::string & name, const std::string & lable, const std::string & id, std::size_t price) : CItem(MISC, name, lable, price, 0)
        {
            m_id = id;
        }
        ~CMisc()
        {}
        bool itemApply()            // these items can't be applied f.e. - bone 
        {
            return false;
        }
        std::string m_id;

};

#endif