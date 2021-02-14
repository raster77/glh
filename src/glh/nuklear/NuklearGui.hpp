#ifndef NUKLEARGUI_HPP
#define NUKLEARGUI_HPP

#include <SFML/Window/Window.hpp>
#include <glad/glad.h>

#ifndef NK_GUI
#define NK_GUI
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "glh/nuklear/nuklear.h"
#include "glh/nuklear/nuklear_sfml_gl3.h"
#endif
#include <string>

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

namespace glh
{

namespace gui
{

    class NuklearGui
    {

        enum Theme { THEME_BLACK, THEME_WHITE, THEME_RED, THEME_BLUE, THEME_DARK };

    public:
        NuklearGui();
        ~NuklearGui();

        void setContext(sf::Window& window);

        void beginEvent();
        void handleEvent(sf::Event& event);
        void endEvent();

        const bool hasFocus() const;

        void update();

        void render();

        const std::string& getTitle() const;
        void setTitle(const std::string& title);

        const int getPosX() const;
        void setPosX(const int x);

        const int getPosY() const;
        void setPosY(const int y);

        void setPosition(const int x, const int y);

        const int getWidth() const;
        void setWidth(const int width);

        const int getHeight() const;
        void setHeight(const int height);

        void setSize(const int width, const int height);

        const bool getAntiAliasing() const;
        void setAntiAliasing(const bool value);

        void setBorder(const bool border);
        const bool hasBorder() const;

        void setMovable(const bool movable);
        const bool isMovable() const;

        void setClosable(const bool closable);
        const bool isClosable() const;

        void setMinimizable(const bool minimizable);
        const bool isMinimizable() const;

        void setScalable(const bool scalable);
        const bool isScalable() const;

        void setShowTitle(const bool show);
        const bool isShowTitle() const;

        void setTheme(const Theme theme);

    protected:
        sf::Window* window;
        nk_context* ctx;
        nk_font_atlas* atlas;

        virtual void setGui() = 0;

        virtual void setFont()
        {
        }

        const unsigned int getBorder() const;
        const unsigned int getMovable() const;
        const unsigned int getClosable() const;
        const unsigned int getScalable() const;
        const unsigned int getMinimizable() const;
        const unsigned int getShowTitle() const;

    private:
        std::string mTitle;
        int mPosX;
        int mPosY;
        int mWidth;
        int mHeight;
        bool mAntiAliasing;
        bool mHasFocus;
        bool mBorder;
        bool mMovable;
        bool mClosable;
        bool mScalable;
        bool mMinimizable;
        bool mShowTitle;
    };
}
}

#endif // NUKLEARGUI_HPP
