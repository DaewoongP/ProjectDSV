#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL VIBuffer : public Component
{
public:
	VIBuffer();
	VIBuffer(const VIBuffer& rhs);
	virtual ~VIBuffer() = default;

public:
	virtual HRESULT Render() override;

protected:
	HRESULT CreateBuffer(_Inout_ ComPtr<ID3D11Buffer>& _buffer, D3D11_BUFFER_DESC _bufferDesc, D3D11_SUBRESOURCE_DATA _subResourceData);

protected:
	ComPtr<ID3D11Buffer>		mVertexBuffer;
	ComPtr<ID3D11Buffer>		mIndexBuffer;

protected:
	_uint						mNumVertices;
	_uint						mNumIndices;
	_uint						mVertexStride;
	_uint						mIndexStride;
	_uint						mNumVertexBuffers;
	DXGI_FORMAT					mFormat;
	D3D11_PRIMITIVE_TOPOLOGY	mTopology;
};

END