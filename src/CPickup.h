#ifndef PICKUP_H
#define PICKUP_H

#include "CEvent.h"
#include "CPickup.fwd.h"
#include "CPlayerPaladin.fwd.h"
#include "CPlayerMage.fwd.h"
#include "CPlayerRogue.fwd.h"
#include "CLoot.fwd.h"
#include <string>

class CPickup : public CEvent
{
    public:
        CPickup(CGameObject* source, CGameObject* target);
        virtual ~CPickup() = default;

        void visitSource(CPlayerPaladin* paladin);
        void visitSource(CPlayerMage* mage);
        void visitSource(CPlayerRogue* rogue);
        void visitTarget(CLoot* loot);

        void updateSource(CPlayerPaladin* paladin);
        void updateSource(CPlayerRogue* rogue);
        void updateSource(CPlayerMage* mage);


        void setItemLabel(std::string label);

        CPickup* getPtr();
    
    private:

        CPickup* m_sharedThis;
        void print() override;
        void updateObjects() override;
        bool m_success = false;
        bool m_canPick = false;
        bool m_accessTarget = false;

};

#endif