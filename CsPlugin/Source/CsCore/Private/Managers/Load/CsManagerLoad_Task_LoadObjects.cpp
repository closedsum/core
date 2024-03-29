// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Load/CsManagerLoad_Task_LoadObjects.h"
#include "CsCore.h"

// CVar
#include "Managers/Load/CsCVars_Manager_Load.h"
// Library
#include "Library/CsLibrary_Time.h"
#include "Library/CsLibrary_Math.h"

// Cached
#pragma region

namespace NCsManagerLoadTaskLoadObjects
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManagerLoad_Task_LoadObjects, OnFinishLoadObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManagerLoad_Task_LoadObjects, LoadObjectPaths);
		}
	}
}

#pragma endregion Cached

UCsManagerLoad_Task_LoadObjects::UCsManagerLoad_Task_LoadObjects(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Index(INDEX_NONE),
	Handle(),
	UpdateGroup(NCsUpdateGroup::GameInstance),
	StreamableManager(nullptr),
	StreamableHandles(),
	OnStartLoadObjectPath_Event(),
	OnFinishLoadObjectPath_Event(),
	OnStartLoadObjectPaths_Event(),
	OnFinishLoadObjectPaths_Event(),
	OnStartLoadProgress_Event(),
	OnLoadProgressUpdated_Event(),
	Order(ECsLoadAsyncOrder::Bulk),
	Paths(),
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
	StreamableHandles.Reset(StreamableHandles.Max());
	bComplete = false;
	OnStartLoadObjectPath_Event.Unbind();
	OnFinishLoadObjectPath_Event.Unbind();
	OnStartLoadObjectPaths_Event.Unbind();
	OnFinishLoadObjectPaths_Event.Unbind();
	OnStartLoadProgress_Event.Unbind();
	OnLoadProgressUpdated_Event.Unbind();
	Order = ECsLoadAsyncOrder::Bulk;
	Paths.Reset(Paths.Max());
	Count = 0;
	SizeLoaded.Reset();
	Info.Reset();
	StartTime = 0.0f;
	SingleStartTime = 0.0f;
	LoadedObjects.Reset(LoadedObjects.Max());
}

// Update
#pragma region

void UCsManagerLoad_Task_LoadObjects::Update(const FCsDeltaTime& DeltaTime)
{
	// If Queue Empty, EXIT
	if (Paths.Num() == CS_EMPTY)
		return;

	if (Order == ECsLoadAsyncOrder::Bulk)
		OnLoadProgressUpdated_Event.ExecuteIfBound(StreamableHandles[CS_FIRST]->GetProgress());

	// If Still Loading, EXIT
	if (Count < Paths.Num())
		return;

	typedef NCsTime::FLibrary TimeLibrary;

	const float CurrentTime = TimeLibrary::GetCurrentDateTimeSeconds();
	const float LoadTime    = CurrentTime - StartTime;

	// All AssetReferences are LOADED
	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("UCsManagerLoad_Task_LoadObjects::OnUpdate: Finished Loading %d Assets. %s in %f seconds."), Count, *(SizeLoaded.ToString()), LoadTime);
	}

	bComplete = true;

	OnFinishLoadObjectPaths_Event.ExecuteIfBound(Handle, StreamableHandles, Paths, LoadedObjects, LoadTime);

	Reset();
}

#pragma endregion Load

// StreamableManager
#pragma region

