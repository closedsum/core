// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sense/CsManager_Sense.h"
#include "CsCore.h"

#include "UniqueObject/CsUniqueObject.h"
#include "Managers/Sense/CsSensedObject.h"

// Manager_Resource
#pragma region

FCsManager_SenseInfo::FCsManager_SenseInfo() :
	Super()
{
}

FCsManager_SenseInfo::~FCsManager_SenseInfo()
{
}

ICsSenseInfo* FCsManager_SenseInfo::ConstructResourceType()
{
	return new FCsSenseInfo();
}

#pragma endregion Manager_Resource

UCsManager_Sense::UCsManager_Sense(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
}

// UObject Interface
#pragma region

void UCsManager_Sense::BeginDestroy()
{
	Super::BeginDestroy();

	Shutdown();
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsManager_Sense::OnRegister()
{
	Super::OnRegister();

	Init();
}

#pragma endregion UActorComponent Interface

// Owner
#pragma region

#pragma endregion Owner

void UCsManager_Sense::Init()
{
}

void UCsManager_Sense::Shutdown()
{
}

// Info
#pragma region

ICsSenseInfo* UCsManager_Sense::GetInfo(UObject* Object)
{
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(Object);

	checkf(UniqueObject, TEXT("UCsManager_Sense::GetInfo: Object: %s does not implement interface: ICsUniqueObject."), *(Object->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();
	/*
	for (TPair<FECsSenseObjectType, TMap<FCsUniqueObjectId, ICsSenseInfo*>>& Pair : SenseMap)
	{
		TMap<FCsUniqueObjectId, ICsSenseInfo*>& Map = Pair.Value;

		if (ICsSenseInfo** Info = Map.Find(Id))
		{
			return *Info;
		}
	}
	*/
	UE_LOG(LogCs, Warning, TEXT("UCsManager_Sense::GetInfo: Object: %s with UniqueId: %s has NOT been added to the SenseMap."), *(Object->GetName()), *(UniqueObject->GetId().Id.ToString()));
	return nullptr;
}

#pragma endregion Info

// Add
#pragma region

void UCsManager_Sense::Add(ICsSensedObject* SensedObject, UObject* Object)
{
	// TODO: Consider using UniqueObject as well

	for (ICsSenseInfo* Info : SenseInfos)
	{
		const FCsSensedObject& O = Info->GetObject();

		if (O.GetInterface() == SensedObject)
			return;
	}

	FCsResourceContainer_SenseInfo* Resource = Manager_SenseInfo.SafeAllocate();// SafeAllocate <FCsSenseInfoMemoryResource>();
	ICsSenseInfo* Info						 = Resource->Get();

	Info->SetObject(SensedObject, Object);
	SenseInfos.Add(Info);

	OnAdd_Event.ExecuteIfBound(Info);
}

/*
void UCsManager_Sense::Add(const FECsSenseObjectType& SenseType, UObject* Object)
{
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(Object);

	checkf(UniqueObject, TEXT("UCsManager_Sense::Add: Object: %s does not implement interface: ICsUniqueObject."), *(Object->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();

	TMap<FCsUniqueObjectId, ICsSenseInfo*>& Map = SenseMapByType[SenseType];
	ICsSenseInfo** InfoPtr						= Map.Find(Id);

	if (InfoPtr)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Sense::Add: Object: %s has alreayd been added."), *(Object->GetName()));
		return;
	}

	FCsSenseInfoMemoryResource* Resource = Manager_SenseInfo.SafeAllocate<FCsSenseInfoMemoryResource>();

	ICsSenseInfo* Info = Resource->Get<ICsSenseInfo>();

	Map.Add(Id, Info);
}
*/
void UCsManager_Sense::Remove(ICsSensedObject* Object)
{
	// TODO: Consider using UniqueObject as well

	const int32 Count = SenseInfos.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		ICsSenseInfo* Info	    = SenseInfos[I];
		const FCsSensedObject& O = Info->GetObject();

		if (O.GetInterface() == Object)
		{
			SenseInfos.RemoveAt(I, 1, false);
			break;
		}
	}
}

/*
void UCsManager_Sense::Remove(UObject* Object)
{
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(Object);

	checkf(UniqueObject, TEXT("UCsManager_Sense::Remove: Object: %s does not implement interface: ICsUniqueObject."), *(Object->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();

	for (TPair<FECsSenseObjectType, TMap<FCsUniqueObjectId, ICsSenseInfo*>>& Pair : SenseMapByType)
	{
		TMap<FCsUniqueObjectId, ICsSenseInfo*>& Map = Pair.Value;
		ICsSenseInfo** InfoPtr						= Map.Find(Id);

		if (!InfoPtr)
			continue;

		Manager_SenseInfo.Deallocate(*InfoPtr);
	}
}
*/
#pragma endregion Add

// Sense
#pragma region

const TArray<ICsSenseInfo*>& UCsManager_Sense::GetSenseInfos()
{
	return SenseInfos;
}

ICsSenseInfo* UCsManager_Sense::GetInfo(ICsSensedObject* Object)
{
	return nullptr;
}

bool UCsManager_Sense::CanSense(UObject* Object)
{
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(Object);

	checkf(UniqueObject, TEXT("UCsManager_Sense::CanSense: Object: %s does not implement interface: ICsUniqueObject."), *(Object->GetName()));

	return false;
}

bool UCsManager_Sense::IsSensing(UObject* Object)
{
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(Object);

	checkf(UniqueObject, TEXT("UCsManager_Sense::IsSensing: Object: %s does not implement interface: ICsUniqueObject."), *(Object->GetName()));

	return false;
}

#pragma endregion Sense

// Heuristic
#pragma region

const TMap<FECsSenseHeuristic, FCsSenseHeuristic>& UCsManager_Sense::GetHeuristics()
{
	return Heuristics;
}

const FCsSenseHeuristic& UCsManager_Sense::GetHeuristic(const FECsSenseHeuristic& HeuristicType)
{
	return Heuristics[HeuristicType];
}

#pragma endregion Heuristic

void UCsManager_Sense::OnTick(const float& DeltaSeconds)
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();

	for (ICsSenseInfo* IInfo : SenseInfos)
	{
		FCsSenseInfo* Info = (FCsSenseInfo*)IInfo;

		//Info->Update(CurrentTime, Location, Direction);
	}
}