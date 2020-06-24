#include "CPlayer.h"
#include "CApplication.h"
#include "CPickup.h"
#include "CAttack.h"
#include "CItem.h"
#include "CEquip.h"
#include "CDiscard.h"

extern CApplication application;


CPlayer::CPlayer(int posY, int posX) : CCharacter(posY, posX)
{
    m_sharedThis.reset(this);
    m_posY_real = posY;
    m_posX_real = posX;
    m_objectForm = '^';
    m_speed = 1;
    m_sprint = false;
    keypad(application.getGame()->getWindow(), true);
}
void CPlayer::changeForm(const char & objectForm)
{
    m_objectForm = objectForm;
}

void CPlayer::defaultStep(int & move)       // basic player movement, every class has it..
{
    int tmpmove;
    int delay = 0;
    if((move = wgetch(application.getGame()->getWindow())) != ERR)
    {
        do
        {
            if(delay == 3)
                break;
                
            tmpmove = wgetch(application.getGame()->getWindow());
            delay++;
        } 
        while((tmpmove == move) || (tmpmove != ERR));
    }

}

std::shared_ptr<CGameObject> CPlayer::directionGetTarget()
{
    int tmppos;    
    std::pair<int, int> pair;
    std::shared_ptr<CGameObject> target = nullptr;

    switch (m_objectForm)
    {
        case '^':
            target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(tmppos = m_posY - 1, m_posX));
            break;
    
        case 'v':
            target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(tmppos = m_posY + 1, m_posX));        
            break;

        case '<':
            target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(m_posY, tmppos = m_posX - 1));
            break;

        case '>':
            target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(m_posY, tmppos = m_posX + 1));
            break;

        default:
            break;
    }

    return target;
} 


