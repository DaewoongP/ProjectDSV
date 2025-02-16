#include "TextureManager.h"
#include "Texture.h"

USING(Engine)

IMPLEMENT_SINGLETON(TextureManager)

Texture* TextureManager::ReuseTexture(const std::wstring& _textureFilePath, _uint _numTextures, TextureSaveType _saveType)
{
	// find in static
	auto iter = mStaticTextures.find(_textureFilePath);
	if (mStaticTextures.end() != iter)
		return iter->second;

	// find in level
	iter = mSceneTextures.find(_textureFilePath);
	if (mSceneTextures.end() != iter)
	{
		if (TextureSaveType::STATIC == _saveType)
			mStaticTextures.emplace(*iter);

		return iter->second;
	}

	Texture* texture = Texture::CreateOrigin(_textureFilePath, _numTextures);
	
	switch (_saveType)
	{
	case Engine::TextureManager::TextureSaveType::STATIC:
		mStaticTextures.emplace(_textureFilePath, texture);
		break;
	case Engine::TextureManager::TextureSaveType::CLEAR:
		mSceneTextures.emplace(_textureFilePath, texture);
		break;
	default:
		__debugbreak();
		MSG_BOX("wrong Type");
		break;
	}

	Utility::SafeAddRef(texture);

	return texture;
}

void TextureManager::ClearLevelTextures()
{
	for (auto& texture : mSceneTextures)
		Utility::SafeRelease(texture.second);

	mSceneTextures.clear();
}
