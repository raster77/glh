#include "NuklearGui.hpp"
#include <iostream>
#ifndef NK_IMPLEMENTATION
#define NK_IMPLEMENTATION
#define NK_SFML_GL3_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sfml_gl3.h"
#endif

glh::gui::NuklearGui::NuklearGui()
    : window(nullptr)
    , ctx(nullptr)
    , atlas(nullptr)
    , mTitle("")
    , mPosX(0)
    , mPosY(0)
    , mWidth(200)
    , mHeight(200)
    , mAntiAliasing(false)
    , mHasFocus(false)
    , mBorder(true)
    , mMovable(true)
    , mClosable(true)
    , mScalable(true)
    , mMinimizable(true)
    , mShowTitle(true)
{
}

glh::gui::NuklearGui::~NuklearGui()
{
    nk_sfml_shutdown();
}

void glh::gui::NuklearGui::setContext(sf::Window& window)
{
    if(this->window == nullptr) {
        this->window = &window;
        ctx = nk_sfml_init(this->window);

        nk_sfml_font_stash_begin(&atlas);
        nk_sfml_font_stash_end();

        setFont();
    }
}

void glh::gui::NuklearGui::update()
{
    if(nk_begin(ctx, mTitle.c_str(), nk_rect(mPosX, mPosY, mWidth, mHeight),
           getBorder() | getMovable() | getScalable() | getMinimizable() | getShowTitle())) {
        setGui();
    }
    nk_end(ctx);
}

void glh::gui::NuklearGui::beginEvent()
{
    nk_input_begin(ctx);
}

void glh::gui::NuklearGui::handleEvent(sf::Event& event)
{
    nk_sfml_handle_event(&event);
}

void glh::gui::NuklearGui::endEvent()
{
    nk_input_end(ctx);
}

bool const glh::gui::NuklearGui::hasFocus() const
{
    return nk_window_is_any_hovered(ctx) == 1;
}

