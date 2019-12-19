// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/MemoryResource/CsManager_MemoryResource_Fixed.h"
#include "Types/CsTypes_Primitive.h"
#include <typeinfo>

// Enums
#pragma region

	// ManagerTArraySize
#pragma region

enum class ECsManagerTArraySize
{
	Small,
	Medium,
	Large,
	VeryLarge,
	ECsManagerTArraySize_MAX,
};

struct CSCORE_API EMCsManagerTArraySize final : public TCsEnumMap<ECsManagerTArraySize>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsManagerTArraySize, ECsManagerTArraySize)
};

namespace NCsManagerTArraySize
{
	typedef ECsManagerTArraySize Type;

	namespace Ref
	{
		extern CSCORE_API const Type Small;
		extern CSCORE_API const Type Medium;
		extern CSCORE_API const Type Large;
		extern CSCORE_API const Type VeryLarge;
		extern CSCORE_API const Type ECsManagerTArraySize_MAX;
	}
}

#pragma endregion ManagerTArraySize

#pragma endregion Enums

#define CS_MANAGER_TARRAY_POOL_SIZE 4

// Structs
#pragma region

#define CS_DECLARE_MANAGER_TARRAY_TYPE(ValueType, PoolSize) \
	struct FCsMemoryResource_TArray_##ValueType : public TCsMemoryResource<TArray<ValueType>> \
	{ \
	}; \
	\
	struct FCsManager_TArray_##ValueType : public TCsManager_MemoryResource_Fixed<TArray<bool>, FCsMemoryResource_TArray_##ValueType, PoolSize> \
	{ \
	};

// FCsManager_TArray_bool
CS_DECLARE_MANAGER_TARRAY_TYPE(bool, CS_MANAGER_TARRAY_POOL_SIZE)

#pragma endregion Structs

template<typename ManagerResourceType, typename ResourceContainerType, typename ValueType>
class TCsManager_TArray_ValueType
{
public:

	TArray<int32> Sizes;

	TCsManager_TArray_ValueType() :
		Sizes()
	{
		Sizes.Reserve((uint8)ECsManagerTArraySize::ECsManagerTArraySize_MAX);
		Sizes.Add(8);
		Sizes.Add(64);
		Sizes.Add(128);
		Sizes.Add(512);

		Pool.Reserve((uint8)ECsManagerTArraySize::ECsManagerTArraySize_MAX);

		for (const ECsManagerTArraySize& Size : EMCsManagerTArraySize::Get())
		{
			ManagerResourceType* M = new ManagerResourceType();

			const TArray<ResourceContainerType*>& Array = M->GetPool();

			for (ResourceContainerType* C : Array)
			{
				TArray<ValueType>* R = C->Get();
				R->Reserve(Sizes[(uint8)Size]);
			}

			Pool.Add(M);
		}
	}

	~TCsManager_TArray_ValueType()
	{
		const int32 Count = Pool.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			ManagerResourceType* P = Pool[I];

			delete P;

			Pool[I] = nullptr;
		}
		Pool.Reset();
	}

protected:

	TArray<ManagerResourceType*> Pool;

public:

	TArray<ValueType>& AllocateRef_TArray(const ECsManagerTArraySize& Size)
	{
		const uint8 Index	   = (uint8)Size;
		const int32& Max	   = Sizes[Index];
		TArray<ValueType>* Ptr = Pool[Index]->AllocateResource();

		checkf(Ptr->Max() == Max, TEXT("TCsManager_TArray::AllocateRef_TArray: Array Max has been altered."));

		Ptr->Reset(Ptr->Max());

		return *Ptr;
	}

	TArray<ValueType>& ForceAllocateRef_TArray(const ECsManagerTArraySize& Size)
	{
		if (Pool[(uint8)Size]->IsExhausted())
			Pool[(uint8)Size]->DellocateHead();

		return AllocateRef_TArray(Size);
	}

	void DeallocateAll_TArray(const ECsManagerTArraySize& Size)
	{
		Pool[(uint8)Size]->DeallocateAll();
	}
};

class CSCORE_API FCsManager_TArray
{
public:

	FCsManager_TArray();

	virtual ~FCsManager_TArray();

	TArray<int32> Sizes;

// bool
#pragma region
protected:

	TCsManager_TArray_ValueType<FCsManager_TArray_bool, FCsMemoryResource_TArray_bool, bool> Pool_bool;

public:

	template<typename ValueType>
	TArray<ValueType>& AllocateRef_TArray(const ECsManagerTArraySize& Size)
	{
		// bool
		if (typeid(ValueType) == typeid(bool))
		{
			return Pool_bool.AllocateRef_TArray(Size);
		}
	}

	TArray<bool>& AllocateRef_TArray_bool(const ECsManagerTArraySize& Size);
	TArray<bool>& ForceAllocateRef_TArray_bool(const ECsManagerTArraySize& Size);

	void DeallocateAll_TArray_bool(const ECsManagerTArraySize& Size);

#pragma endregion bool
};