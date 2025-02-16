#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class Texture;
class TextureManager
{
	DECLARE_SINGLETON(TextureManager)
public:
	enum class TextureSaveType { STATIC, CLEAR, TYPEEND };

public:
	TextureManager() = default;
	~TextureManager() = default;

public:
	Texture* ReuseTexture(const std::wstring& _textureFilePath, _uint _numTextures = 1, TextureSaveType _saveType = TextureSaveType::CLEAR);
	void ClearLevelTextures();

private:
	_umap<std::wstring, Texture*>	mStaticTextures;
	_umap<std::wstring, Texture*>	mSceneTextures;
};

END

#define TEXTURE		GET_SINGLE(TextureManager)