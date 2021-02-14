#ifndef SCENE_HPP
#define SCENE_HPP

#include "glh/core/Image.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <glad/glad.h>
#include <glm/detail/type_vec2.hpp>
#include <iostream>
#include <memory>

class Scene
{
public:
    Scene();
    Scene(sf::Window* window);
    virtual ~Scene();

    virtual void update(const float dt) = 0;
    virtual void draw() = 0;
    virtual void preHandleEvent() = 0;
    virtual void handleEvent(sf::Event& event) = 0;
    virtual void postHandleEvent() = 0;
    virtual void load() = 0;

    void setWindow(sf::Window* window);
    const std::string& getTitle() const;
    void setTitle(const std::string& title);
    void screenShot();
    
    typedef std::unique_ptr<Scene> ScenePtr;

protected:
    std::string mTitle;
    glm::vec2 mousePos;
    sf::Window* window;
    bool enableMouseEvent;

    const sf::Vector2f getWindowCenter() const;
    const float getWindowWidth() const;
    const float getWindowHeight() const;
    const float getWindowRatio() const;
    const glm::vec2 getMousePosition() const;
};

#endif // SCENE_HPP
