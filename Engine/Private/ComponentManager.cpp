#include "ComponentManager.h"
USING(Engine)

IMPLEMENT_SINGLETON(ComponentManager)

HRESULT ComponentManager::Initialize(_uint _numLevels)
{
    mPrototypes.resize(_numLevels);

    return S_OK;
}

HRESULT ComponentManager::AddPrototype(_uint _levelIndex, const std::wstring& _prototypeTag, std::shared_ptr<Component> _prototype)
{
    std::shared_ptr<Component> prototype = Find_Prototype(_levelIndex, _prototypeTag); 
    NULL_CHECK_RETURN_MSG(!prototype, E_FAIL, TEXT("Existing prototype"))

    mPrototypes[_levelIndex].emplace(_prototypeTag, _prototype);

    return S_OK;
}

std::shared_ptr<Component> ComponentManager::CloneComponent(_uint _levelIndex, const std::wstring& _prototypeTag, void* pArg)
{
    std::shared_ptr<Component> prototype = Find_Prototype(_levelIndex, _prototypeTag);
    NULL_CHECK_RETURN_MSG(prototype, std::shared_ptr<Component>(), TEXT("Can't Find Component"))

    std::shared_ptr<Component> component = prototype->Clone(pArg);
    if (nullptr == component)
        return std::shared_ptr<Component>();

    return component;
}

void ComponentManager::ClearLevelResources(_uint _levelIndex)
{
    if (_levelIndex >= mPrototypes.size())
        return;

    mPrototypes[_levelIndex].clear();
}

std::shared_ptr<Component> ComponentManager::Find_Prototype(_uint _levelIndex, const std::wstring& _prototypeTag)
{
    auto iter = mPrototypes[_levelIndex].find(_prototypeTag);

    if (iter == mPrototypes[_levelIndex].end())
        return std::shared_ptr<Component>();

    return iter->second;
}

