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

bool CProp::acceptSource(std::shared_ptr<CAttack> attack)
{
    return false;
}

bool CProp::acceptSource(std::shared_ptr<CEquip> equip)
{
    return false;
}

bool CProp::acceptTarget(std::shared_ptr<CAttack> attack)
{
    return false;
}

bool CProp::updateSource(std::shared_ptr<CAttack> attack)
{
    return false;
}

bool CProp::updateTarget(std::shared_ptr<CAttack> attack)
{
    return false;
}

bool CProp::acceptSource(std::shared_ptr<CPickup> pickup)
{
    return false;
}

bool CProp::acceptTarget(std::shared_ptr<CPickup> pickup)
{
    return false;
}

bool CProp::updateSource(std::shared_ptr<CPickup> pickup)
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

std::shared_ptr<CGameObject> CProp::loadGameObject(ifstream& is)
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
