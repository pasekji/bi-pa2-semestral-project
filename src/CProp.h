#ifndef PROP_H
#define PROP_H

#include "CGameObject.h"
#include <fstream>
#include "enums.h"
#include "CAttack.fwd.h"

class CProp : public CGameObject
{
    public:
        CProp(int posY, int posX, prop_type type) : CGameObject(posY, posX)
        {
            switch (type)
            {
                case WALL:
                    m_objectForm = '#';
                    m_type = type;
                    break;
                case TREE:
                    m_objectForm = 'T';
                    m_type = type;
                    break;
                case STONE:
                    m_objectForm = '.';
                    m_type = type;
                    break;
                case BUSH:
                    m_objectForm = '@';
                    m_type = type;
                    break;
                case VOID:
                    m_objectForm = '+';
                    m_type = type;
                    break;
                default:
                    break;
            }
        }

        virtual ~CProp() = default;


        bool acceptSource(std::shared_ptr<CAttack> attack) override
        {
            return false;
        }

        bool acceptSource(std::shared_ptr<CEquip> equip) override
        {
            return false;
        }

        bool acceptTarget(std::shared_ptr<CAttack> attack) override
        {
            return false;
        }

        bool updateSource(std::shared_ptr<CAttack> attack) override
        {
            return false;
        }

        bool updateTarget(std::shared_ptr<CAttack> attack) override
        {
            return false;
        }

        bool acceptSource(std::shared_ptr<CPickup> pickup) override
        {
            return false;
        }
        bool acceptTarget(std::shared_ptr<CPickup> pickup) override
        {
            return false;
        }
        bool updateSource(std::shared_ptr<CPickup> pickup) override
        {
            return false;
        }
        
        void showStats() const override
        {
            return;
        }

        void getLabel(std::string & label) const override
        {
            return;
        } 

        virtual string getTypeName()
        {
            return "CProp";
        }

        void save(ofstream& os) override
        {
            os << getTypeName() << endl;
            os << (int)m_type;
            os << m_posX;
            os << m_posY;
        }

        static std::shared_ptr<CGameObject> loadGameObject(ifstream& is)
        {
            int _type;
            is >> _type;
            int posX;
            int posY;
            is >> posX;
            is >> posY;

            std::shared_ptr<CProp> result;
            result.reset(new CProp(posY, posX, (prop_type)_type));
            return result;
        }
    
    private:
        prop_type m_type;
};

#endif