#pragma once
#include "Component.h"

BEGIN(Engine)

class RenderManager
{
	DECLARE_SINGLETON(RenderManager)
public:
	enum class RenderType { PRIORITY, TYPEEND };

public:
	RenderManager() = default;
	~RenderManager() = default;

public:
	HRESULT Initialize();

public:
	void	AddRenderGroup(RenderType _renderType, std::shared_ptr<Component> _component);
	HRESULT Draw();

private:
	HRESULT RenderPriority();
	HRESULT RenderNonBlend();
	HRESULT RenderLights();
	HRESULT RenderDeferred();
	HRESULT RenderNonLight();
	HRESULT RenderBlend();
	HRESULT RenderPostProcessing();
	HRESULT RenderUI();

private:
	HRESULT AddComponents();

private:
	std::list<std::shared_ptr<Component>>	mRenderComponents[static_cast<_uint>(RenderType::TYPEEND)];
};

END

#define RENDER			GET_SINGLE(Engine::RenderManager)