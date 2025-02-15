#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL Component : public std::enable_shared_from_this<Component>
{
public:
	Component();
	Component(const Component& rhs);
	virtual ~Component() = default;

public:
	_bool IsCloned() { return mCloned; }

public:
	virtual HRESULT Initialize(void* _arg) { return S_OK; }
	virtual void Tick(_float _timeDelta) {}
	virtual void LateTick(_float _timeDelta) {}
	virtual HRESULT Render() { return S_OK; }

protected:
	ComPtr<ID3D11Device> GetDevice() { return mDevice; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return mDeviceContext; }

private:
	ComPtr<ID3D11Device>		mDevice;
	ComPtr<ID3D11DeviceContext> mDeviceContext;
	_bool						mCloned;

public:
	virtual std::shared_ptr<Component> Clone(void* _arg) PURE;
};

END