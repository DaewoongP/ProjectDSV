#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL RectBuffer : public VIBuffer
{
public:
	RectBuffer();
	virtual ~RectBuffer() = default;

public:
	void Initialize();

public:
	static RectBuffer* Create();
	virtual void Free() override;
};

END