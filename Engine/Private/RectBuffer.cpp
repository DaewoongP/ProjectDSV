#include "RectBuffer.h"

USING(Engine)

RectBuffer::RectBuffer()
	: VIBuffer()
{
}

RectBuffer::RectBuffer(const RectBuffer& rhs)
	: VIBuffer(rhs)
{
}

HRESULT RectBuffer::InitializePrototype()
{
	mNumVertexBuffers = { 1 };
	mVertexStride = { sizeof(VTXPOSTEX) };
	mNumVertices = { 4 };
	mIndexStride = { sizeof(_ushort) };
	mNumIndices = { 6 };
	mFormat = DXGI_FORMAT_R16_UINT;
	mTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

#pragma region VERTEX_BUFFER
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.ByteWidth = mVertexStride * mNumVertices;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.StructureByteStride = mVertexStride;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	VTXPOSTEX* pVertices = new VTXPOSTEX[mNumVertices];
	ZeroMemory(pVertices, sizeof(VTXPOSTEX) * mNumVertices);

	pVertices[0].Position = _float3(-0.5f, 0.5f, 0.f);
	pVertices[0].TexCoord = _float2(0.f, 0.f);

	pVertices[1].Position = _float3(0.5f, 0.5f, 0.f);
	pVertices[1].TexCoord = _float2(1.f, 0.f);

	pVertices[2].Position = _float3(0.5f, -0.5f, 0.f);
	pVertices[2].TexCoord = _float2(1.f, 1.f);

	pVertices[3].Position = _float3(-0.5f, -0.5f, 0.f);
	pVertices[3].TexCoord = _float2(0.f, 1.f);

	D3D11_SUBRESOURCE_DATA subResourceData;
	ZeroMemory(&subResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	subResourceData.pSysMem = pVertices;

	FAILED_RETURN(__super::CreateBuffer(mVertexBuffer, bufferDesc, subResourceData), E_FAIL);

	Utility::SafeDeleteArray(pVertices);

#pragma endregion

#pragma region INDEX_BUFFER
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	bufferDesc.ByteWidth = mIndexStride * mNumIndices;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	_ushort* pIndices = new _ushort[mNumIndices];
	ZeroMemory(pIndices, sizeof(_ushort) * mNumIndices);

	pIndices[0] = 0;
	pIndices[1] = 1;
	pIndices[2] = 2;

	pIndices[3] = 0;
	pIndices[4] = 2;
	pIndices[5] = 3;

	ZeroMemory(&subResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	subResourceData.pSysMem = pIndices;

	FAILED_RETURN(__super::CreateBuffer(mIndexBuffer, bufferDesc, subResourceData), E_FAIL);
	Utility::SafeDeleteArray(pIndices);
#pragma endregion

	return S_OK;
}

std::shared_ptr<RectBuffer> RectBuffer::Create()
{
	auto instance = std::make_shared<RectBuffer>();
	FAILED_CHECK_RETURN_MSG(instance->InitializePrototype(), nullptr, TEXT("Failed"));
	return instance;
}

std::shared_ptr<Component> RectBuffer::Clone(void* _arg)
{
	auto instance = std::make_shared<RectBuffer>(*this);
	FAILED_CHECK_RETURN_MSG(instance->Initialize(_arg), nullptr, TEXT("Failed"));
	return instance;
}
