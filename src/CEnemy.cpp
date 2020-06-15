#include "CEnemy.h"
#include "CApplication.h"
#include "CAttack.h"


extern CApplication application;

CEnemy::CEnemy(WINDOW* objectSpace, int posY, int posX, enemy_type type) : CCharacter(objectSpace, posY, posX)
{
    switch (type)
    {
        case BASILISK:
            m_objectForm = '~';
            m_type = BASILISK;
            m_health = 40;
            m_currentHealth = m_health;
            m_energy = 30;
            m_currentEnergy = m_energy;
            m_force = 3;
            m_speed = 1;
            m_chanceOfBlock = 0.25;
            m_triggerDistance = 15;
            m_primaryAttackType = BITE;
            break;
        case UNDEAD:
            m_objectForm = 'F';
            m_type = UNDEAD;
            m_health = 30;
            m_currentHealth = m_health;
            m_energy = 20;
            m_currentEnergy = m_energy;
            m_force = 5;
            m_speed = 1;
            m_chanceOfBlock = 0.10;
            m_triggerDistance = 3;
            m_primaryAttackType = SCRATCH;
            break;
        case GHOUL:
            m_objectForm = 'G';
            m_type = GHOUL;
            m_health = 30;
            m_currentHealth = m_health;
            m_energy = 40;
            m_currentEnergy = m_energy;
            m_force = 6;
            m_speed = 1;
            m_chanceOfBlock = 0.15;
            m_triggerDistance = 4;
            m_primaryAttackType = TEAR;
            break;
        case HELLHOUND:
            m_objectForm = 'E';
            m_type = HELLHOUND;
            m_health = 50;
            m_currentHealth = m_health;
            m_energy = 25;
            m_currentEnergy = m_energy;
            m_force = 10;
            m_speed = 1;
            m_chanceOfBlock = 0.20;
            m_triggerDistance = 4;
            m_primaryAttackType = MELEE; 
            break;
        case NOONWRAITH:
            m_objectForm = 'Y';
            m_type = NOONWRAITH;
            m_health = 35;
            m_currentHealth = m_health;
            m_energy = 30;
            m_currentEnergy = m_energy;
            m_force = 7;
            m_speed = 2;
            m_chanceOfBlock = 0.35;
            m_triggerDistance = 5;
            m_primaryAttackType = SLAP;
            break;
        case SIREN:
            m_objectForm = '%';
            m_type = SIREN;
            m_health = 40;
            m_currentHealth = m_health;
            m_energy = 35;
            m_currentEnergy = m_energy;
            m_force = 4;
            m_speed = 3;
            m_chanceOfBlock = 0.30;
            m_triggerDistance = 7;
            m_primaryAttackType = KICK;
            break;
        default:
            break;
    }
}

const float CEnemy::getDistance(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos) const
{
    return sqrt(pow(playerPos.second - thisPos.second, 2) +  
                pow(playerPos.first - thisPos.first, 2) * 1.0);
}

void CEnemy::findPath(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos, direction & move) const
{
    static int followCount;
    const int retrieveBound = 5;

    if((sqrt(pow(playerPos.second - thisPos.second, 2)) - sqrt(pow(playerPos.first - thisPos.first, 2))) >= 0.0)
    {
        if(playerPos.second > thisPos.second)
        {
            if((abs(playerPos.second - thisPos.second) > 1) && (followCount < retrieveBound))
            {
                move = RIGHT;
                followCount++;
            }
            else
                followCount--;         
        }
        else
        {
            if((abs(playerPos.second - thisPos.second) > 1) && (followCount < retrieveBound))
            {
                move = LEFT;
                followCount++;
            }
            else
                followCount--;          
        }
    }
    else
    {
        if(playerPos.first > thisPos.first)
        {
            if((abs(playerPos.first - thisPos.first) > 1) && (followCount < retrieveBound))
            {
                move = DOWN;
                followCount++;
            }
            else
                followCount--;          
        }
        else
        {
            if((abs(playerPos.first - thisPos.first) > 1) && (followCount < retrieveBound))
            {
                move = UP;
                followCount++;
            }
            else
                followCount--;           
        }
    }
    
    return;
}

