#include <ncurses.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "enums.h"

// main menu - new game, load game, quit
// new game -> player creation menu and map selection
// load game -> list savegame menu files in directory + timestamp                                                                

class CMenu
{
    protected:
        CMenu()
        {}
        virtual ~CMenu()
        {}
        
        int m_width, m_height;

        std::vector<std::string>::iterator m_it;
        std::vector<std::string> m_options;
        std::string m_lable;
        unsigned int m_selected;
        int m_action;
        WINDOW* m_menuWindow;

    public:
        virtual void loadMenu() = 0;
        virtual void initMenu() = 0;
        virtual void renderMenu() = 0;
        virtual unsigned int getAction() = 0;

        unsigned int getSelected()
        {
            unsigned int tmp = m_selected;
            m_selected = 0;
            return tmp;
        }

        bool is_init = false;
};

class CNewGameMenu : public CMenu
{
    public:
        CNewGameMenu() : CMenu()
        {}
        ~CNewGameMenu()
        {}

        unsigned int getAction()
        {
            return 0;
        }

        void renderMenu()
        {}

        void initMenu()
        {}

        void loadMenu()
        {}

        bool selectMap();
        bool setupPlayer();

    private:
        player_class m_class;
        map_type m_map;
        std::string m_playerName;
        bool m_mapSelect;
        bool m_playerSetup;

};

class CLoadGameMenu : public CMenu
{
    public:
        CLoadGameMenu() : CMenu()
        {}
        ~CLoadGameMenu()
        {}

        unsigned int getAction()
        {
            return 0;
        }

        void renderMenu()
        {}

        void initMenu()
        {}

        void loadMenu()
        {}

        const std::string & getFileName() const;

    private:
        const std::string m_fileName;
        void listDir();
        bool load();

};

class CSaveGameMenu : public CMenu
{
    public:
        CSaveGameMenu() : CMenu()
        {}
        ~CSaveGameMenu()
        {}

        unsigned int getAction()
        {
            return 0;
        }

        void renderMenu()
        {}

        void initMenu()
        {}

        void loadMenu()
        {}

        void setTitle();

    private:
        std::string m_fileName;
        void listDir();
        bool save();
        bool m_newSave;
};


