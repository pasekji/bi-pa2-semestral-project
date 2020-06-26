#ifndef GAME_H
#define GAME_H

#include <deque>
#include <ncurses.h>
#include <unistd.h>
#include <memory>
#include "CEvent.h"
#include "CMap.h"

class CGame
{
    public:
        CGame() = default;
        ~CGame()
        {
            delwin(m_Window);
            delwin(m_eventWindow);
            delwin(m_effectWindow);
            delwin(m_objectWindow);
            delwin(m_playerWindow);
            delwin(m_inventoryWindow);
        }

        void run();
        void pushEvent(CEvent* event);
        bool isRunning();
        void backToGame();

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
        bool m_build = false;

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
        void printEvents();
        std::deque<CEvent*> m_eventQueue;
        CMap* m_currentMap = std::make_shared<CMap>();

};

#endif