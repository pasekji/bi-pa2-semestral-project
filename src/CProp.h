#ifndef PROP_H
#define PROP_H

#include "CGameObject.h"

class CProp : public CGameObject
{
    public:
        CProp(WINDOW* objectSpace, int posY, int posX, char & objectForm) : CGameObject(objectSpace, posY, posX)
        {
            m_objectForm = objectForm;
        }
        ~CProp()
        {}

};

#endif