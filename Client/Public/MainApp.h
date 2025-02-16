#pragma once
#include "GameInstance.h"
#include "Client_Defines.h"

BEGIN(Client)

class MainApp
{
public:
	MainApp() = default;
	~MainApp() = default;

public:
	HRESULT Initialize();
	void Update(_float fTimeDelta);
	void Render();

public:
	static MainApp* Create();
};

END