#include "Base.h"

USING(Engine)

Base::Base()
	: m_nRefCount(1)
{
}

_uint Base::AddRef()
{
	return ++m_nRefCount;
}

_uint Base::Release()
{
	if (0 == --m_nRefCount)
	{
		Free();

		delete this;

		return 0;
	}
	else
		return m_nRefCount;
}