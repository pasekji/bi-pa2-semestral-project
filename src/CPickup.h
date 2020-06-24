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
        CPickup(std::shared_ptr<CGameObject> source, std::shared_ptr<CGameObject> target);
        virtual ~CPickup() = default;

        void visitSource(std::shared_ptr<CPlayerPaladin> paladin);
        void visitSource(std::shared_ptr<CPlayerMage> mage);
        void visitSource(std::shared_ptr<CPlayerRogue> rogue);
        void visitTarget(std::shared_ptr<CLoot> loot);

        void updateSource(std::shared_ptr<CPlayerPaladin> paladin);
        void updateSource(std::shared_ptr<CPlayerRogue> rogue);
        void updateSource(std::shared_ptr<CPlayerMage> mage);


        void setItemLabel(std::string label)
        {
            m_itemLabel = label;
        }

        std::shared_ptr<CPickup> getPtr()
        {
            return m_sharedThis;
        }
    
    private:

        std::shared_ptr<CPickup> m_sharedThis;
        void print() override;
        void updateObjects() override;
        bool m_success = false;
        bool m_canPick = false;
        bool m_accessTarget = false;

};

#endif