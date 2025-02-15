#pragma once
#include "Composite.h"
#include "Shader.h"
#include "Texture.h"
#include "RectBuffer.h"

BEGIN(Engine)

class ComponentManager
{
	DECLARE_SINGLETON(ComponentManager)
public:
	ComponentManager() = default;
	~ComponentManager() = default;

	HRESULT Initialize(_uint _numLevels);
	HRESULT AddPrototype(_uint _levelIndex, const std::wstring& _prototypeTag, std::shared_ptr<Component> _prototype);
	std::shared_ptr<Component> CloneComponent(_uint _levelIndex, const std::wstring& _prototypeTag, void* pArg);
	void ClearLevelResources(_uint _levelIndex);

private:
	std::shared_ptr<Component> Find_Prototype(_uint _levelIndex, const std::wstring& _prototypeTag);

private:
	typedef std::vector<_umap<std::wstring, std::shared_ptr<Component>>>	PROTOTYPES;
	PROTOTYPES	mPrototypes;
};

END

#define COM		GET_SINGLE(Engine::ComponentManager)