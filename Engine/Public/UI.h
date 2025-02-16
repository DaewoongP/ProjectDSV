#pragma once
#include "Shader.h"
#include "Texture.h"
#include "RectBuffer.h"

BEGIN(Engine)

class ENGINE_DLL UI : public Component
{
public: // constructor
	UI();
	virtual ~UI() = default;

public: // public func
	void Initialize();

public: // virtual func
	virtual void Update() override;
	virtual void Render() override;

private: // component
	Engine::RectBuffer*		m_pRectBuffer;
	Engine::Shader*			m_pShader;
	Engine::Texture*		m_pTexture;

private: // data
	_float2		m_vPos; // LT
	_float		m_fWidth;
	_float		m_fHeight;
	
public: // handling func
	static UI* Create();
	virtual void Free() override;
};

END