#include "RenderManager.h"
#include "Component.h"

USING(Engine)

IMPLEMENT_SINGLETON(RenderManager)

RenderManager::~RenderManager()
{
	for (_uint i = 0; i < static_cast<_uint>(RenderType::TYPEEND); ++i)
	{
		ClearRenderGroup(static_cast<RenderType>(i));
	}
}

HRESULT RenderManager::Initialize()
{
	return S_OK;
}

void RenderManager::AddRenderGroup(RenderType _renderType, Component* _component)
{
	m_arrRenderComponents[static_cast<_uint>(_renderType)].emplace_back(_component);
	Utility::SafeAddRef(_component);
}

HRESULT RenderManager::Draw()
{
	FAILED_RETURN(RenderPriority(), E_FAIL);

	return S_OK;
}

#pragma region RenderTargets
HRESULT RenderManager::RenderPriority()
{
	for (auto& component : m_arrRenderComponents[static_cast<_uint>(RenderType::PRIORITY)])
	{
		if (nullptr != component)
			component->Render();
		Utility::SafeRelease(component);
	}

	m_arrRenderComponents[static_cast<_uint>(RenderType::PRIORITY)].clear();

	return S_OK;
}
#pragma endregion

HRESULT RenderManager::AddComponents()
{
	// 셰이더 컴포넌트 추가 예정
	
	return S_OK;
}

void RenderManager::ClearRenderGroup(RenderType eRenderType)
{
	auto& currentComponents = m_arrRenderComponents[static_cast<_uint>(eRenderType)];
	for (auto& component : currentComponents)
	{
		Utility::SafeRelease(component);
	}
	currentComponents.clear();
}
