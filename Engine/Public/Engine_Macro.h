
#pragma once
#include <cstring>

///////////////////////// My Macros //////////////////////////////////
#define			PURE							= 0
#define			MAX_DIK							256
#define			CharToWChar(_pChar, _pWchar)	MultiByteToWideChar(CP_ACP, 0, _pChar, MAX_PATH, _pWchar, MAX_PATH);
#define         WCharToChar(_pWchar, _pChar)    WideCharToMultiByte(CP_ACP, 0, _pWchar, -1, _pChar, MAX_PATH, nullptr, nullptr);
#define D3DCOLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
///////////////////////// default Macros /////////////////////////////


#ifndef			MSG_BOX
#define			MSG_BOX(_message)			MessageBox(nullptr, TEXT(_message), L"System Message", MB_OK)
#endif

#define			BEGIN(NAMESPACE)		namespace NAMESPACE {
#define			END						}

#define			USING(NAMESPACE)	using namespace NAMESPACE;


#ifdef	ENGINE_EXPORTS
#define ENGINE_DLL		_declspec(dllexport)
#else
#define ENGINE_DLL		_declspec(dllimport)
#endif

#define DISPLAY_ERROR(_message)                                                                             \
        const char* filename = strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__;            \
        filename = strrchr(filename, '/') ? strrchr(filename, '/') + 1 : filename;                          \
        wchar_t fullMessage[512];                                                                           \
        swprintf(fullMessage, sizeof(fullMessage)/sizeof(wchar_t), L"%S\r\n%s", __FUNCTION__, _message);    \
        wchar_t title[256];                                                                                 \
        swprintf(title, sizeof(title)/sizeof(wchar_t), L"%S::%d", filename, __LINE__);                      \
        MessageBoxW(nullptr, fullMessage, title, MB_OK);                                                    \

#define NULL_RETURN(_ptr, _return)						\
	if(  _ptr == 0 )									\
	{													\
		return _return;									\
	}													\

#define NULL_CHECK(_ptr)								\
    if ( _ptr == 0)										\
    {													\
        __debugbreak();									\
        return E_FAIL;									\
    }

#define NULL_CHECK_RETURN(_ptr, _return)				\
    if ( _ptr == 0)							            \
    {													\
        __debugbreak();									\
        return _return;									\
    }


#define NULL_CHECK_MSG(_ptr, _message)					\
    if ( _ptr == 0)							            \
    {													\
        DISPLAY_ERROR(_message);						\
		__debugbreak();									\
        return E_FAIL;									\
    }

#define NULL_CHECK_RETURN_MSG(_ptr, _return, _message)  \
    if ( _ptr == 0)							            \
    {													\
        DISPLAY_ERROR(_message);						\
		__debugbreak();									\
        return _return;									\
	} 


#define FAILED_RETURN(_hr, _return)						\
	if( ((HRESULT)(_hr)) < 0 )							\
	{													\
		return _return;									\
	}													\

#define FAILED_CHECK(_hr)								\
    if (((HRESULT)(_hr)) < 0)							\
    {													\
        __debugbreak();									\
        return E_FAIL;									\
    }

#define FAILED_CHECK_RETURN(_hr, _return)				\
    if (((HRESULT)(_hr)) < 0)							\
    {													\
        __debugbreak();									\
        return _return;									\
    }

#define FAILED_CHECK_MSG(_hr, _message)					\
    if (((HRESULT)(_hr)) < 0)							\
    {													\
        DISPLAY_ERROR(_message);						\
		__debugbreak();									\
        return E_FAIL;									\
    }


#define FAILED_CHECK_RETURN_MSG(_hr, _return, _message) \
    if (((HRESULT)(_hr)) < 0)							\
    {													\
        DISPLAY_ERROR(_message);						\
		__debugbreak();									\
        return _return;									\
	}    



#define NO_COPY(CLASSNAME)										\
		private:												\
		CLASSNAME(const CLASSNAME&) = delete;					\
		CLASSNAME& operator = (const CLASSNAME&) = delete;		

#define DECLARE_SINGLETON(CLASSNAME)							\
		NO_COPY(CLASSNAME)										\
		private:												\
		static CLASSNAME*	mInstance;							\
		public:													\
		static CLASSNAME*	GetInstance( void );				\
		static void DestroyInstance( void );					\

#define IMPLEMENT_SINGLETON(CLASSNAME)							\
		CLASSNAME*	CLASSNAME::mInstance = nullptr;				\
		CLASSNAME*	CLASSNAME::GetInstance( void )	{			\
			if(nullptr == mInstance) {							\
				mInstance = new CLASSNAME;						\
			}													\
			return mInstance;									\
		}														\
		void CLASSNAME::DestroyInstance( void ) {				\
			if(nullptr != mInstance)							\
			{													\
				delete mInstance;								\
			}													\
		}														\

#define GET_SINGLE(CLASSNAME)    CLASSNAME::GetInstance()
