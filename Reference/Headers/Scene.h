#pragma once
#include "Composite.h"

BEGIN(Engine)
// 현재 레벨
class ENGINE_DLL Scene : public Composite
{
public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	virtual void Free() override;
};

END