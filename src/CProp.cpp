#include "CProp.h"

CProp::CProp(int posY, int posX, prop_type type) : CGameObject(posY, posX)
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

bool CProp::acceptSource(CAttack* attack)
{
    return false;
}

bool CProp::acceptSource(CEquip* equip)
{
    return false;
}

bool CProp::acceptTarget(CAttack* attack)
{
    return false;
}

bool CProp::updateSource(CAttack* attack)
{
    return false;
}

bool CProp::updateTarget(CAttack* attack)
{
    return false;
}

bool CProp::acceptSource(CPickup* pickup)
{
    return false;
}

bool CProp::acceptTarget(CPickup* pickup)
{
    return false;
}

bool CProp::updateSource(CPickup* pickup)
{
    return false;
}

void CProp::showStats() const
{
    return;
}

void CProp::getLabel(std::string & label) const
{
    return;
} 

string CProp::getTypeName()
{
    return "CProp";
}

void CProp::save(ofstream& os)
{
    os << getTypeName() << " ";
    os << (int)m_type << " ";
    os << m_posX << " ";
    os << m_posY << endl;
}

CGameObject* CProp::loadGameObject(ifstream& is)
{
    int _type;
    is >> _type;
    int posX;
    int posY;
    is >> posX;
    is >> posY;

    CProp* result;
    result = new CProp(posY, posX, (prop_type)_type);
    return result;
}
