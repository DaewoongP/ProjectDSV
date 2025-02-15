#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

template<typename T>
class Factory
{
private:
	Factory() = default;
	~Factory() = default;

public:
	//static std::shared_ptr<T> CreateShared()
	//{
	//	auto instance = std::make_shared<T>();
	//	FAILED_CHECK_RETURN_MSG(instance->InitializePrototype(), nullptr, TEXT("Factory::CreateShared\n Failed"));
	//	return instance;
	//}

	//template<typename ...Args>
	//static std::shared_ptr<T> CreateShared(Args&&... args)
	//{
	//	auto instance = std::make_shared<T>();
	//	FAILED_CHECK_RETURN_MSG(instance->InitializePrototype(std::forward<Args>(args)...), nullptr, TEXT("Factory::CreateShared\n Failed"));
	//	return instance;
	//}

	//static std::unique_ptr<T> CreateUnique()
	//{
	//	auto instance = std::make_unique<T>();
	//	FAILED_CHECK_RETURN_MSG(instance->InitializePrototype(), nullptr, TEXT("Factory::CreateUnique\n Failed"));
	//	return instance;
	//}

	//template<typename ...Args>
	//static std::unique_ptr<T> CreateUnique(Args&&... args)
	//{
	//	auto instance = std::make_unique<T>();
	//	FAILED_CHECK_RETURN_MSG(instance->InitializePrototype(std::forward<Args>(args)...), nullptr, TEXT("Factory::CreateUnique\n Failed"));
	//	return instance;
	//}

	//// Clone
	//static std::shared_ptr<T> CloneShared(const std::shared_ptr<T>& _origin)
	//{
	//	auto instance = std::make_shared<T>(_origin);
	//	FAILED_CHECK_RETURN_MSG(instance->Initialize(), nullptr, TEXT("Factory::CloneShared\n Failed"));
	//	return instance;
	//}

	//template<typename ...Args>
	//static std::shared_ptr<T> CloneShared(const std::shared_ptr<T>& _origin, Args&&... args)
	//{
	//	auto instance = std::make_shared<T>(_origin);
	//	FAILED_CHECK_RETURN_MSG(instance->Initialize(), nullptr, TEXT("Factory::CloneShared\n Failed"));
	//	return instance;
	//}

	//static std::unique_ptr<T> CloneUnique(const std::unique_ptr<T>& _origin)
	//{
	//	auto instance = std::make_unique<T>(_origin);
	//	FAILED_CHECK_RETURN_MSG(instance->Initialize(), nullptr, TEXT("Factory::CreateUnique\n Failed"));
	//	return instance;
	//}

	//template<typename ...Args>
	//static std::unique_ptr<T> CloneUnique(const std::unique_ptr<T>& _origin, Args&&... args)
	//{
	//	auto instance = std::make_unique<T>(_origin);
	//	FAILED_CHECK_RETURN_MSG(instance->Initialize(std::forward<Args>(args)...), nullptr, TEXT("Factory::CreateUnique\n Failed"));
	//	return instance;
	//}
};

END