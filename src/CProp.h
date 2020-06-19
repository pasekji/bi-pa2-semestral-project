#ifndef PROP_H
#define PROP_H

#include "CGameObject.h"
#include <fstream>
#include "enums.h"

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
        
        void showStats() const override
        {
            return;
        }

        void getLable(std::string & lable) const override
        {
            return;
        } 

        virtual string getTypeName()
        {
            return "CProp";
        }

        void save(ofstream& os) override
        {
            writeString(os, getTypeName());
            os << (int)m_type;
        }

        static CGameObject* loadGameObject(ifstream& is)
        {
            int _type;
            is >> _type;
            CProp* res = new CProp(nullptr, 0,0, (prop_type)_type); // TODO
            return res;
        }
    
    private:
        prop_type m_type;
};

#endif