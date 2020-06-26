#ifndef PROP_H
#define PROP_H

#include "CGameObject.h"
#include <fstream>
#include "enums.h"
#include "CAttack.fwd.h"

class CProp : public CGameObject
{
    public:
        CProp(int posY, int posX, prop_type type);

        virtual ~CProp() = default;

        bool acceptSource(std::shared_ptr<CAttack> attack) override;
        bool acceptSource(std::shared_ptr<CEquip> equip) override;
        bool acceptTarget(std::shared_ptr<CAttack> attack) override;
        bool updateSource(std::shared_ptr<CAttack> attack) override;
        bool updateTarget(std::shared_ptr<CAttack> attack) override;
        bool acceptSource(std::shared_ptr<CPickup> pickup) override;
        bool acceptTarget(std::shared_ptr<CPickup> pickup) override;
        bool updateSource(std::shared_ptr<CPickup> pickup) override;
        
        void showStats() const override;
        void getLabel(std::string & label) const override;
        virtual string getTypeName();
        void save(ofstream& os) override;
        static std::shared_ptr<CGameObject> loadGameObject(ifstream& is);
    
    private:
        prop_type m_type;
};

#endif