void UCsManagerLoad_Task_LoadObjects::OnFinishLoadObjectPath()
{
	using namespace NCsManagerLoadTaskLoadObjects::NCached;

	const FString& Context = Str::OnFinishLoadObjectPath;

	FSoftObjectPath& Path = Paths[Count];

	UObject* Object = Path.ResolveObject();
	
	checkf(Object, TEXT("%s: Object is NULL. Failed to resolve Path @ %s."), *Context, *(Path.ToString()));

	LoadedObjects.Add(Object);

	const int32 LastCount = Count;

	++Count;

	// Get Memory loaded and the time it took
	typedef NCsMath::FLibrary MathLibrary;

	const int32 Bytes	  = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
	const float Kilobytes = MathLibrary::BytesToKilobytes(Bytes);
	const float Megabytes = MathLibrary::BytesToMegabytes(Bytes);

	SizeLoaded.Bytes	 += Bytes;
	SizeLoaded.Kilobytes += Kilobytes;
	SizeLoaded.Megabytes += Megabytes;

	typedef NCsTime::FLibrary TimeLibrary;

	const float CurrentTime = TimeLibrary::GetCurrentDateTimeSeconds();
	const float LoadingTime	= CurrentTime - StartTime;

	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("%s: Finished Loading %s. %f mb (%f kb, %d bytes) in %f seconds."), *Context, *Path.ToString(), Megabytes, Kilobytes, Bytes, LoadingTime);
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
			UE_LOG(LogCs, Log, TEXT("%s: Requesting Load of %s."), *Context, *(NextPath.ToString()));
		}
		OnStartLoadObjectPath_Event.ExecuteIfBound(NextPath);
		StreamableHandles.Add(StreamableManager->RequestAsyncLoad(NextPath, OnFinishLoadObjectPathDelegate));
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
		typedef NCsMath::FLibrary MathLibrary;

		const int32 Bytes	  = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
		const float Kilobytes = MathLibrary::BytesToKilobytes(Bytes);
		const float Megabytes = MathLibrary::BytesToMegabytes(Bytes);

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

#define PayloadType NCsLoad::NManager::NLoadObjectPaths::FPayload
FCsLoadHandle UCsManagerLoad_Task_LoadObjects::LoadObjectPaths(const PayloadType& Payload)
{
#undef PayloadType
	using namespace NCsManagerLoadTaskLoadObjects::NCached;

	const FString& Context = Str::LoadObjectPaths;

	Order = Payload.AsyncOrder;

	const TArray<FSoftObjectPath>& ObjectPaths = Payload.ObjectPaths;

	const int32 Size = ObjectPaths.Num();
	const int32 Max  = FMath::Max(Paths.Max(), Size);

	Paths.Reset(Max);
	Paths.Append(ObjectPaths);

	LoadedObjects.Reset(Max);

	// Add Callback
	OnFinishLoadObjectPaths_Event = Payload.OnFinishLoadObjectPaths;

	// Start Loading - Load All References
	OnStartLoadObjectPaths_Event.ExecuteIfBound(Size);
	OnStartLoadProgress_Event.ExecuteIfBound(Size);

	if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("%s: Requesting Load of %d Assets."), *Context, Size);
		// None | Bulk
		if (Order == ECsLoadAsyncOrder::None ||
			Order == ECsLoadAsyncOrder::Bulk)
		{
			for (const FSoftObjectPath& Path : ObjectPaths)
			{
				UE_LOG(LogCs, Log, TEXT("%s: Requesting Load of %s."), *Context, *(Path.ToString()));
			}
		}
	}
	// Start the Async Load

		// FirstToLast
	if (Order == ECsLoadAsyncOrder::FirstToLast)
	{
		if (CsCVarLogManagerLoad->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Log, TEXT("%s: Requesting Load of %s."), *Context, *(ObjectPaths[CS_FIRST].ToString()));
		}
		OnStartLoadObjectPath_Event.ExecuteIfBound(ObjectPaths[CS_FIRST]);
		StreamableHandles.Add(StreamableManager->RequestAsyncLoad(ObjectPaths[CS_FIRST], OnFinishLoadObjectPathDelegate));
	}
		// Bulk
	else
	{
		StreamableHandles.Add(StreamableManager->RequestAsyncLoad(ObjectPaths, OnFinishLoadObjectPathsDelegate));
	}

	typedef NCsTime::FLibrary TimeLibrary;

	StartTime = TimeLibrary::GetCurrentDateTimeSeconds();

	Handle.New();

	return Handle;
}

#pragma endregion Load