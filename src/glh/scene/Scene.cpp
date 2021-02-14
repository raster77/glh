#include "Scene.hpp"

Scene::Scene()
    : mTitle("")
    , mousePos(0.f)
    , enableMouseEvent(true)
{
}

Scene::Scene(sf::Window* window)
    : mTitle("")
    , mousePos(0.f)
    , window(window)
    , enableMouseEvent(true)
{
}

Scene::~Scene()
{
}

void Scene::setWindow(sf::Window* window)
{
    this->window = window;
}

const std::string& Scene::getTitle() const
{
    return mTitle;
}

void Scene::setTitle(const std::string& title)
{
    mTitle = title;
}

void Scene::screenShot()
{
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    int w = window->getSize().x;
    int h = window->getSize().y;

    glh::Image imgCapture;

    imgCapture.create(w, h, glh::Color(0.f, 0.f, 0.f, 1.f));
    std::cout << w << " " << h << std::endl;
    std::vector<unsigned char> pixels;

    glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, imgCapture.getPixelsPtr());

    imgCapture.flipVertically();

    std::string fileName = "capture.jpg";
    imgCapture.saveToFile(fileName);
}

const sf::Vector2f Scene::getWindowCenter() const
{
    sf::Vector2f c = static_cast<sf::Vector2f>(window->getSize());
    return c * 0.5f;
}

const float Scene::getWindowWidth() const
{
    return static_cast<float>(window->getSize().x);
}

const float Scene::getWindowHeight() const
{
    return static_cast<float>(window->getSize().y);
}

const float Scene::getWindowRatio() const
{
    return getWindowWidth() / getWindowHeight();
}

const glm::vec2 Scene::getMousePosition() const
{
    sf::Vector2f v = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
    return glm::vec2(v.x, v.y);
}
