#ifndef GAME_H
#define GAME_H

#include <list>
#include <ncurses.h>
#include <unistd.h>
#include "CEvent.h"
#include "CMap.h"

class CGame
{
    public:
        CGame() = default;
        ~CGame() = default;
        int m_yMax, m_xMax;
        std::list<CEvent*> event_list;
        CMap* m_currentMap = new CMap;
        WINDOW* m_Window;
        WINDOW* m_eventWindow;
        WINDOW* m_effectWindow;
        WINDOW* m_objectWindow;
        WINDOW* m_playerWindow;
        WINDOW* m_inventoryWindow;
        void run();
        void endGame();
        bool saveGame();
        bool loadGame();

    private:
        void initGame();
        void renderSpace();
        void renderBars();
        void initMap();

};

#endif