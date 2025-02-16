#pragma once
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL Component : public Base
{
public:
	Component();
	virtual ~Component() = default;

public:
	virtual void Update() {}
	virtual void Render() {}

public:
	virtual void Free() override {}
};

END