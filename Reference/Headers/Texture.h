#pragma once
#include "Component.h"
#include "TextureManager.h"

BEGIN(Engine)

class ENGINE_DLL Texture : public Component
{
public:
	Texture();
	Texture(const Texture& rhs);
	virtual ~Texture() = default;

public:
	virtual HRESULT InitializePrototype(const std::wstring& _textureFilePath, _uint _numTexture);

public:
	HRESULT BindShaderResource(std::shared_ptr<class Shader> _shader, const std::string& _constantName, _uint _textureIndex = 0);
	HRESULT BindShaderResources(std::shared_ptr<class Shader> _shader, const std::string& _constantName);

private:
	_uint											mNumTexture;
	std::vector<ComPtr<ID3D11ShaderResourceView>>	mTextures;
	std::vector<std::wstring>						mTexturePathes;

public:
	static std::shared_ptr<Texture> Create(const std::wstring& _textureFilePath, _uint _numTexture = 1, TextureManager::TextureSaveType _saveType = TextureManager::TextureSaveType::CLEAR);
	static std::shared_ptr<Texture> CreateOrigin(const std::wstring& _textureFilePath, _uint _numTexture = 1);
	virtual std::shared_ptr<Component> Clone(void* _arg) override;
};

END