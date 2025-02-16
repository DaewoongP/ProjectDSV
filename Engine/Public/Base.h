#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL Base
{
protected:
	Base();
	virtual ~Base() = default;

public:
	_uint AddRef();
	_uint Release();

protected:
	_uint			m_nRefCount;

public:
	virtual void Free() PURE;
};

END
