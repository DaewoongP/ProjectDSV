#pragma once
#include "Composite.h"

BEGIN(Engine)
// 현재 레벨
class ENGINE_DLL Scene : public Composite
{
public:
	Scene() = delete;
	Scene(_uint nSceneIndex);
	virtual ~Scene() = default;

protected:
	_uint		m_nScene; // 내 레벨을 판단 가능

public:
	static Scene* Create(_uint nSceneIndex);
	virtual void Free() override;
};

END