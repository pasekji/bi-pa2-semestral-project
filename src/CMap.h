#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "CGameObject.h"
#include "CCharacter.h"
#include "CPlayer.h"
#include "CPlayerPaladin.h"
#include "CPlayerRogue.h"
#include "CPlayerMage.h"
#include "CEnemy.h"
#include "CProp.h"
#include <fstream>

using namespace std;

class CMap
{
    public:
        CMap() = default;
        ~CMap() = default;    
        void loadMap();                                 // load all objects in map and render
        void demo_loadMap();                            // demo loadMap() for testing only
        bool loadMapFromFile(const std::string & pathToFile);
        bool collisionDetect(std::pair<int, int> & pair);
        void staticCamera(direction & dir, int & steps);
        int m_width, m_height;
        WINDOW* m_mapWindow;

        CPlayer* getPlayer() const;

        CGameObject* getTargetObject(std::pair<int, int> & pair) const;

        void catchPlayer();
        void save(ofstream& os);
        void load(ifstream& is);

    private:
        std::string m_pathToFile;
        std::string m_locationName;     
        CPlayer* m_player;
        std::vector<CCharacter*> m_moveableObjects;
        std::vector<CGameObject*> m_imoveableObjects;
        std::vector<CGameObject*> m_targets;
        void spawnPlayer(int posY, int posX, player_class playerClass);           // (int posY, int posX)
        void spawnEnemy(int posY, int posX, enemy_type type);
        void spawnProp(int posY, int posX, prop_type type);
        void renderObjects();                           // only new render of objects
        void moveableDoAction();                        // invoke action to change properties of instance. posX++ (once)
        void camera_objectsUp(int & steps);
        void camera_objectsDown(int & steps);
        void camera_objectsLeft(int & steps);
        void camera_objectsRight(int & steps);
    
};

#endif