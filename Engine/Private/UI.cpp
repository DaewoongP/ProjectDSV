#include "UI.h"
#include "Shader.h"
#include "Texture.h"
#include "RectBuffer.h"
#include "GameInstance.h"

USING(Engine)

UI::UI()
	: Composite()
	, m_pShader(nullptr), m_pTexture(nullptr), m_pRectBuffer(nullptr)
	, m_vPos({0.f, 0.f}), m_fWidth(0.f), m_fHeight(0.f), m_bLClicked(false), m_bRClicked(false)
{
}

void UI::Initialize(const std::wstring& wstrTexturePath, _float2 vPos, _float fWidth, _float fHeight)
{
	m_vPos = vPos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	m_pRectBuffer = RectBuffer::Create();
	m_pShader = Shader::Create(TEXT("../Bin/ShaderFiles/VtxtexShader.hlsl"), Engine::VTXPOSTEX_DECL::Elements, Engine::VTXPOSTEX_DECL::NumElements);
	m_pTexture = Texture::Create(wstrTexturePath);

	AddComponent(TEXT("RectBuffer"), m_pRectBuffer);
	Utility::SafeAddRef(m_pRectBuffer);
	AddComponent(TEXT("Shader"), m_pShader);
	Utility::SafeAddRef(m_pShader);
	AddComponent(TEXT("Texture"), m_pTexture);
	Utility::SafeAddRef(m_pTexture);
}

void UI::Update()
{
	_int2 vMousePos = GAME->GetMousePos();

	if (IsOnMe(vMousePos.x, vMousePos.y))
	{
		if (GAME->GetDIMouseState(InputDevice::DIMK_LBUTTON, InputDevice::KEY_DOWN))
		{
			LButtonDown(vMousePos.x, vMousePos.y);
			m_bLClicked = true;
		}
		else if (GAME->GetDIMouseState(InputDevice::DIMK_LBUTTON, InputDevice::KEY_UP) &&
			m_bLClicked)
		{
			LButtonUp(vMousePos.x, vMousePos.y);
			m_bLClicked = false;
		}
		else if (GAME->GetDIMouseState(InputDevice::DIMK_RBUTTON, InputDevice::KEY_DOWN) &&
			IsOnMe(vMousePos.x, vMousePos.y))
		{
			RButtonDown(vMousePos.x, vMousePos.y);
			m_bRClicked = true;
		}
		else if (GAME->GetDIMouseState(InputDevice::DIMK_RBUTTON, InputDevice::KEY_UP) &&
			m_bRClicked)
		{
			RButtonUp(vMousePos.x, vMousePos.y);
			m_bRClicked = false;
		}
	}
	else
	{
		if (m_bLClicked)
		{
			LButtonUp(vMousePos.x, vMousePos.y);
			m_bLClicked = false;
		}
		if (m_bRClicked)
		{
			RButtonUp(vMousePos.x, vMousePos.y);
			m_bRClicked = false;
		}
	}
}

void UI::Render()
{
	_float4x4 identityMatrix, viewMatrix, projMatrix;

	XMStoreFloat4x4(&identityMatrix, XMMatrixScaling(m_fWidth, m_fHeight, 1.f) * XMMatrixTranslation(m_vPos.x - GAME->GetViewPort().Width * 0.5f, -m_vPos.y + GAME->GetViewPort().Height * 0.5f, 0.f));
	m_pShader->BindMatrix("gWorldMatrix", &identityMatrix);

	XMStoreFloat4x4(&viewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&projMatrix, XMMatrixOrthographicLH(GAME->GetViewPort().Width, GAME->GetViewPort().Height, 0.f, 1.f));

	m_pShader->BindMatrix("gViewMatrix", &viewMatrix);
	m_pShader->BindMatrix("gProjMatrix", &projMatrix);

	m_pTexture->BindShaderResources(m_pShader, "gTexture");

	m_pShader->Begin("Test");

	m_pRectBuffer->Render();
}

void UI::ChangeTexture(Texture* pTexture)
{
	Utility::SafeRelease(m_pTexture);
	Utility::SafeAddRef(pTexture);
	m_pTexture = pTexture;
}

bool UI::IsOnMe(_int x, _int y)
{
	_float2 vLT{ m_vPos.x - m_fWidth * 0.5f, m_vPos.y - m_fHeight * 0.5f };
	_float2 vRB{ m_vPos.x + m_fWidth * 0.5f, m_vPos.y + m_fHeight * 0.5f };

	if (vLT.x <= x &&
		vLT.y <= y &&
		vRB.x >= x &&
		vRB.y >= y)
	{
		return true;
	}

	return false;
}

void UI::LButtonDown(_int x, _int y)
{
}

void UI::RButtonDown(_int x, _int y)
{
}

void UI::LButtonUp(_int x, _int y)
{
}

void UI::RButtonUp(_int x, _int y)
{
}

UI* UI::Create(const std::wstring& wstrTexturePath, _float2 vPos, _float fWidth, _float fHeight)
{
	auto instance = new UI();
	instance->Initialize(wstrTexturePath, vPos, fWidth, fHeight);
	return instance;
}

void UI::Free()
{
	Utility::SafeRelease(m_pShader);
	Utility::SafeRelease(m_pTexture);
	Utility::SafeRelease(m_pRectBuffer);

	__super::Free();
}
