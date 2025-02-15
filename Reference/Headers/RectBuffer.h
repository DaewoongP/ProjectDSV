#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL RectBuffer : public VIBuffer
{
public:
	RectBuffer();
	RectBuffer(const RectBuffer& rhs);
	virtual ~RectBuffer() = default;

public:
	HRESULT InitializePrototype();

public:
	static std::shared_ptr<RectBuffer> Create();
	std::shared_ptr<Component> Clone(void* _arg) override;
};

END