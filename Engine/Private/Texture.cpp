#include "Texture.h"
#include "Shader.h"

USING(Engine)

Texture::Texture()
	: mNumTexture(0)
{
}

Texture::Texture(const Texture& rhs)
	: Component(rhs)
	, mNumTexture(rhs.mNumTexture)
	, mTextures(rhs.mTextures)
{
}

HRESULT Texture::InitializePrototype(const std::wstring& _textureFilePath, _uint _numTexture)
{
	mNumTexture = _numTexture;
	mTextures.reserve(_numTexture);

	_tchar textureFilePathCopy[MAX_PATH] = TEXT("");
	lstrcpy(textureFilePathCopy, _textureFilePath.c_str());

	for (_uint i = 0; i < mNumTexture; ++i)
	{
		ComPtr<ID3D11ShaderResourceView> shaderResourceView;
		_tchar inputPath[MAX_PATH] = TEXT("");
		wsprintf(inputPath, textureFilePathCopy, i);

		_tchar	ext[MAX_PATH] = TEXT("");
		_wsplitpath_s(inputPath, nullptr, 0, nullptr, 0, nullptr, 0, ext, 256);

		HRESULT	hr = 0;

		if (!lstrcmp(ext, TEXT(".dds")))
		{
			hr = CreateDDSTextureFromFile(GetDevice().Get(), inputPath, nullptr, &shaderResourceView);
		}
		else if (!lstrcmp(ext, TEXT(".tga")))
		{
			MSG_BOX("Ext .tga not supported");
			return E_FAIL;
		}
		else
		{
			hr = CreateWICTextureFromFile(GetDevice().Get(), inputPath, nullptr, &shaderResourceView);
		}

		FAILED_CHECK_RETURN_MSG(hr, E_FAIL, TEXT("Failed"));

		mTextures.emplace_back(shaderResourceView);
		mTexturePathes.emplace_back(inputPath);
	}

	return S_OK;
}

HRESULT Texture::BindShaderResource(std::shared_ptr<class Shader> _shader, const std::string& _constantName, _uint _textureIndex)
{
	return _shader->BindShaderResource(_constantName, mTextures[_textureIndex]);
}

HRESULT Texture::BindShaderResources(std::shared_ptr<class Shader> _shader, const std::string& _constantName)
{
	return _shader->BindShaderResources(_constantName, mTextures.data(), mNumTexture);
}

std::shared_ptr<Texture> Texture::Create(const std::wstring& _textureFilePath, _uint _numTexture, TextureManager::TextureSaveType _saveType)
{
	auto instance = TEXTURE->ReuseTexture(_textureFilePath, _numTexture, _saveType);
	return instance;
}

std::shared_ptr<Texture> Texture::CreateOrigin(const std::wstring& _textureFilePath, _uint _numTexture)
{
	auto instance = std::make_shared<Texture>();
	FAILED_CHECK_RETURN_MSG(instance->InitializePrototype(_textureFilePath, _numTexture), nullptr, TEXT("Failed"));
	return instance;
}

std::shared_ptr<Component> Texture::Clone(void* _arg)
{
	auto instance = std::make_shared<Texture>(*this);
	FAILED_CHECK_RETURN_MSG(instance->Initialize(_arg), nullptr, TEXT("Failed"));
	return instance;
}