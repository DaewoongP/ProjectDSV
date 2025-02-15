#pragma once
#include <iostream>
#include <cstring>

class DebugFunc
{
public:
	static void Text(const std::string& _text)
	{
#ifdef _DEBUG
		std::cout << _text << std::endl;
#endif // _DEBUG
	}
	static void Text(const std::string& _text, float _timeDelta, float _textTime = 1.f)
	{
#ifdef _DEBUG
		static float timeAcc = 0.f;
		timeAcc += _timeDelta;

		if (timeAcc >= _textTime)
		{
			std::cout << _text << std::endl;
			timeAcc = 0.f;
		}
#endif // _DEBUG
	}
};

class Utility
{
public:
	template <typename T>
	static void SafeDelete(T& pointer)
	{
		if (nullptr != pointer)
		{
			delete pointer;
			pointer = nullptr;
		}
	}

	template <typename T>
	static void SafeDeleteArray(T& pointer)
	{
		if (nullptr != pointer)
		{
			delete[] pointer;
			pointer = nullptr;
		}
	}

	class TagFinder
	{
	public:
		explicit TagFinder(const wchar_t* pTag) : m_pTargetTag(pTag) { }
		~TagFinder() = default;

	public:
		template<typename T>
		bool operator()(const T& pair)
		{
			return 0 == lstrcmpW(m_pTargetTag, pair.first);
		}

	private:
		const wchar_t* m_pTargetTag;
	};
};