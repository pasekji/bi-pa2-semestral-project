#include "CMap.h"
#include "CApplication.h"
#include <ctype.h>

extern CApplication application;

void CMap::loadMap()            
{
    // no predef ROOM_HEIGHT othr. will be used 
    spawnPlayer(((int)(application.getGame().getYMax() * 0.99) - 2) / 2, ((int)(application.getGame().getXMax() * 0.633) - 2) / 2, PALADIN);
    return;
}

bool CMap::collisionDetect(std::pair<int, int> & pair)
{
    for (auto i: m_moveableObjects)
    {
        if(i->getPos() == pair)
            return true;
    }

    for (auto i: m_imoveableObjects)
    {
        if(i->getPos() == pair)
            return true;
    }

    return false;
}

void CMap::demo_loadMap()
{

    // no predef ROOM_HEIGHT or othr. will be used 
    spawnEnemy(((ROOM_HEIGHT - (ROOM_HEIGHT/5))/2), (ROOM_WIDTH - 2) / 2, BASILISK);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20)), WALL);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20) - 1), WALL);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20) - 2), WALL);

    return;
}

void CMap::renderObjects()
{
    for(auto i: m_moveableObjects)
    {
        i->objectRender();
    }

    for(auto i: m_imoveableObjects)
    {
        i->objectRender();
    }

    return;
}

void CMap::moveableDoAction()
{
    for(auto i = ++m_moveableObjects.begin(); i != m_moveableObjects.end(); ++i)
    {
        (*i)->getAction();
    }

    return;
}

void CMap::spawnPlayer(int posY, int posX, player_class playerClass)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
        throw std::invalid_argument("received overlapping coordinates with other object");

    switch (playerClass)
    {
        case PALADIN:
            m_player = new CPlayerPaladin(m_mapWindow, posY, posX);
            break;
        case MAGE:
            m_player = new CPlayerMage(m_mapWindow, posY, posX);
            break;
        case ROGUE:
            m_player = new CPlayerRogue(m_mapWindow, posY, posX);
            break;
        default:
            break;
    }
        
    m_moveableObjects.push_back(m_player);
    m_targets.push_back(m_player);
    demo_loadMap();
    wrefresh(m_mapWindow);
    catchPlayer();


    return;
}

CPlayer* CMap::getPlayer() const            // not needed
{
    return m_player;
}

CGameObject* CMap::getTargetObject(std::pair<int, int> & pair) const
{
    for(auto i : m_targets)
    {
        if(i->getPos() == pair)
        {
            i->showStats();
            return i;
        }
    } 
    
    return nullptr;
}

void CMap::catchPlayer()
{
    while (toupper(m_player->getAction()) != 'X')    
    {
        m_player->showStats();
        moveableDoAction();
        renderObjects();
        wrefresh(m_mapWindow);
        wrefresh(application.getGame().getPlayerWindow());

    }   
    
    clear();
    refresh();

    return;                 // resenim tech vice sracek je ze se mi tady cyklus ve volani void funkci... 
                            // extern application je třeba používat pouze na get/set
}

void CMap::spawnEnemy(int posY, int posX, enemy_type type)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
        throw std::invalid_argument("received overlapping coordinates with other object");
    
    CEnemy* enemy = new CEnemy(m_mapWindow, posY, posX, type);
    m_moveableObjects.push_back(enemy);
    m_targets.push_back(enemy);

    return;
}

void CMap::spawnProp(int posY, int posX, prop_type type)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
        throw std::invalid_argument("received overlapping coordinates with other object");

    CProp* prop = new CProp(m_mapWindow, posY, posX, type);
    m_imoveableObjects.push_back(prop);

    return;
}

void CMap::staticCamera(direction & dir, int & steps)
{
    switch (dir)
    {
        case UP:
            camera_objectsDown(steps);
            renderObjects();
            break;
    
        case DOWN:
            camera_objectsUp(steps);
            renderObjects();
            break;
        
        case LEFT:
            camera_objectsRight(steps);
            renderObjects();
            break;

        case RIGHT:
            camera_objectsLeft(steps);
            renderObjects();
            break;
        
        default:
            break;
    }

    return;
}

void CMap::camera_objectsDown(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveDown(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveDown(steps);
    }

    return;
}

void CMap::camera_objectsUp(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveUp(steps);    
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveUp(steps);
    }

    return;
}

void CMap::camera_objectsRight(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveRight(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveRight(steps);
    }

    return;
}

void CMap::camera_objectsLeft(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveLeft(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveLeft(steps);
    }

    return;  
}


void CMap::save(ofstream& os)
{
    writeString(os, m_locationName);
    m_player->save(os);
    os << m_moveableObjects.size();
    for (auto moveable : m_moveableObjects)
    {
        moveable->save(os);
    }
    // std::vector<CGameObject*> m_imoveableObjects;
    // std::vector<CGameObject*> m_targets;
}

void CMap::load(ifstream& is)
{
    m_locationName = loadString(is);
    size_t m_moveableObjectsSize;
    is >> m_moveableObjectsSize;
    for(size_t i = 0; i < m_moveableObjectsSize; i++)
    {
        m_moveableObjects.push_back(nullptr); // zavolat CGameObject::load()
    }
}