void glh::gui::NuklearGui::render()
{
    if(mAntiAliasing)
        nk_sfml_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
    else
        nk_sfml_render(NK_ANTI_ALIASING_OFF, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

const std::string& glh::gui::NuklearGui::getTitle() const
{
    return mTitle;
}

void glh::gui::NuklearGui::setTitle(const std::string& title)
{
    mTitle = title;
}

const int glh::gui::NuklearGui::getPosX() const
{
    return mPosX;
}

void glh::gui::NuklearGui::setPosX(const int x)
{
    mPosX = x;
}

const int glh::gui::NuklearGui::getPosY() const
{
    return mPosY;
}

void glh::gui::NuklearGui::setPosY(const int y)
{
    mPosY = y;
}

void glh::gui::NuklearGui::setPosition(const int x, const int y)
{
    mPosX = x;
    mPosY = y;
}

const int glh::gui::NuklearGui::getWidth() const
{
    return mWidth;
}

void glh::gui::NuklearGui::setWidth(const int width)
{
    mWidth = width;
}

const int glh::gui::NuklearGui::getHeight() const
{
    return mHeight;
}

void glh::gui::NuklearGui::setHeight(const int height)
{
    mHeight = height;
}

void glh::gui::NuklearGui::setSize(const int width, const int height)
{
    mWidth = width;
    mHeight = height;
}

const bool glh::gui::NuklearGui::getAntiAliasing() const
{
    return mAntiAliasing;
}

void glh::gui::NuklearGui::setAntiAliasing(const bool value)
{
    mAntiAliasing = value;
}

void glh::gui::NuklearGui::setBorder(const bool border)
{
    mBorder = border;
}

const bool glh::gui::NuklearGui::hasBorder() const
{
    return mBorder;
}

void glh::gui::NuklearGui::setMovable(const bool movable)
{
    mMovable = movable;
}

const bool glh::gui::NuklearGui::isMovable() const
{
    return mMovable;
}

void glh::gui::NuklearGui::setClosable(const bool closable)
{
    mClosable = closable;
}

const bool glh::gui::NuklearGui::isClosable() const
{
    return mClosable;
}

void glh::gui::NuklearGui::setMinimizable(const bool minimizable)
{
    mMinimizable = minimizable;
}

const bool glh::gui::NuklearGui::isMinimizable() const
{
    return mMinimizable;
}

void glh::gui::NuklearGui::setScalable(const bool scalable)
{
    mScalable = scalable;
}

const bool glh::gui::NuklearGui::isScalable() const
{
    return mScalable;
}

void glh::gui::NuklearGui::setShowTitle(const bool show)
{
    mShowTitle = show;
}

const bool glh::gui::NuklearGui::isShowTitle() const
{
    return mShowTitle;
}

const unsigned int glh::gui::NuklearGui::getBorder() const
{
    return mBorder ? NK_WINDOW_BORDER : '\0';
}

const unsigned int glh::gui::NuklearGui::getMovable() const
{
    return mMovable ? NK_WINDOW_MOVABLE : '\0';
}

const unsigned int glh::gui::NuklearGui::getClosable() const
{
    return mClosable ? NK_WINDOW_CLOSABLE : '\0';
}

const unsigned int glh::gui::NuklearGui::getScalable() const
{
    return mScalable ? NK_WINDOW_SCALABLE : '\0';
}

const unsigned int glh::gui::NuklearGui::getMinimizable() const
{
    return mMinimizable ? NK_WINDOW_MINIMIZABLE : '\0';
}

const unsigned int glh::gui::NuklearGui::getShowTitle() const
{
    return mShowTitle ? NK_WINDOW_TITLE : '\0';
}

void glh::gui::NuklearGui::setTheme(const Theme theme)
{
    struct nk_color table[NK_COLOR_COUNT];
    if(theme == THEME_WHITE) {
        table[NK_COLOR_TEXT] = nk_rgba(70, 70, 70, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_HEADER] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_BORDER] = nk_rgba(0, 0, 0, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(185, 185, 185, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(170, 170, 170, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(160, 160, 160, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(150, 150, 150, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(120, 120, 120, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_SELECT] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(80, 80, 80, 255);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(70, 70, 70, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(60, 60, 60, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_EDIT] = nk_rgba(150, 150, 150, 255);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(0, 0, 0, 255);
        table[NK_COLOR_COMBO] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_CHART] = nk_rgba(160, 160, 160, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(45, 45, 45, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(180, 180, 180, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(140, 140, 140, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(150, 150, 150, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(160, 160, 160, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(180, 180, 180, 255);
        nk_style_from_table(ctx, table);
    } else if(theme == THEME_RED) {
        table[NK_COLOR_TEXT] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(30, 33, 40, 215);
        table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
        table[NK_COLOR_BORDER] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(190, 50, 70, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(195, 55, 75, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SELECT] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(186, 50, 74, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(191, 55, 79, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_EDIT] = nk_rgba(51, 55, 67, 225);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_COMBO] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(170, 40, 60, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(30, 33, 40, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(181, 45, 69, 220);
        nk_style_from_table(ctx, table);
    } else if(theme == THEME_BLUE) {
        table[NK_COLOR_TEXT] = nk_rgba(20, 20, 20, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(202, 212, 214, 215);
        table[NK_COLOR_HEADER] = nk_rgba(137, 182, 224, 220);
        table[NK_COLOR_BORDER] = nk_rgba(140, 159, 173, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(142, 187, 229, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(147, 192, 234, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(177, 210, 210, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(182, 215, 215, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_SELECT] = nk_rgba(177, 210, 210, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(177, 210, 210, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(137, 182, 224, 245);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(142, 188, 229, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(147, 193, 234, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_EDIT] = nk_rgba(210, 210, 210, 225);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(20, 20, 20, 255);
        table[NK_COLOR_COMBO] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_CHART] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(190, 200, 200, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(156, 193, 220, 255);
        nk_style_from_table(ctx, table);
    } else if(theme == THEME_DARK) {
        table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(57, 67, 71, 215);
        table[NK_COLOR_HEADER] = nk_rgba(51, 51, 56, 220);
        table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(58, 93, 121, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(63, 98, 126, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 53, 56, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_SELECT] = nk_rgba(57, 67, 61, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(48, 83, 111, 245);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_EDIT] = nk_rgba(50, 58, 61, 225);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_COMBO] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_CHART] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 83, 111, 255);
        nk_style_from_table(ctx, table);
    } else {
        nk_style_default(ctx);
    }
}