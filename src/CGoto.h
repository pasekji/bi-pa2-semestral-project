#ifndef GOTO_H
#define GOTO_H

#include "CEvent.h"
#include "CMap.h"
#include "CDoor.h"

class CGoto : public CEvent
{
    public:
        CGoto(CPlayer* source, CDoor* door) : CEvent(source, door, GOTO)
        {}
        ~CGoto()
        {}
        void print() const override;
        void updateObjects() override;

    private:
        CDoor* m_door;
        CMap* m_mapFrom;
        CMap* m_mapTo;
};

#endif