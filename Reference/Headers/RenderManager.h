#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class Component;
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
	void	AddRenderGroup(RenderType _renderType, Component* _component);
	HRESULT Draw();

private:
	HRESULT RenderPriority();

private:
	HRESULT AddComponents();
	void	ClearRenderGroup(RenderType eRenderType);

private:
	std::array<std::list<Component*>, static_cast<_uint>(RenderType::TYPEEND)>	m_arrRenderComponents;
};

END

#define RENDER			GET_SINGLE(Engine::RenderManager)