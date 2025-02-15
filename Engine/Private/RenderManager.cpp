#include "RenderManager.h"

USING(Engine)

IMPLEMENT_SINGLETON(RenderManager)

HRESULT RenderManager::Initialize()
{
	return S_OK;
}

void RenderManager::AddRenderGroup(RenderType _renderType, std::shared_ptr<Component> _component)
{
	NULL_CHECK_RETURN_MSG(_component.get(), , TEXT("Component is NULL"));
	
	mRenderComponents[static_cast<_uint>(_renderType)].emplace_back(_component);
}

HRESULT RenderManager::Draw()
{
	FAILED_RETURN(RenderPriority(), E_FAIL);
	FAILED_RETURN(RenderNonBlend(), E_FAIL);
	FAILED_RETURN(RenderLights(), E_FAIL);
	FAILED_RETURN(RenderDeferred(), E_FAIL);
	FAILED_RETURN(RenderNonLight(), E_FAIL);
	FAILED_RETURN(RenderBlend(), E_FAIL);
	FAILED_RETURN(RenderPostProcessing(), E_FAIL);
	FAILED_RETURN(RenderUI(), E_FAIL);

	return S_OK;
}

#pragma region RenderTargets
HRESULT RenderManager::RenderPriority()
{
	for (auto& component : mRenderComponents[static_cast<_uint>(RenderType::PRIORITY)])
	{
		if (nullptr != component)
			component->Render();
	}

	mRenderComponents[static_cast<_uint>(RenderType::PRIORITY)].clear();

	return S_OK;
}

HRESULT RenderManager::RenderNonBlend()
{
	return S_OK;
}

HRESULT RenderManager::RenderLights()
{
	return S_OK;
}

HRESULT RenderManager::RenderDeferred()
{
	return S_OK;
}

HRESULT RenderManager::RenderNonLight()
{
	return S_OK;
}

HRESULT RenderManager::RenderBlend()
{
	return S_OK;
}

HRESULT RenderManager::RenderPostProcessing()
{
	return S_OK;
}

HRESULT RenderManager::RenderUI()
{
	return S_OK;
}
#pragma endregion

HRESULT RenderManager::AddComponents()
{
	// 셰이더 컴포넌트 추가 예정
	
	return S_OK;
}