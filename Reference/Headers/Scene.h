#pragma once
#include "Composite.h"

BEGIN(Engine)
// ���� ����
class ENGINE_DLL Scene : public Composite
{
public:
	Scene() = delete;
	Scene(_uint nSceneIndex);
	virtual ~Scene() = default;

protected:
	_uint		m_nScene; // �� ������ �Ǵ� ����

public:
	static Scene* Create(_uint nSceneIndex);
	virtual void Free() override;
};

END