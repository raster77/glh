#include "SceneManager.hpp"


SceneManager::SceneManager(sf::Window* window)
        : mWindow(window)
        , mCurrentScene(nullptr)
        , mPreviousScene(nullptr)
        , mSwitch(0)
        , index(0)
{
}

SceneManager::~SceneManager()
{
}

Scene* SceneManager::getScene()
{
    return mCurrentScene.get();
}

void SceneManager::loadScene(const std::size_t& idx)
{
    if(idx <= sceneNames.size() -1) {
        loadScene(sceneNames[idx]);
    }
}

void SceneManager::loadScene(const std::string& sceneName)
{
    mNextScene = sceneName;
    mSwitch = true;
    switchState();
    mCurrentScene.get()->load();
    mWindow->setTitle(mCurrentScene.get()->getTitle());
    std::vector<std::string>::iterator it;
    it = std::find(sceneNames.begin(), sceneNames.end(), sceneName);
    if(it != sceneNames.end())
        index = it - sceneNames.begin();
}

Scene* SceneManager::next()
{
    if(index + 1 >= sceneNames.size())
        index = 0;
    else
        index++;

    loadScene(sceneNames[index]);
    return mCurrentScene.get();
}

Scene* SceneManager::previous()
{
    if(index == 0)
        index = sceneNames.size() - 1;
    else
        index--;
    loadScene(sceneNames[index]);
    return mCurrentScene.get();
}

Scene::ScenePtr SceneManager::createScene(const std::string& sceneName)
{
    auto found = mScenes.find(sceneName);
    assert(found != mScenes.end());
    return found->second();
}

void SceneManager::switchState()
{
    mCurrentScene.reset();
    if(mPreviousScene != nullptr && mPreviousScene->getTitle() == mNextScene)
        mCurrentScene = std::move(mPreviousScene);
    else
        mCurrentScene = std::move(createScene(mNextScene));

    mSwitch = false;
}
