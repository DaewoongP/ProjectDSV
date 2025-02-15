#include "Component.h"
#include "GameInstance.h"

USING(Engine)

Component::Component()
	: mDevice(GAME->GetDevice())
	, mDeviceContext(GAME->GetDeviceContext())
	, mCloned(false)
{
}

Component::Component(const Component& rhs)
	: mDevice(rhs.mDevice)
	, mDeviceContext(rhs.mDeviceContext)
	, mCloned(true)
{
	
}
