#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL Shader : public Component
{
public:
	Shader();
	virtual ~Shader() = default;

public:
	HRESULT Initialize(const std::wstring& _shaderFilePath, const D3D11_INPUT_ELEMENT_DESC* _elements, _uint _numElements);

public:
	HRESULT Begin(const std::string& _passName);

public:
	HRESULT BindShaderResource(const std::string& _constantName, ComPtr<ID3D11ShaderResourceView> _shaderResourceView);
	HRESULT BindShaderResources(const std::string& _constantName, ComPtr<ID3D11ShaderResourceView> _shaderResourceViewArray[], _uint _numTexture);
	HRESULT BindMatrix(const std::string& _constantName, const _float4x4* _matrix);
	HRESULT BindMatrices(const std::string& _constantName, const _float4x4* _matrix, _uint numMatrices);
	HRESULT BindRawValue(const std::string& _constantName, const void* _rawData, _uint _dataSize);

private:
	ComPtr<ID3DX11Effect>								mEffect;
	_uint												mNumPasses;
	_umap<std::string, ComPtr<ID3D11InputLayout>>		mInputLayouts;

private:
	ComPtr<ID3D11InputLayout> FindInputLayout(const std::string& _passName);
	ComPtr<ID3DX11EffectVariable> GetVariable(const std::string& _constantName) const;

public:
	static Shader* Create(const _tchar* _shaderFilePath, const D3D11_INPUT_ELEMENT_DESC* _elements, _uint _numElements);
	virtual void Free() override { __super::Free(); }
};

END