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
        WINDOW* m_Window;                   // player or map window
        WINDOW* m_eventWindow;
        WINDOW* m_effectWindow;
        WINDOW* m_objectWindow;
        WINDOW* m_playerWindow;
        WINDOW* m_inventoryWindow;
        void run();
        void pushEvent(CEvent* event);
        bool isRunning();
        void backToGame();
        CMap* getMap() const;

        const int & getYMax() const;
        const int & getXMax() const;

        bool is_init = false;

    private:
        int m_yMax, m_xMax;
        void initGame();
        void loadGame();
        void endGame();
        void initSpace();
        void initBars();
        void initMap();
        void updateEventList();
        std::list<CEvent*> event_list;
        CMap* m_currentMap = new CMap;

};

#endif