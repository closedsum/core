// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Components/ActorComponent.h"
#include "Managers/Sense/CsTypes_Sense.h"
#include "Managers/Resource/CsManager_ResourceValueType_Abstract.h"
#include "UniqueObject/CsTypes_UniqueObject.h"
#include "Managers/Sense/CsSenseInfo.h"
#include "Managers/Sense/CsSenseHeuristic.h"
#include "CsManager_Sense.generated.h"

// Manager_MemoryResource
#pragma region

struct CSCORE_API FCsResourceContainer_SenseInfo : public TCsResourceContainer<ICsSenseInfo>
{
};

class CSCORE_API FCsManager_SenseInfo : public TCsManager_ResourceValueType_Abstract<ICsSenseInfo, FCsResourceContainer_SenseInfo>
{
private:

	typedef TCsManager_ResourceValueType_Abstract<ICsSenseInfo, FCsResourceContainer_SenseInfo> Super;

public:

	FCsManager_SenseInfo();
	~FCsManager_SenseInfo();

	virtual ICsSenseInfo* ConstructResourceType() override;
};

#pragma endregion Manager_MemoryResource

class ICsSensingObject;
class ICsSensedObject;

UCLASS()
class CSCORE_API UCsManager_Sense : public UActorComponent
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region
protected:

	virtual void OnRegister() override;

#pragma endregion UActorComponent Interface

// Owner
#pragma region
public:

	ICsSensingObject* MySensingOwner;

#pragma endregion Owner

public:

	virtual void Init();
	virtual void Shutdown();

// Info
#pragma region
protected:

	FCsManager_SenseInfo Manager_SenseInfo;

public:
	
	virtual ICsSenseInfo* GetInfo(UObject* Object);

#pragma endregion Info

// Add / Remove
#pragma region
public:

	virtual void Add(ICsSensedObject* SensedObject, UObject* Object);
	//virtual void Add(const FECsSenseObjectType& SenseType, UObject* Object);

	DECLARE_DELEGATE_OneParam(FOnAdd, ICsSenseInfo* /*Info*/);

	FOnAdd OnAdd_Event;

	virtual void Remove(ICsSensedObject* Object);
	//virtual void Remove(UObject* Object);

#pragma endregion Add / Remove

// Sense
#pragma region
public:

protected:

	TMap<FECsSenseObjectType, TMap<FCsUniqueObjectId, ICsSenseInfo*>> SenseMapByType;
	TMap<FCsUniqueObjectId, ICsSenseInfo*> SenseMap;

	TArray<ICsSensedObject*> CurrentSensedObjects;
	TArray<ICsSenseInfo*> SenseInfos;

	TArray<FCsSenseInfoKey> SenseInfoKeys;

public:

	const TArray<ICsSenseInfo*>& GetSenseInfos();

	ICsSenseInfo* GetInfo(ICsSensedObject* Object);

	template<typename SenseInfoType>
	SenseInfoType* GetInfo(ICsSensedObject* Object)
	{
		static_assert(std::is_base_of<ICsSenseInfo, SenseInfoType>(), "UCsManager_Sense::GetInfo: SenseInfoType does NOT implement interface: ICsSenseInfo.");

		return (SenseInfoType*)(GetInfo(Object));
	}

	virtual bool CanSense(UObject* Object);
	virtual bool IsSensing(UObject* Object);

#pragma endregion Sense

// Heuristic
#pragma region
protected:

	TMap<FECsSenseHeuristic, FCsSenseHeuristic> Heuristics;

public:

	const TMap<FECsSenseHeuristic, FCsSenseHeuristic>& GetHeuristics();

	const FCsSenseHeuristic& GetHeuristic(const FECsSenseHeuristic& HeuristicType);

#pragma endregion Heuristic

	virtual void OnTick(const float& DeltaSeconds);
};