int CEnemy::getAction()     // just demo testing - TODO - AI 
{
    const direction way[6] = {STAY, STAY, UP, DOWN, LEFT, RIGHT}; 
    int index = rand() % 6;
    direction move = way[index];
    int tmppos, tmpstep;
    std::pair<int, int> thisPos;
    std::pair<int, int> playerPos;
    
    playerPos = application.getGame().getMap()->getPlayer()->getPos();
    thisPos = getPos();

    if(getDistance(pair, playerPos) <= (float)m_triggerDistance)
        findPath(pair, playerPos, move);

    switch (move) 
    {
        case STAY:
            break;
        case UP:
            tmpstep = 1;

            while((!application.getGame().getMap()->collisionDetect(thisPos = std::make_pair(tmppos = m_posY - tmpstep, m_posX))) && (tmpstep <=  m_speed))
                tmpstep++;

            tmpstep--;
            moveUp(tmpstep);
            break;
        case DOWN:
            tmpstep = 1;

            while((!application.getGame().getMap()->collisionDetect(thisPos = std::make_pair(tmppos = m_posY + tmpstep, m_posX))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveDown(tmpstep);
            break;
        case LEFT:
            tmpstep = 1;

            while((!application.getGame().getMap()->collisionDetect(thisPos = std::make_pair(m_posY, tmppos = m_posX - tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveLeft(tmpstep);
            break;
        case RIGHT:
            tmpstep = 1;

            while((!application.getGame().getMap()->collisionDetect(thisPos = std::make_pair(m_posY, tmppos = m_posX + tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            tmpstep--;
            moveRight(tmpstep);
        default:
            break;
    }

    return index;
}

bool CEnemy::interactWith()
{
    //TODO
    return false;
}

bool CEnemy::accept(CAttack* attack)
{
    attack->visit(this);
    return true;
}

void CEnemy::showStats() const
{
    int height, width;
    getmaxyx(application.getGame().getObjectWindow(), height, width);

    switch (m_type)
    {
        case BASILISK:
            mvwprintw(application.getGame().getObjectWindow(), (height - 10) / 2, (width - strlen("BASILISK")) / 2, "BASILISK");
            break;
        case UNDEAD:
            mvwprintw(application.getGame().getObjectWindow(), (height - 10) / 2, (width - strlen("UNDEAD")) / 2, "UNDEAD");
            break;
        case GHOUL:
            mvwprintw(application.getGame().getObjectWindow(), (height - 10) / 2, (width - strlen("GHOUL")) / 2, "GHOUL");
            break;
        case HELLHOUND:
            mvwprintw(application.getGame().getObjectWindow(), (height - 10) / 2, (width - strlen("HELLHOUND")) / 2, "HELLHOUND");
            break;
        case NOONWRAITH:
            mvwprintw(application.getGame().getObjectWindow(), (height - 10) / 2, (width - strlen("NOONWRAITH")) / 2, "NOONWRAITH");
            break;
        case SIREN:
            mvwprintw(application.getGame().getObjectWindow(), (height - 10) / 2, (width - strlen("SIREN")) / 2, "SIREN");
            break;
        default:
            break;
    }

    mvwprintw(application.getGame().getObjectWindow(), (height - 6) / 2, (width - 18) / 2, "Health:     %d/%d", m_currentHealth, m_health);
    mvwprintw(application.getGame().getObjectWindow(), (height - 2) / 2, (width - 18) / 2, "Energy:     %d/%d", m_currentEnergy, m_energy);
    mvwprintw(application.getGame().getObjectWindow(), (height + 2) / 2, (width - 15) / 2, "Force:      %d", m_force);

    wrefresh(application.getGame().getObjectWindow());


    return;
} 