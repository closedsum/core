// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/MemoryResource/CsManager_MemoryResource_Fixed.h"

enum class ECsManagerTArraySize
{
	S_8,
	S_64,
	S_128,
	S_512,
	ECsManagerTArraySize_MAX
};

#define CS_MANAGER_TARRAY_POOL_SIZE 4

// Structs
#pragma region

#define CS_DECLARE_MANAGER_TARRAY(ValueType, Size, PoolSize) \
	struct FCsMemoryResource_TArray_##ValueType##_##Size : public TCsMemoryResource<TArray<ValueType>> \
	{ \
	}; \
	\
	struct FCsManager_TArray_##ValueType##_##Size : public TCsManager_MemoryResource_Fixed<TArray<bool>, FCsMemoryResource_TArray_##ValueType##_##Size, PoolSize> \
	{ \
	private: \
	\
		typedef TCsManager_MemoryResource_Fixed<TArray<bool>, FCsMemoryResource_TArray_##ValueType##_##Size, PoolSize> Super; \
	\
	public: \
	\
		FCsManager_TArray_##ValueType##_##Size() : \
			Super() \
		{ \
			const TArray<FCsMemoryResource_TArray_##ValueType##_##Size*>& Array = GetPool(); \
	\
			for (FCsMemoryResource_TArray_##ValueType##_##Size* M : Array) \
			{ \
				TArray<ValueType>* R = M->Get(); \
				R->Reserve(Size); \
			} \
		} \
	};

// FCsManager_TArray_bool_8
CS_DECLARE_MANAGER_TARRAY(bool, 8, CS_MANAGER_TARRAY_POOL_SIZE)
// FCsManager_TArray_bool_64
CS_DECLARE_MANAGER_TARRAY(bool, 64, CS_MANAGER_TARRAY_POOL_SIZE)

#pragma endregion Structs

class CSCORE_API FCsManager_TArray
{
public:

	FCsManager_TArray();

	virtual ~FCsManager_TArray();

// bool
#pragma region
protected:

	TArray<ICsManager_MemoryResource*> Manager_TArray_bool;

	FCsManager_TArray_bool_8 Manager_TArray_bool_8;
	FCsManager_TArray_bool_64 Manager_TArray_bool_64;

public:

	TArray<bool>& AllocateRef_TArray_bool(const ECsManagerTArraySize& Size);
	TArray<bool>& ForceAllocateRef_TArray_bool(const ECsManagerTArraySize& Size);

	void DeallocateAll_TArray_bool(const ECsManagerTArraySize& Size);

#pragma endregion bool
};