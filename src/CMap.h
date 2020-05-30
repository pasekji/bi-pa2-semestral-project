#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <map>
#include "CGameObject.h"
#include "CCharacter.h"
#include "CDoor.h"
#include "CPlayer.h"
#include "CPlayerPaladin.h"
#include "CEnemy.h"
#include "CProp.h"

class CMap
{
    public:
        CMap() = default;
        ~CMap() = default;    
        void loadMap();                                 // load all objects in map and render
        void demo_loadMap();                            // demo loadMap() for testing only
        bool loadMapFromFile(const std::string & pathToFile);
        bool openDoor(CDoor* door);
        bool goToMap(CMap* map);
        bool colisionDetect(std::pair<int, int> & pair);
        void staticCamera(direction & dir, int & steps);
        int m_width, m_height;
        int m_yMax, m_xMax;
        WINDOW* m_mapWindow;

    private:
        std::string m_pathToFile;
        std::string m_locationName;
        CDoor* m_upperLayer;
        std::vector<CCharacter*> m_moveableObjects;
        std::vector<CGameObject*> m_imoveableObjects;
        std::map<std::pair<int, int>, CGameObject*> m_targets;
        std::map<CDoor, CMap*> m_layers;                     // current layer must be included too - TODO: get position at target map
        void spawnPlayer(int posY, int posX, player_class playerClass);           // (int posY, int posX)
        void spawnEnemy(int posY, int posX, enemy_type type);
        void spawnProp(int posY, int posX, const char & objectForm);
        void renderObjects();                           // only new render of objects
        void moveableDoAction();                        // invoke action to change properties of instance. posX++ (once)
        void camera_objectsUp(int & steps);
        void camera_objectsDown(int & steps);
        void camera_objectsLeft(int & steps);
        void camera_objectsRight(int & steps);
    
};

#endif