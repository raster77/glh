#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <SFML/Window/Window.hpp>
#include <cassert>
#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include "Scene.hpp"

class SceneManager
{
public:
    SceneManager(sf::Window* window);
    ~SceneManager();
    
    Scene* getScene();
    void loadScene(const std::string& sceneName);
    void loadScene(const std::size_t& idx);
    Scene* next();
    Scene* previous();
    
    template <typename T> void registerScene(const std::string& sceneName);
    
private:
    sf::Window* mWindow;
    Scene::ScenePtr mCurrentScene;
    Scene::ScenePtr mPreviousScene;
    std::string mNextScene;
    bool mSwitch;
    std::size_t index;
    std::vector<std::string> sceneNames;
    std::unordered_map<std::string, std::function<Scene::ScenePtr()>> mScenes;
    
    Scene::ScenePtr createScene(const std::string& sceneName);
    void switchState();

};

template <typename T> void SceneManager::registerScene(const std::string& sceneName)
{
    sceneNames.emplace_back(sceneName);
    mScenes[sceneName] = [this]() {
        Scene::ScenePtr d(new T(mWindow));
        d.get()->setTitle(mNextScene);
        return d;
    };
}

#endif // SCENEMANAGER_HPP
