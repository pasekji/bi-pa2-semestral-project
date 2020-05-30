#include <ncurses.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "enums.h"

// main menu - new game, load game, quit
// new game -> player creation menu and map selection
// load game -> list savegame menu files in directory + timestamp

/*
 _   _ _____   _   _   ___  ___  ___ _____  ____________ _____ 
| \ | |  _  | | \ | | / _ \ |  \/  ||  ___| | ___ \ ___ \  __ \
|  \| | | | | |  \| |/ /_\ \| .  . || |__   | |_/ / |_/ / |  \/
| . ` | | | | | . ` ||  _  || |\/| ||  __|  |    /|  __/| | __ 
| |\  \ \_/ / | |\  || | | || |  | || |___  | |\ \| |   | |_\ \
\_| \_/\___/  \_| \_/\_| |_/\_|  |_/\____/  \_| \_\_|    \____/
                                                                 
*/                                                                 

class CMenu
{
    protected:
        CMenu() = default;
        virtual ~CMenu()
        {}
        
        int m_width, m_height;

        std::vector<std::string>::iterator m_it;
        std::vector<std::string> m_options;
        std::size_t m_selected;
        std::string m_lable;
        int m_action;

    public:
        WINDOW* m_menuWindow;
        virtual void renderMenu() = 0;
        virtual int getAction() = 0;

};

class CMainMenu : public CMenu
{
    public:
        CMainMenu() : CMenu()
        {}
        ~CMainMenu()
        {}

        int getAction()
        {
            return 0;
        }

        void renderMenu()
        {}
    
    private:
        const std::vector<std::string> m_logo;
        
};

class CNewGameMenu : public CMenu
{
    public:
        CNewGameMenu() : CMenu()
        {}
        ~CNewGameMenu()
        {}

        int getAction()
        {
            return 0;
        }

        void renderMenu()
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

        int getAction()
        {
            return 0;
        }

        void renderMenu()
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

        int getAction()
        {
            return 0;
        }

        void renderMenu()
        {}

        void setTitle();

    private:
        std::string m_fileName;
        void listDir();
        bool save();
        bool m_newSave;
};


