#pragma once
#include "Composite.h"

BEGIN(Engine)
// ���� ����
class ENGINE_DLL Scene : public Composite
{
public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	virtual void Free() override;
};

END