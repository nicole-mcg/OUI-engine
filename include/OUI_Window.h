#ifndef OUI_WINDOW_H
#define OUI_WINDOW_H

#include "OUI_Export.h"
#include "gfx/OUI_Graphics.h"
#include "comp/OUI_Container.h"
#include "event/OUI_Event.h"
#include "comp/OUI_Button.h"
#include "comp/OUI_Panel.h"
#include "comp/OUI_Label.h"
#include "event/OUI_EditEvent.h"
#include <stdint.h>

namespace oui {

    class Context;

    struct QueuedEvent {
        long long queueTime;
        int delay;
        std::function<void()> func;
    };

    class Window: public Container {
        

        private: Context* context;

        private: bool shutdown;

        //Basic window properties
        private: std::u16string title;
        private: bool visible;
        private: char cursorType;
        protected: int globalMouseX;
        protected: int globalMouseY;
        private: bool maximized;
        private: int maximizeX;
        private: int maximizeY;
        private: int maximizeWidth;
        private: int maximizeHeight;
        protected: bool focused;
        private: int editIndex;
        private: std::vector<EditEvent*> editEvents;
        private: std::vector<QueuedEvent*> queuedEvents;
                  

         //Active window properties
        protected: bool moving;
        private: int moveOffX;
        private: int moveOffY;
        protected: bool resizing;
        protected: int resizeX;
        protected: int resizeY;

        //Custimizations
        protected: int cursor;

        protected: bool shiftDown;
        protected: bool ctrlDown;
        protected: bool altDown;

        private: Component* selectedComponent;
        private: Component* rightClickedComponent;

        public: OUI_API ~Window();
        public: OUI_API Window(int width=0, int height=0);

        protected: void initializeWindow(int width, int height);

        public: OUI_API void setContext(Context* context);
        public: OUI_API Context* getContext();

        public: OUI_API virtual void setProfile(const std::u16string& profile) override;

        public: OUI_API virtual bool isWindow() override;

        public: OUI_API virtual int process() override;
        public: OUI_API Graphics* getGraphics();

        public: OUI_API void handleMouseMoveEvent(MouseEvent event);
        public: OUI_API void handleMouseDownEvent(MouseEvent event);
        public: OUI_API void handleMouseUpEvent(MouseEvent event);
        public: OUI_API virtual void handleEvent(Event e);
        public: OUI_API virtual void redraw() override;

        public: OUI_API void setTimeout(int delay, std::function<void()> func);

        public: OUI_API std::u16string getTitle();
        public: OUI_API bool hasFocus();

        public: OUI_API void addEditEvent(EditEvent* e, bool append = false);
        public: OUI_API void undo();
        public: OUI_API void redo();
        
        public: OUI_API bool isShiftDown();
        public: OUI_API bool isCtrlDown();
        public: OUI_API bool isAltDown();

        public: OUI_API void setSelectedComponent(Component* component);
        public: OUI_API Component* getSelectedComponent();
        public: OUI_API void setRightClickedComponent(Component* component);
        public: OUI_API Component* getRightClickedComponent();


        //TODO move to own file (with other functions, sleep, etc.)
        public: OUI_API void setClipboardText(const std::u16string& text);
        public: OUI_API std::u16string getClipboardText();
        public: OUI_API bool hasClipboardText();

        public: OUI_API void close();
        public: OUI_API void setVisible(bool visible);
        public: OUI_API void setPage(std::u16string path);
        public: OUI_API virtual Window* getWindow() override;

        // Abstract methods
        public: OUI_API virtual Graphics* createGraphics(int width, int height);

        public: OUI_API virtual void render();
        public: OUI_API virtual void showWindow();
        public: OUI_API virtual void hideWindow();
        public: OUI_API virtual void setTitle(const std::u16string& title);
        public: OUI_API virtual void setSize(int width, int height);
        public: OUI_API virtual void setPosition(int x, int y);
        public: OUI_API virtual bool setCursor(int cursor);
        public: OUI_API virtual void minimize();
        public: OUI_API virtual void maximize();
    };

}

#endif