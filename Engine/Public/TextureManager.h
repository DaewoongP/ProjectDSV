#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class TextureManager
{
	DECLARE_SINGLETON(TextureManager)
public:
	enum class TextureSaveType { STATIC, CLEAR, TYPEEND };

public:
	TextureManager() = default;
	~TextureManager() = default;

public:
	std::shared_ptr<class Texture> ReuseTexture(const std::wstring& _textureFilePath, _uint _numTextures = 1, TextureSaveType _saveType = TextureSaveType::CLEAR);
	void ClearLevelTextures();

private:
	_umap<std::wstring, std::shared_ptr<class Texture>>	mStaticTextures;
	_umap<std::wstring, std::shared_ptr<class Texture>>	mLevelTextures;
};

END

#define TEXTURE		GET_SINGLE(TextureManager)