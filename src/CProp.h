#ifndef PROP_H
#define PROP_H

#include "CGameObject.h"

class CProp : public CGameObject
{
    public:
        CProp(WINDOW* objectSpace, int posY, int posX, const char & objectForm) : CGameObject(objectSpace, posY, posX, objectForm)
        {}
        ~CProp()
        {}

};

#endif