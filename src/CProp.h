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

        bool acceptSource(CAttack* attack) override;
        bool acceptSource(CEquip* equip) override;
        bool acceptTarget(CAttack* attack) override;
        bool updateSource(CAttack* attack) override;
        bool updateTarget(CAttack* attack) override;
        bool acceptSource(CPickup* pickup) override;
        bool acceptTarget(CPickup* pickup) override;
        bool updateSource(CPickup* pickup) override;
        
        void showStats() const override;
        void getLabel(std::string & label) const override;
        virtual string getTypeName();
        void save(ofstream& os) override;
        static CGameObject* loadGameObject(ifstream& is);
    
    private:
        prop_type m_type;
};

#endif