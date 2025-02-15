#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL Level abstract
{
public:
	Level() = default;
	virtual ~Level() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float _timeDelta);
	virtual HRESULT Render();
};

END