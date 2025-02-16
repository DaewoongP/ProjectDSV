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
	void SetSceneIndex(_uint nSceneIndex) { m_nSceneIndex = nSceneIndex; }

protected:
	_uint		m_nSceneIndex; // 내 레벨을 판단 가능

public:
	virtual void Free() override;
};

END