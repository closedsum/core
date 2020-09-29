// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
#include "Types/Enum/CsEnumMap.h"
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

#pragma endregion Structs

// TCsManager_TArray_ValueType
#pragma region

template<typename ManagerResourceType, typename ResourceContainerType, typename ValueType>
class TCsManager_TArray_ValueType
{
public:

	TArray<int32> Sizes;

	TCsManager_TArray_ValueType() :
		Sizes()
	{
		Sizes.Reset((uint8)ECsManagerTArraySize::ECsManagerTArraySize_MAX);
		Sizes.Add(8);
		Sizes.Add(64);
		Sizes.Add(128);
		Sizes.Add(512);

		Pool.Reset((uint8)ECsManagerTArraySize::ECsManagerTArraySize_MAX);

		for (const ECsManagerTArraySize& Size : EMCsManagerTArraySize::Get())
		{
			ManagerResourceType* M = new ManagerResourceType();

			const TArray<ResourceContainerType*>& Array = M->GetPool();

			for (ResourceContainerType* C : Array)
			{
				TArray<ValueType>* R = C->Get();
				R->Reset(Sizes[(uint8)Size]);
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

	TArray<ValueType>& AllocateRef(const ECsManagerTArraySize& Size)
	{
		const uint8 Index	   = (uint8)Size;
		const int32& Max	   = Sizes[Index];
		TArray<ValueType>* Ptr = Pool[Index]->AllocateResource();

		checkf(Ptr->Max() == Max, TEXT("TCsManager_TArray_ValueType::AllocateRef_TArray: Array Max has been altered."));

		Ptr->Reset(Ptr->Max());

		return *Ptr;
	}

	TArray<ValueType>& ForceAllocateRef(const ECsManagerTArraySize& Size)
	{
		if (Pool[(uint8)Size]->IsExhausted())
			Pool[(uint8)Size]->DeallocateHead();

		return AllocateRef(Size);
	}

	void DeallocateAll(const ECsManagerTArraySize& Size)
	{
		Pool[(uint8)Size]->DeallocateAll();
	}
};

#pragma endregion TCsManager_TArray_PointerType

// TCsManager_TArray_PointerType
#pragma region

template<typename ManagerResourceType, typename ResourceContainerType, typename PointerType>
class TCsManager_TArray_PointerType
{
public:

	TArray<int32> Sizes;

	TCsManager_TArray_PointerType() :
		Sizes()
	{
		Sizes.Reset((uint8)ECsManagerTArraySize::ECsManagerTArraySize_MAX);
		Sizes.Add(8);
		Sizes.Add(64);
		Sizes.Add(128);
		Sizes.Add(512);

		Pool.Reset((uint8)ECsManagerTArraySize::ECsManagerTArraySize_MAX);

		for (const ECsManagerTArraySize& Size : EMCsManagerTArraySize::Get())
		{
			ManagerResourceType* M = new ManagerResourceType();

			const TArray<ResourceContainerType*>& Array = M->GetPool();

			for (ResourceContainerType* C : Array)
			{
				TArray<PointerType*>* R = C->Get();
				R->Reset(Sizes[(uint8)Size]);
			}

			Pool.Add(M);
		}
	}

	~TCsManager_TArray_PointerType()
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

	TArray<PointerType*>& AllocateRef(const ECsManagerTArraySize& Size)
	{
		const uint8 Index		  = (uint8)Size;
		const int32& Max		  = Sizes[Index];
		TArray<PointerType*>* Ptr = Pool[Index]->AllocateResource();

		checkf(Ptr->Max() == Max, TEXT("TCsManager_TArray_PointerType::AllocateRef_TArray: Array Max has been altered."));

		Ptr->Reset(Ptr->Max());

		return *Ptr;
	}

	TArray<PointerType*>& ForceAllocateRef(const ECsManagerTArraySize& Size)
	{
		if (Pool[(uint8)Size]->IsExhausted())
			Pool[(uint8)Size]->DeallocateHead();

		return AllocateRef(Size);
	}

	void DeallocateAll(const ECsManagerTArraySize& Size)
	{
		Pool[(uint8)Size]->DeallocateAll();
	}
};

#pragma endregion TCsManager_TArray_PointerType

// Macros
#pragma region

#define CS_DECLARE_MANAGER_TARRAY_VALUE_TYPE(ValueType) \
	protected: \
	\
		struct FCsResourceContainer_TArray_##ValueType : public TCsResourceContainer<TArray<ValueType>> \
		{ \
		}; \
		\
		struct FCsManager_TArray_##ValueType : public TCsManager_ResourceValueType_Fixed<TArray<ValueType>, FCsResourceContainer_TArray_##ValueType, CS_MANAGER_TARRAY_POOL_SIZE> \
		{ \
		}; \
	\
		TCsManager_TArray_ValueType<FCsManager_TArray_##ValueType, FCsResourceContainer_TArray_##ValueType, ValueType> Pool_##ValueType; \
	\
	public: \
	\
		template<> \
		TArray<ValueType>& AllocateRef<ValueType>(const ECsManagerTArraySize& Size) \
		{ \
			return Pool_##ValueType.AllocateRef(Size); \
		} \
	\
		template<> \
		TArray<ValueType>& ForceAllocateRef<ValueType>(const ECsManagerTArraySize& Size) \
		{ \
			return Pool_##ValueType.ForceAllocateRef(Size); \
		} \
	\
		template<> \
		void DeallocateAll<ValueType>(const ECsManagerTArraySize& Size) \
		{ \
			Pool_##ValueType.DeallocateAll(Size); \
		}

#define CS_DECLARE_MANAGER_TARRAY_POINTER_TYPE(PointerType) \
	protected: \
	\
		struct FCsResourceContainer_TArray_##PointerType : public TCsResourceContainer<TArray<PointerType*>> \
		{ \
		}; \
		\
		struct FCsManager_TArray_##PointerType : public TCsManager_ResourceValueType_Fixed<TArray<PointerType*>, FCsResourceContainer_TArray_##PointerType, CS_MANAGER_TARRAY_POOL_SIZE> \
		{ \
		}; \
	\
		TCsManager_TArray_PointerType<FCsManager_TArray_##PointerType, FCsResourceContainer_TArray_##PointerType, PointerType> Pool_##PointerType; \
	\
	public: \
	\
		template<> \
		TArray<PointerType*>& AllocateRef<PointerType*>(const ECsManagerTArraySize& Size) \
		{ \
			return Pool_##PointerType.AllocateRef(Size); \
		} \
	\
		template<> \
		TArray<PointerType*>& ForceAllocateRef<PointerType*>(const ECsManagerTArraySize& Size) \
		{ \
			return Pool_##PointerType.ForceAllocateRef(Size); \
		} \
	\
		template<> \
		void DeallocateAll<PointerType*>(const ECsManagerTArraySize& Size) \
		{ \
			Pool_##PointerType.DeallocateAll(Size); \
		}

#pragma endregion Macros

class CSCORE_API FCsManager_TArray
{
public:

	FCsManager_TArray();

	virtual ~FCsManager_TArray();

public:

	template<typename ValueType>
	TArray<ValueType>& AllocateRef(const ECsManagerTArraySize& Size);

	template<typename ValueType>
	TArray<ValueType>& ForceAllocateRef(const ECsManagerTArraySize& Size);

	template<typename ValueType>
	void DeallocateAll(const ECsManagerTArraySize& Size);

	// bool
	CS_DECLARE_MANAGER_TARRAY_VALUE_TYPE(bool)
	// int32
	CS_DECLARE_MANAGER_TARRAY_VALUE_TYPE(int32)

	// UObject
	CS_DECLARE_MANAGER_TARRAY_POINTER_TYPE(UObject)
	// AActor
	CS_DECLARE_MANAGER_TARRAY_POINTER_TYPE(AActor)
};