#include "CPrimaryAttack.h"
#include "CApplication.h"

extern CApplication application;

CPrimaryAttack::CPrimaryAttack(CGameObject* source, CGameObject* target, attack_type attackType) : CAttack(source, target, attackType)
{
    source->accept(this);
    target->accept(this);
}

CPrimaryAttack::~CPrimaryAttack()
{

}

void CPrimaryAttack::print() const
{
    return;
}

void CPrimaryAttack::evaluateAttack()
{
    return;
}

void CPrimaryAttack::updateObjects()
{
    return;
}