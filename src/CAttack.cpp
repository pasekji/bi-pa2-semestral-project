#include "CAttack.h"
#include "CApplication.h"
#include <ncurses.h>

extern CApplication application;

void CAttack::visit(CPlayerPaladin* paladin)
{
    mvwprintw(application.getGame().getPlayerWindow(), 9, 1, "paladin visited");
    return;
}

void CAttack::visit(CPlayerMage* mage)
{
    mvwprintw(application.getGame().getPlayerWindow(), 9, 1, "mage visited");
    return;
}

void CAttack::visit(CPlayerRogue* rogue)
{
    mvwprintw(application.getGame().getPlayerWindow(), 9, 1, "rogue visited");
    return;
}

void CAttack::visit(CEnemy* enemy)
{
    mvwprintw(application.getGame().getPlayerWindow(), 10, 1, "enemy visited");
    return;
}