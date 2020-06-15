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

        void run();
        void pushEvent(CEvent* event);
        bool isRunning();
        void backToGame();

        void showObjectStats(CGameObject* object) const;

        CMap* getMap() const;
        WINDOW* getWindow() const;
        WINDOW* getPlayerWindow() const;
        WINDOW* getEventWindow() const;
        WINDOW* getEffectWindow() const;
        WINDOW* getObjectWindow() const;
        WINDOW* getInventoryWindow() const;


        const int & getYMax() const;
        const int & getXMax() const;

        bool is_init = false;

    private:
        WINDOW* m_Window;                   // player or map window
        WINDOW* m_eventWindow;
        WINDOW* m_effectWindow;
        WINDOW* m_objectWindow;
        WINDOW* m_playerWindow;
        WINDOW* m_inventoryWindow;
        int m_yMax, m_xMax;
        void initGame();
        void loadGame();
        void endGame();
        void initSpace();
        void initBars();
        void initMap();
        void updateEventList();
        void clearWindows() const;
        void correctMainWindow() const;
        void correctPlayerWindow() const;
        void correctEventWindow() const;
        void correctObjectWindow() const;
        void correctInventoryWindow() const;
        void correctEffectWindow() const;
        void refreshBars() const;
        std::list<CEvent*> event_list;
        CMap* m_currentMap = new CMap;

};

#endif