#include "VIBuffer.h"

USING(Engine)

VIBuffer::VIBuffer()
    : Component()
    , mVertexBuffer(nullptr)
    , mIndexBuffer(nullptr)
    , mNumVertices(0)
    , mNumIndices(0)
    , mVertexStride(0)
    , mIndexStride(0)
    , mNumVertexBuffers(0)
    , mFormat(DXGI_FORMAT())
    , mTopology(D3D11_PRIMITIVE_TOPOLOGY())
{
}

VIBuffer::VIBuffer(const VIBuffer& rhs)
    : Component(rhs)
    , mVertexBuffer(rhs.mVertexBuffer)
    , mIndexBuffer(rhs.mIndexBuffer)
    , mNumVertices(rhs.mNumVertices)
    , mNumIndices(rhs.mNumIndices)
    , mVertexStride(rhs.mVertexStride)
    , mIndexStride(rhs.mIndexStride)
    , mNumVertexBuffers(rhs.mNumVertexBuffers)
    , mFormat(rhs.mFormat)
    , mTopology(rhs.mTopology)
{
}

HRESULT VIBuffer::Render()
{
    ComPtr<ID3D11DeviceContext> deviceContext = GetDeviceContext();

    ID3D11Buffer* buffers[] = { mVertexBuffer.Get() };

    _uint   strides[] = { mVertexStride };

    _uint	offset[] = { 0 };

    deviceContext->IASetVertexBuffers(0, mNumVertexBuffers, buffers, strides, offset);
    deviceContext->IASetIndexBuffer(mIndexBuffer.Get(), mFormat, 0);
    deviceContext->IASetPrimitiveTopology(mTopology);
    deviceContext->DrawIndexed(mNumIndices, 0, 0);

    return S_OK;
}

HRESULT VIBuffer::CreateBuffer(_Inout_ ComPtr<ID3D11Buffer>& _buffer, D3D11_BUFFER_DESC _bufferDesc, D3D11_SUBRESOURCE_DATA _subResourceData)
{
    return GetDevice()->CreateBuffer(&_bufferDesc, &_subResourceData, _buffer.GetAddressOf());
}
