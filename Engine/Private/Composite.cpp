#include "Composite.h"
#include "GameInstance.h"
#include "LevelManager.h"
USING(Engine)
Composite::Composite()
	: Component()
{
}

Composite::Composite(const Composite& rhs)
	: Component(rhs)
{
}

std::shared_ptr<Component> Composite::GetComponent(const std::wstring& _key)
{
	return FindComponent(_key);
}

void Composite::Tick(_float _timeDelta)
{
	for (auto& component : mComponents)
	{
		component.second->Tick(_timeDelta);
	}

	__super::Tick(_timeDelta);
}

void Composite::LateTick(_float _timeDelta)
{
	for (auto& component : mComponents)
	{
		component.second->LateTick(_timeDelta);
	}

	__super::LateTick(_timeDelta);
}

std::shared_ptr<Component> Composite::AddComponent(const std::wstring& _prototypeKey, const std::wstring& _componentKey, void* _arg, _int _levelIndex)
{
	if (-1 == _levelIndex)
	{
		_levelIndex = LEVEL->GetCurrentLevelIndex();
	}

	NULL_CHECK_RETURN_MSG(!GetComponent(_componentKey), std::shared_ptr<Component>(), TEXT("Existing component"));

	// Clone component
	std::shared_ptr<Component> component = GAME->CloneComponent(_levelIndex, _prototypeKey, _arg);
	if (nullptr == component)
		return std::shared_ptr<Component>();

	mComponents.emplace(_componentKey, component);
	return component;
}

std::shared_ptr<Component> Composite::FindComponent(const std::wstring& _key)
{
	auto	iter = mComponents.find(_key);

	if (iter == mComponents.end())
		return nullptr;

	return iter->second;
}

size_t Composite::RemoveComponent(const std::wstring& _key)
{
	return mComponents.erase(_key);
}