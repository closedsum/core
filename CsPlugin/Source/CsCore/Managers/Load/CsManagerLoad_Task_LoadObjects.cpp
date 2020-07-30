// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Load/CsManagerLoad_Task_LoadObjects.h"
#include "CsCore.h"
#include "CsCVars.h"

// Library
#include "Library/CsLibrary_Common.h"
#include "Library/CsLibrary_Math.h"

#include "Classes/Engine/World.h"

UCsManagerLoad_Task_LoadObjects::UCsManagerLoad_Task_LoadObjects(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Index(INDEX_NONE),
	Handle(),
	UpdateGroup(NCsUpdateGroup::GameInstance),
	OnStartLoadObjectPath_Event(),
	OnFinishLoadObjectPath_Event(),
	OnStartLoadObjectPaths_Event(),
	OnFinishLoadObjectPaths_Event(),
	OnStartLoadProgress_Event(),
	OnLoadProgressUpdated_Event(),
	Order(ECsLoadAsyncOrder::Bulk),
	Paths(),
	World(nullptr),
	Count(0),
	SizeLoaded(),
	Info(),
	StartTime(0.0f),
	SingleStartTime(0.0f)
{
}

void UCsManagerLoad_Task_LoadObjects::Init()
{
	// FirstToLast
	OnFinishLoadObjectPathDelegate = FStreamableDelegate::CreateUObject(this, &UCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPath);
	// None | Bulk
	OnFinishLoadObjectPathsDelegate = FStreamableDelegate::CreateUObject(this, &UCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPaths);
}

void UCsManagerLoad_Task_LoadObjects::Reset()
{
	Handle.Reset();
	Order = ECsLoadAsyncOrder::Bulk;
	Paths.Reset(Paths.Max());
	OnStartLoadObjectPath_Event.Unbind();
	OnFinishLoadObjectPath_Event.Unbind();
	OnStartLoadObjectPaths_Event.Unbind();
	OnFinishLoadObjectPaths_Event.Unbind();
	OnStartLoadProgress_Event.Unbind();
	OnLoadProgressUpdated_Event.Unbind();
	World = nullptr;
	Count = 0;
	SizeLoaded.Reset();
	Info.Reset();
	StartTime = 0.0f;
	SingleStartTime = 0.0f;
	StreamableHandle = nullptr;
}

// Update
#pragma region

void UCsManagerLoad_Task_LoadObjects::Update(const FCsDeltaTime& DeltaTime)
{
	// If Queue Empty, EXIT
	if (Paths.Num() == CS_EMPTY)
		return;

	if (Order == ECsLoadAsyncOrder::Bulk)
		OnLoadProgressUpdated_Event.ExecuteIfBound(StreamableHandle->GetProgress());

	// If Still Loading, EXIT
	if (Count < Paths.Num())
		return;

	const float CurrentTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();
	const float LoadTime    = CurrentTime - StartTime;

	// All AssetReferences are LOADED
	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("UCsManagerLoad_Task_LoadObjects::OnUpdate: Finished Loading %d Assets. %s in %f seconds."), Count, *(SizeLoaded.ToString()), LoadTime);
	}

	OnFinishLoadObjectPaths_Event.ExecuteIfBound(Handle, Paths, LoadedObjects, LoadTime);

	Reset();
}

#pragma endregion Load

// StreamableManager
#pragma region

void UCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPath()
{
	FSoftObjectPath& Path = Paths[Count];

	UObject* Object = Path.ResolveObject();
	
	checkf(Object, TEXT("UCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPath: Object is NULL. Failed to resolve Path @ %s."), *(Path.ToString()));

	LoadedObjects.Add(Object);

	const int32 LastCount = Count;

	++Count;

	// Get Memory loaded and the time it took
	const int32 Bytes	  = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
	const float Kilobytes = FCsLibrary_Math::BytesToKilobytes(Bytes);
	const float Megabytes = FCsLibrary_Math::BytesToMegabytes(Bytes);

	SizeLoaded.Bytes	 += Bytes;
	SizeLoaded.Kilobytes += Kilobytes;
	SizeLoaded.Megabytes += Megabytes;

	const float CurrentTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();
	const float LoadingTime	= CurrentTime - StartTime;

	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("FCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPath: Finished Loading %s. %f mb (%f kb, %d bytes) in %f seconds."), *Path.ToString(), Megabytes, Kilobytes, Bytes, LoadingTime);
	}

	// Broadcast the event to anyone listening
	Info.Path			 = Path;
	Info.Count			 = LastCount;
	Info.Size.Bytes		 = Bytes;
	Info.Size.Kilobytes  = Kilobytes;
	Info.Size.Megabytes  = Megabytes;
	Info.Time			 = LoadingTime;

	OnFinishLoadObjectPath_Event.ExecuteIfBound(Info, Object);

	// FirstToLast, Queue the NEXT Asset for Async Load
	if (Count < Paths.Num())
	{
		FSoftObjectPath& NextPath = Paths[Count];

		if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManager_Load::OnFinishedLoadingAssetReference: Requesting Load of %s."), *(NextPath.ToString()));
		}
		OnStartLoadObjectPath_Event.ExecuteIfBound(NextPath);
		StreamableManager->RequestAsyncLoad(NextPath, OnFinishLoadObjectPathDelegate);
	}
	StartTime = CurrentTime;
}

void UCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPaths()
{
	for (FSoftObjectPath& Path : Paths)
	{
		UObject* Object = Path.ResolveObject();
		
		checkf(Object, TEXT("UCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPaths: Failed to Resolve Path @ %s."), *(Path.ToString()));

		// Get Memory loaded and the time it took
		const int32 Bytes	  = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
		const float Kilobytes = FCsLibrary_Math::BytesToKilobytes(Bytes);
		const float Megabytes = FCsLibrary_Math::BytesToMegabytes(Bytes);

		SizeLoaded.Bytes	 += Bytes;
		SizeLoaded.Kilobytes += Kilobytes;
		SizeLoaded.Megabytes += Megabytes;

		LoadedObjects.Add(Object);
	}
	Count = Paths.Num();
}

#pragma endregion StreamableManager

// Load
#pragma region

FCsLoadHandle UCsManagerLoad_Task_LoadObjects::LoadObjectPaths(const TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder, FOnFinishLoadObjectPaths Delegate)
{
	Order = AsyncOrder;

	const int32 Size = ObjectPaths.Num();
	const int32 Max  = FMath::Max(Paths.Max(), Size);

	Paths.Reserve(Max);
	Paths.Append(ObjectPaths);

	// Add Callback
	OnFinishLoadObjectPaths_Event = Delegate;

	// Start Loading - Load All References
	OnStartLoadObjectPaths_Event.ExecuteIfBound(Size);
	OnStartLoadProgress_Event.ExecuteIfBound(Size);

	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("UCsManagerLoad_Task_LoadObjects::LoadObjectPaths: Requesting Load of %d Assets."), Size);
		// None | Bulk
		if (AsyncOrder == ECsLoadAsyncOrder::None ||
			AsyncOrder == ECsLoadAsyncOrder::Bulk)
		{
			for (const FSoftObjectPath& Path : ObjectPaths)
			{
				UE_LOG(LogCs, Log, TEXT("UCsManagerLoad_Task_LoadObjects::LoadObjectPaths: Requesting Load of %s."), *(Path.ToString()));
			}
		}
	}
	// Start the Async Load

		// FirstToLast
	if (AsyncOrder == ECsLoadAsyncOrder::FirstToLast)
	{
		if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("UCsManagerLoad_Task_LoadObjects::LoadObjectPaths: Requesting Load of %s."), *(ObjectPaths[CS_FIRST].ToString()));
		}
		OnStartLoadObjectPath_Event.ExecuteIfBound(ObjectPaths[CS_FIRST]);
		StreamableManager->RequestAsyncLoad(ObjectPaths[CS_FIRST], OnFinishLoadObjectPathDelegate);
	}
		// Bulk
	else
	{
		StreamableHandle = StreamableManager->RequestAsyncLoad(ObjectPaths, OnFinishLoadObjectPathsDelegate);
	}

	StartTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();

	Handle.New();

	return Handle;
}

#pragma endregion Load