bool CPlayer::defaultMove(int move)
{
    // if default speed and delay move up, down etc...

    int tmppos, tmpstep;
    direction tmpdir;
    std::pair<int, int> pair;
    bool used = false;

    switch (move) 
    {
        case 'w':
        case 'W':
        case KEY_UP:
            tmpstep = 1;

            while((!application.getGame()->getMap()->collisionDetect(pair = std::make_pair(tmppos = m_posY - tmpstep, m_posX))) && (tmpstep <=  m_speed))
                tmpstep++;

            if(!spareEnergyToStep())
                break;

            tmpstep--;

            takeStep();
            moveUp(tmpstep);
            m_posY_real -= tmpstep;
            application.getGame()->getMap()->staticCamera(tmpdir = UP, tmpstep);
            changeForm('^');
            used = true;
            break;

        case 's':
        case 'S':
        case KEY_DOWN:
            tmpstep = 1;

            while((!application.getGame()->getMap()->collisionDetect(pair = std::make_pair(tmppos = m_posY + tmpstep, m_posX))) && (tmpstep <= m_speed))
                tmpstep++;

            if(!spareEnergyToStep())
                break;

            tmpstep--;

            takeStep();
            moveDown(tmpstep);
            m_posY_real += tmpstep;
            application.getGame()->getMap()->staticCamera(tmpdir = DOWN, tmpstep);
            changeForm('v');
            used = true;
            break;

        case 'a':
        case 'A':
        case KEY_LEFT:
            tmpstep = 1;

            while((!application.getGame()->getMap()->collisionDetect(pair = std::make_pair(m_posY, tmppos = m_posX - tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            if(!spareEnergyToStep())
                break;

            tmpstep--;

            takeStep();
            moveLeft(tmpstep);
            m_posX_real -= tmpstep;
            application.getGame()->getMap()->staticCamera(tmpdir = LEFT, tmpstep);
            changeForm('<');
            used = true;
            break;
        
        case 'd':
        case 'D':
        case KEY_RIGHT:
            tmpstep = 1;

            while((!application.getGame()->getMap()->collisionDetect(pair = std::make_pair(m_posY, tmppos = m_posX + tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            if(!spareEnergyToStep())
                break;

            tmpstep--;

            takeStep();
            moveRight(tmpstep);
            m_posX_real += tmpstep;
            application.getGame()->getMap()->staticCamera(tmpdir = RIGHT, tmpstep);
            changeForm('>');
            used = true;
            break;

        case 'i':
        case 'I':
            goToInventory();
            used = true;
            break;

        default:
            break;
    }

    return used;
}

bool CPlayer::itemPickup(std::shared_ptr<CGameObject> target)
{
    std::shared_ptr<CEvent> pickup;
    pickup = (new CPickup(m_sharedThis, target))->getPtr();
    application.getGame()->pushEvent(pickup);
    return true;
}

bool CPlayer::acceptSource(std::shared_ptr<CAttack> attack)
{
    attack->visitSource(m_sharedThis);
    return true;
}   

bool CPlayer::acceptTarget(std::shared_ptr<CAttack> attack)
{
    attack->visitTarget(m_sharedThis);
    return true;
}

bool CPlayer::updateSource(std::shared_ptr<CAttack> attack)
{
    attack->updateSource(m_sharedThis);
    return true;
}

bool CPlayer::updateTarget(std::shared_ptr<CAttack> attack)
{
    attack->updateTarget(m_sharedThis);
    return true;
}

bool CPlayer::acceptSource(std::shared_ptr<CEquip> equip)
{
    equip->visitSource(m_sharedThis);
    return true;
}

void CPlayer::goToInventory()
{
    int action, height, width;
    std::string label;
    unsigned selected = 0;
    getmaxyx(application.getGame()->getInventoryWindow(), height, width);

    while((action = toupper(wgetch(application.getGame()->getInventoryWindow()))) != 'I')
    {
        if(action == 'X')
        {
            wattroff(application.getGame()->getInventoryWindow(), A_REVERSE);
            werase(application.getGame()->getInventoryWindow());
            wborder(application.getGame()->getInventoryWindow(), 0, 0, 0, 0, 0, 0, 0, 0);   
            wrefresh(application.getGame()->getInventoryWindow());
            return;
        }
        
        switch (action)
        {
            case KEY_UP:
                if(selected != 0)
                    selected--;
            break;
        
            case KEY_DOWN:
                selected++;
                if(selected == m_inventory->getSize())
                    selected = m_inventory->getSize() - 1;
            break;

            default:
                break;
        }

        std::shared_ptr<CItem> item = m_inventory->getItemAt(selected);

        if(item == nullptr)
        {
            wattron(application.getGame()->getInventoryWindow(), A_REVERSE);
            mvwprintw(application.getGame()->getInventoryWindow(),(height - 2) / 2, (width - strlen("NOTHING")) / 2, "  %s  ", "NOTHING");
        }
        else
        {
            wattron(application.getGame()->getInventoryWindow(), A_REVERSE);
            mvwprintw(application.getGame()->getInventoryWindow(), (height - 2) / 2, (width - strlen(item->getLabel().c_str()) - 4) / 2, "   %s   ", item->getLabel().c_str());
        }

        wborder(application.getGame()->getInventoryWindow(), 0, 0, 0, 0, 0, 0, 0, 0);   
        wrefresh(application.getGame()->getInventoryWindow());
  
        if(action == 10)
        {
            useItem(item);
            if(item != nullptr)
                if(item->m_used)
                    m_inventory->eraseItemAt(selected);

            wattroff(application.getGame()->getInventoryWindow(), A_REVERSE);
            werase(application.getGame()->getInventoryWindow());
            wborder(application.getGame()->getInventoryWindow(), 0, 0, 0, 0, 0, 0, 0, 0);   
            wrefresh(application.getGame()->getInventoryWindow());
            return;
        }

        if(action == KEY_BACKSPACE)
        {
            dumpItem(item);
            if(item != nullptr)
                m_inventory->eraseItemAt(selected);

            wattroff(application.getGame()->getInventoryWindow(), A_REVERSE);
            werase(application.getGame()->getInventoryWindow());
            wborder(application.getGame()->getInventoryWindow(), 0, 0, 0, 0, 0, 0, 0, 0);   
            wrefresh(application.getGame()->getInventoryWindow());
            return;
        }
    }
    wattroff(application.getGame()->getInventoryWindow(), A_REVERSE);
    werase(application.getGame()->getInventoryWindow());
    wborder(application.getGame()->getInventoryWindow(), 0, 0, 0, 0, 0, 0, 0, 0);   
    wrefresh(application.getGame()->getInventoryWindow());

    return;
}

bool CPlayer::useItem(std::shared_ptr<CItem> item)
{
    std::shared_ptr<CEvent> equip;
    equip = (new CEquip(m_sharedThis, item))->getPtr();
    application.getGame()->pushEvent(equip);
    return true;    
}

bool CPlayer::dumpItem(std::shared_ptr<CItem> item)
{
    std::shared_ptr<CEvent> discard;
    discard = (new CDiscard(m_sharedThis, item))->getPtr();
    application.getGame()->pushEvent(discard);

    return true;
}
