// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"
#include "Containers/CsWeakObjectPtr.h"
#include "Engine/DataTable.h"

#include "CsTdTypes_Creep.generated.h"
#pragma once

// Creep
#pragma region

USTRUCT(BlueprintType)
struct CSTD_API FECsTdCreep : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsTdCreep)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsTdCreep)

struct CSTD_API EMCsTdCreep : public TCsEnumStructMap<FECsTdCreep, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsTdCreep, FECsTdCreep, uint8)
};

namespace NCsTdCreep
{
	typedef FECsTdCreep Type;
}

#pragma endregion Creep

// FCsTdCreepPooledCache
#pragma region

struct CSTD_API FCsTdCreepPooledCache : public ICsPooledObjectCache
{
public:

	int32 Index;

	bool bAllocated;

	bool bQueueDeallocate;

	ECsPooledObjectState State;

	ECsPooledObjectUpdate UpdateType;

	TCsWeakObjectPtr<UObject> Instigator;

	TCsWeakObjectPtr<UObject> Owner;

	TCsWeakObjectPtr<UObject> Parent;

	float WarmUpTime;

	float LifeTime;

	FCsTime StartTime;

	FCsDeltaTime ElapsedTime;

	FCsInterfaceMap* InterfaceMap;

	FCsTdCreepPooledCache() :
		Index(INDEX_NONE),
		bAllocated(false),
		bQueueDeallocate(false),
		State(ECsPooledObjectState::Inactive),
		UpdateType(ECsPooledObjectUpdate::Manager),
		Instigator(),
		Owner(),
		Parent(),
		WarmUpTime(0.0f),
		LifeTime(0.0f),
		StartTime(),
		ElapsedTime(),
		InterfaceMap(nullptr)
	{
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->Add<ICsPooledObjectCache>(static_cast<ICsPooledObjectCache*>(this));
	}

	virtual ~FCsTdCreepPooledCache() 
	{
		delete InterfaceMap;
	}

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsPooledObjectCache
#pragma region

	void Init(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	void Allocate(ICsPooledObjectPayload* Payload, const FCsTime& InTime)
	{

	}

	FORCEINLINE const bool& IsAllocated() const 
	{
		return bAllocated;
	}

	void Deallocate()
	{
		bAllocated = false;
		bQueueDeallocate = false;
	}

	void QueueDeallocate()
	{
		bQueueDeallocate = true;
	}

	FORCEINLINE const bool& ShouldDeallocate() const
	{
		return bQueueDeallocate;
	}

	FORCEINLINE const ECsPooledObjectState& GetState() const
	{
		return State;
	}

	FORCEINLINE const ECsPooledObjectUpdate& GetUpdateType() const
	{
		return UpdateType;
	}

	FORCEINLINE UObject* GetInstigator() const 
	{
		return Instigator.Get();
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Owner.Get();
	}

	FORCEINLINE UObject* GetParent() const
	{
		return Parent.Get();
	}

	FORCEINLINE const float& GetWarmUpTime() const
	{
		return WarmUpTime;
	}

	FORCEINLINE const float& GetLifeTime() const
	{
		return LifeTime;
	}

	FORCEINLINE const FCsTime& GetStartTime() const
	{
		return StartTime;
	}

	FORCEINLINE const FCsDeltaTime& GetElapsedTime() const
	{
		return ElapsedTime;
	}

	FORCEINLINE bool HasLifeTimeExpired()
	{
		return false;
	}

	void Reset()
	{

	}

#pragma endregion ICsPooledObjectCache
};

#pragma endregion FCsTdCreepPooledCache

// ICsTdCreepPayload
#pragma region

struct CSTD_API ICsTdCreepPayload : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsTdCreepPayload() {}
};

#pragma endregion ICsTdCreepPayload

// FCsTdCreepRefContainer
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSTD_API FCsTdCreepRefContainer : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsTdCreep"))
	TSoftClassPtr<UObject> Creep;

	UPROPERTY()
	int32 Creep_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Creep_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Creep_Class;

	UPROPERTY(Transient, BlueprintReadOnly)
	TSubclassOf<UObject> Creep_SubclassOf;

	FCsTdCreepRefContainer() :
		Creep(nullptr),
		Creep_LoadFlags(0),
		Creep_Internal(nullptr),
		Creep_Class(nullptr),
		Creep_SubclassOf(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Creep_Internal; }
	
	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Creep_Class; }

	template<typename T>
	FORCEINLINE T* GetClass() const { return Cast<T>(GetClass()); }

	FORCEINLINE TSubclassOf<UObject> GetSubclassOf() const { return Creep_SubclassOf; }
};

#pragma endregion FCsTdCreepRefContainer