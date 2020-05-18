#ifndef GAME_H
#define GAME_H

#include <list>
#include <ncurses.h>
#include "CEvent.h"
#include "CMap.h"

class CGame
{
    public:
        CGame() = default;
        ~CGame() = default;
        int m_yMax, m_xMax;
        std::list<CEvent*> event_list;
        CMap* m_currentMap;
        WINDOW* m_Window;
        void run();
        void endGame();
        bool saveGame();
        bool loadGame();

    private:
        void initGame();
        void renderSpace();
        void initMap();

};

#endif