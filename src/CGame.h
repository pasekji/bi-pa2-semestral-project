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
        WINDOW* m_Window;                   // player or map window
        WINDOW* m_eventWindow;
        WINDOW* m_effectWindow;
        WINDOW* m_objectWindow;
        WINDOW* m_playerWindow;
        WINDOW* m_inventoryWindow;
        void run();
        void endGame();
        void pushEvent(CEvent* event);
        bool isRunning();
        void backToGame();
        CMap* getMap();

    private:
        void initGame();
        void initSpace();
        void initBars();
        void initMap();
        void updateEventList();
        std::list<CEvent*> event_list;
        CMap* m_currentMap = new CMap;

};

#endif