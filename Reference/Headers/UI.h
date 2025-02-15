#pragma once
#include "Shader.h"
#include "Texture.h"
#include "RectBuffer.h"

BEGIN(Engine)

class ENGINE_DLL UI : public Component
{
public:
	UI();
	UI(const UI& rhs);
	virtual ~UI() = default;

public:
	HRESULT Initialize();
	void Tick(_float _timeDelta);
	void LateTick(_float _timeDelta);
	HRESULT Render();

public:
	HRESULT InitializePrototype();

private:
	std::shared_ptr<Engine::RectBuffer> mRectBuffer;
	std::shared_ptr<Engine::Shader>		mShader;
	std::shared_ptr<Engine::Texture>	mTexture;

private:
	_float2		mPos; // LT
	_float		mWidth;
	_float		mHeight;
	
public:
	static std::shared_ptr<UI> Create();
	virtual std::shared_ptr<Component> Clone(void* _arg);
};

END