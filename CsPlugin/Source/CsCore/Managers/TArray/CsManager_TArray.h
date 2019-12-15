// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/MemoryResource/CsManager_MemoryResource_Fixed.h"

#define CS_MANAGER_TARRAY_POOL_SIZE 4

// Structs
#pragma region

	// Routine

struct CSCORE_API FCsMemoryResource_TArray_bool_8 : public TCsMemoryResource<TArray<bool>>
{
};

struct CSCORE_API FCsManager_TArray_bool_8 : public TCsManager_MemoryResource_Fixed<TArray<bool>, FCsMemoryResource_TArray_bool_8, CS_MANAGER_TARRAY_POOL_SIZE>
{
private:

	typedef TCsManager_MemoryResource_Fixed<TArray<bool>, FCsMemoryResource_TArray_bool_8, CS_MANAGER_TARRAY_POOL_SIZE> Super;

public:

	FCsManager_TArray_bool_8() :
		Super()
	{
		const TArray<FCsMemoryResource_TArray_bool_8*>& Array = GetPool();

		for (FCsMemoryResource_TArray_bool_8* M : Array)
		{
			TArray<bool>* R = M->Get();
			R->Reserve(8);
		}
	}
};

#define CS_DECLARE_MANAGER_TARRAY(ValueType, Size, PoolSize) \
	struct CSCORE_API FCsMemoryResource_TArray_##ValueType##_Size : public TCsMemoryResource<TArray<ValueType>>
	{
	};

	struct CSCORE_API FCsManager_TArray_bool_8 : public TCsManager_MemoryResource_Fixed<TArray<bool>, FCsMemoryResource_TArray_bool_8, CS_MANAGER_TARRAY_POOL_SIZE>
	{
	private:

		typedef TCsManager_MemoryResource_Fixed<TArray<bool>, FCsMemoryResource_TArray_bool_8, CS_MANAGER_TARRAY_POOL_SIZE> Super;

	public:

		FCsManager_TArray_bool_8() :
			Super()
		{
			const TArray<FCsMemoryResource_TArray_bool_8*>& Array = GetPool();

			for (FCsMemoryResource_TArray_bool_8* M : Array)
			{
				TArray<bool>* R = M->Get();
				R->Reserve(8);
			}
		}
	};


#pragma endregion Structs

class CSCORE_API FCsManager_TArray
{
public:

	FCsManager_TArray();

	virtual ~FCsManager_TArray();
};