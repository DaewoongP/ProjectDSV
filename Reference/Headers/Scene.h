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
	void SetSceneIndex(_uint nSceneIndex) { m_nSceneIndex = nSceneIndex; }

protected:
	_uint		m_nSceneIndex; // �� ������ �Ǵ� ����

public:
	virtual void Free() override;
};

END