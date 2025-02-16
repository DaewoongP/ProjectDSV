#include "VIBuffer.h"
#include "GameInstance.h"

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

void VIBuffer::Render()
{
    ComPtr<ID3D11DeviceContext> deviceContext = GAME->GetDeviceContext();

    ID3D11Buffer* buffers[] = { mVertexBuffer.Get() };

    _uint   strides[] = { mVertexStride };

    _uint	offset[] = { 0 };

    deviceContext->IASetVertexBuffers(0, mNumVertexBuffers, buffers, strides, offset);
    deviceContext->IASetIndexBuffer(mIndexBuffer.Get(), mFormat, 0);
    deviceContext->IASetPrimitiveTopology(mTopology);
    deviceContext->DrawIndexed(mNumIndices, 0, 0);
}

HRESULT VIBuffer::CreateBuffer(_Inout_ ComPtr<ID3D11Buffer>& _buffer, D3D11_BUFFER_DESC _bufferDesc, D3D11_SUBRESOURCE_DATA _subResourceData)
{
    return GAME->GetDevice()->CreateBuffer(&_bufferDesc, &_subResourceData, _buffer.GetAddressOf());
}
