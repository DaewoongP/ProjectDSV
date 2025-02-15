#include "Shader.h"

USING(Engine)

Shader::Shader()
	: Component()
	, mEffect(nullptr)
	, mNumPasses(0)
{
}

Shader::Shader(const Shader& rhs)
	: Component(rhs)
	, mEffect(rhs.mEffect)
	, mNumPasses(rhs.mNumPasses)
	, mInputLayouts(rhs.mInputLayouts)
{
}

HRESULT Shader::InitializePrototype(const std::wstring& _shaderFilePath, const D3D11_INPUT_ELEMENT_DESC* _elements, _uint _numElements)
{
	_uint		hlslFlag = 0;
#ifdef _DEBUG
	hlslFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	hlslFlag = D3DCOMPILE_OPTIMIZATION_LEVEL1;
#endif
	FAILED_CHECK_RETURN_MSG(D3DX11CompileEffectFromFile(_shaderFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, hlslFlag, 0, GetDevice().Get(), mEffect.GetAddressOf(), nullptr), E_FAIL,
		TEXT("Failed Create Shader Effect File"));

	ComPtr<ID3DX11EffectTechnique> technique = mEffect->GetTechniqueByIndex(0);
	NULL_CHECK_RETURN_MSG(technique, E_FAIL, TEXT("Failed Get Shader technique"));
	
	D3DX11_TECHNIQUE_DESC	techniqueDesc;
	ZeroMemory(&techniqueDesc, sizeof(D3DX11_TECHNIQUE_DESC));

	FAILED_CHECK_RETURN_MSG(technique->GetDesc(&techniqueDesc), E_FAIL, TEXT("Failed Get Shader TECHNIQUEDESC"));

	mNumPasses = techniqueDesc.Passes;

	for (_uint i = 0; i < mNumPasses; ++i)
	{
		ComPtr<ID3D11InputLayout> inputLayout;

		ComPtr<ID3DX11EffectPass> _pass = technique->GetPassByIndex(i);
		NULL_CHECK_RETURN_MSG(_pass, E_FAIL, TEXT("Failed Get pass"));

		D3DX11_PASS_DESC	passDesc;
		ZeroMemory(&passDesc, sizeof(D3DX11_PASS_DESC));

		FAILED_CHECK_RETURN_MSG(_pass->GetDesc(&passDesc), E_FAIL, TEXT("Failed Get PASSDESC"));

		FAILED_CHECK_RETURN_MSG(GetDevice()->CreateInputLayout(_elements, _numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, inputLayout.GetAddressOf()), E_FAIL, 
			TEXT("Failed CreateInputLayout"));

		mInputLayouts.emplace(passDesc.Name, inputLayout);
	}

	return S_OK;
}

HRESULT Shader::Begin(const std::string& _passName)
{
	ComPtr<ID3DX11EffectTechnique> technique = mEffect->GetTechniqueByIndex(0);
	NULL_RETURN(technique, E_FAIL);

	ComPtr<ID3DX11EffectPass> _pass = technique->GetPassByName(_passName.c_str());
	NULL_RETURN(_pass, E_FAIL);

	FAILED_RETURN(_pass->Apply(0, GetDeviceContext().Get()), E_FAIL);

	ComPtr<ID3D11InputLayout> inputLayout = FindInputLayout(_passName);
	NULL_RETURN(inputLayout, E_FAIL);

	GetDeviceContext()->IASetInputLayout(inputLayout.Get());

	return S_OK;
}

HRESULT Shader::BindShaderResource(const std::string& _constantName, ComPtr<ID3D11ShaderResourceView> _shaderResourceView)
{
	return GetVariable(_constantName)->AsShaderResource()->SetResource(_shaderResourceView.Get());
}

HRESULT Shader::BindShaderResources(const std::string& _constantName, ComPtr<ID3D11ShaderResourceView> _shaderResourceViewArray[], _uint _numTexture)
{
	std::vector<ID3D11ShaderResourceView*> shaderResourceViewArray(_numTexture);
	for (_uint i = 0; i < _numTexture; ++i)
	{
		shaderResourceViewArray[i] = _shaderResourceViewArray[i].Get();
	}

	return GetVariable(_constantName)->AsShaderResource()->SetResourceArray(shaderResourceViewArray.data(), 0, _numTexture);
}

HRESULT Shader::BindMatrix(const std::string& _constantName, const _float4x4* _matrix)
{
	return GetVariable(_constantName)->AsMatrix()->SetMatrix((_float*)_matrix);
}

HRESULT Shader::BindMatrices(const std::string& _constantName, const _float4x4* _matrix, _uint numMatrices)
{
	return GetVariable(_constantName)->AsMatrix()->SetMatrixArray((_float*)_matrix, 0, numMatrices);
}

HRESULT Shader::BindRawValue(const std::string& _constantName, const void* _rawData, _uint _dataSize)
{
	return GetVariable(_constantName)->SetRawValue(_rawData, 0, _dataSize);
}

ComPtr<ID3D11InputLayout> Shader::FindInputLayout(const std::string& _passName)
{
	auto iter = mInputLayouts.find(_passName);

	if (mInputLayouts.end() == iter)
		return nullptr;

	return iter->second;
}

ComPtr<ID3DX11EffectVariable> Shader::GetVariable(const std::string& _constantName) const
{
	return mEffect->GetVariableByName(_constantName.c_str());
}

std::shared_ptr<Shader> Shader::Create(const _tchar* _shaderFilePath, const D3D11_INPUT_ELEMENT_DESC* _elements, _uint _numElements)
{
	auto instance = std::make_shared<Shader>();
	FAILED_CHECK_RETURN_MSG(instance->InitializePrototype(_shaderFilePath, _elements, _numElements), nullptr, TEXT("Failed"));
	return instance;
}

std::shared_ptr<Component> Shader::Clone(void* _arg)
{
	auto instance = std::make_shared<Shader>(*this);
	FAILED_CHECK_RETURN_MSG(instance->Initialize(_arg), nullptr, TEXT("Failed"));
	return instance;
}