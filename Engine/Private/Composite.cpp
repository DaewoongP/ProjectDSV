#include "Composite.h"
#include "GameInstance.h"
USING(Engine)
Composite::Composite()
	: Component()
{
}

Component* Composite::GetComponent(const std::wstring& wstrKey)
{
	auto component = m_umapComponents.find(wstrKey);
	if (component == m_umapComponents.end())
		return nullptr;
	return component->second;
}

void Composite::Update()
{
	for (auto& component : m_umapComponents)
	{
		component.second->Update();
	}

	__super::Update();
}

void Composite::AddComponent(const std::wstring& wstrKey, Component* pComponent)
{
	m_umapComponents.emplace(wstrKey, pComponent);
	Utility::SafeAddRef(pComponent);
}

void Composite::RemoveComponent(const std::wstring& wstrKey)
{
	auto component = GetComponent(wstrKey);
	Utility::SafeRelease(component);
	m_umapComponents.erase(wstrKey);
}
