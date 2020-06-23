#ifndef PROP_H
#define PROP_H

#include "CGameObject.h"
#include <fstream>
#include "enums.h"
#include "CAttack.fwd.h"

class CProp : public CGameObject
{
    public:
        CProp(WINDOW* objectSpace, int posY, int posX, prop_type type) : CGameObject(objectSpace, posY, posX)
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
        
        virtual ~CProp()
        {}

        bool acceptSource(CAttack* attack) override
        {
            return false;
        }

        bool acceptTarget(CAttack* attack) override
        {
            return false;
        }

        bool updateSource(CAttack* attack) override
        {
            return false;
        }

        bool updateTarget(CAttack* attack) override
        {
            return false;
        }

        bool acceptSource(CPickup* pickup) override
        {
            return false;
        }
        bool acceptTarget(CPickup* pickup) override
        {
            return false;
        }
        bool updateSource(CPickup* pickup) override
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

        static CGameObject* loadGameObject(ifstream& is, WINDOW* objectSpace)
        {
            int _type;
            is >> _type;
            int posX;
            int posY;
            is >> posX;
            is >> posY;
            CProp* res = new CProp(objectSpace, posY, posX, (prop_type)_type);
            return res;
        }
    
    private:
        prop_type m_type;
};

#endif