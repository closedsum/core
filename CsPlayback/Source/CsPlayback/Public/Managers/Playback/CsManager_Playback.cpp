// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Playback/CsManager_Playback.h"
#include "CsPlayback.h"

// Library
#include "Level/CsLibrary_Level.h"
#include "Managers/Playback/CsLibrary_Manager_Playback.h"
#include "Managers/Runnable/CsLibrary_Manager_Runnable.h"
// Settings
//#include "Settings/CsDeveloperSettings.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Runnable/CsManager_Runnable.h"
// Coordinators
#include "Coordinators/GameEvent/CsCoordinator_GameEvent.h"
// Json
#include "JsonObjectConverter.h"
// Level
#include "Engine/LevelScriptActor.h"
// Runnable
#include "Managers/Runnable/Cache/CsCache_Runnable.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Playback/CsGetManagerPlayback.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

 namespace NCsManagerPlayback
 {
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Playback, GetFromWorldContextObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Playback, SetPlaybackState);
		}
	}
 }

#pragma endregion Cached

// static initializations
UCsManager_Playback* UCsManager_Playback::s_Instance;
bool UCsManager_Playback::s_bShutdown = false;

UCsManager_Playback::UCsManager_Playback(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Playback* UCsManager_Playback::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerPlayback(InRoot)->GetManager_Playback();
}

#endif // #if WITH_EDITOR

#if WITH_EDITOR
/*static*/ bool UCsManager_Playback::IsValid(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerPlayback(InRoot)->GetManager_Playback() != nullptr;
}
#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Playback::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerPlayback* GetManagerPlayback = Get_GetManagerPlayback(InRoot);

	UCsManager_Playback* Manager_Playback = GetManagerPlayback->GetManager_Playback();

	if (!Manager_Playback)
	{
		Manager_Playback = NewObject<UCsManager_Playback>(InRoot, UCsManager_Playback::StaticClass(), TEXT("Manager_Playback_Singleton"), RF_Transient | RF_Public);

		GetManagerPlayback->SetManager_Playback(Manager_Playback);

		Manager_Playback->SetMyRoot(InRoot);
		Manager_Playback->Initialize();
	}
	else
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Playback>(GetTransientPackage(), UCsManager_Playback::StaticClass(), TEXT("Manager_Playback_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Playback::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerPlayback* GetManagerPlayback = Get_GetManagerPlayback(InRoot);
	UCsManager_Playback* Manager_Playback	  = GetManagerPlayback->GetManager_Playback();
	Manager_Playback->CleanUp();

	GetManagerPlayback->SetManager_Playback(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR
/*static*/ bool UCsManager_Playback::HasShutdown(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerPlayback(InRoot)->GetManager_Playback() == nullptr;
}
#endif // #if WITH_EDITOR

#if WITH_EDITOR

/*static*/ ICsGetManagerPlayback* UCsManager_Playback::Get_GetManagerPlayback(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Playback::Get_GetManagerPlayback: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Playback::Get_GetManagerPlayback: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Playback::Get_GetManagerPlayback: Manager_Singleton is NULL."));

	ICsGetManagerPlayback* GetManagerPlayback = Cast<ICsGetManagerPlayback>(Manager_Singleton);

	checkf(GetManagerPlayback, TEXT("UCsManager_Playback::Get_GetManagerPlayback: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerPlayback."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerPlayback;
}

/*static*/ ICsGetManagerPlayback* UCsManager_Playback::GetSafe_GetManagerPlayback(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::GetSafe_GetManagerPlayback: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::GetSafe_GetManagerPlayback: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::GetSafe_GetManagerPlayback: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerPlayback>(Manager_Singleton);
}

/*static*/ UCsManager_Playback* UCsManager_Playback::GetSafe(UObject* Object)
{
	if (ICsGetManagerPlayback* GetManagerPlayback = GetSafe_GetManagerPlayback(Object))
		return GetManagerPlayback->GetManager_Playback();
	return nullptr;
}

/*static*/ UCsManager_Playback* UCsManager_Playback::GetFromWorldContextObject(UObject* WorldContextObject)
{
	using namespace NCsManagerPlayback::NCached;

	const FString& Context = Str::GetFromWorldContextObject;

	typedef NCsPlayback::NManager::FLibrary PlaybackManagerLibrary;

	if (UObject* ContextRoot = PlaybackManagerLibrary::GetSafeContextRoot(Context, WorldContextObject))
	{
		if (UCsManager_Playback* Manager = GetSafe(ContextRoot))
			return Manager;

		UE_LOG(LogCsPlayback, Warning, TEXT("%s: Failed to Manager Item of type UCsManager_Playback from ContextRoot: %s."), *Context, *(ContextRoot->GetName()));
	}
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsManager_Playback::Initialize()
{
	// PlaybackByEvents
	{
		Last_Events.Reset(EMCsGameEvent::Get().Num());
		Last_Events.AddDefaulted(EMCsGameEvent::Get().Num());
		
		Preview_Events.Reset(EMCsGameEvent::Get().Num());
		Preview_Events.AddDefaulted(EMCsGameEvent::Get().Num());

		Final_Events.Reset(EMCsGameEvent::Get().Num());
		Final_Events.AddDefaulted(EMCsGameEvent::Get().Num());

		IgnoredGameEvents.Add(NCsGameEvent::Default__MousePositionXY__);
		IgnoredGameEvents.Add(NCsGameEvent::Default__MouseLeftButtonPressed__);
		IgnoredGameEvents.Add(NCsGameEvent::Default__MouseRightButtonPressed__);

		Record.Outer = this;
		Record.Task = new UCsManager_Playback::FRecord::FTask();

		// Set FileName
		{
			const FString Dir		 = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
			const FString SaveFolder = TEXT("Playback/") + FString(FPlatformProcess::UserName()) + TEXT("/");
			const FString FileName	 = Dir + SaveFolder + FDateTime::Now().ToString(TEXT("%Y%m%d%H%M%S%s")) + TEXT("_") + FGuid::NewGuid().ToString(EGuidFormats::Digits) + TEXT(".json");

			Record.Task->FileName = FileName;
		}

		typedef NCsRunnable::NPayload::FImpl PayloadType;

		PayloadType* Payload	= UCsManager_Runnable::Get(MyRoot)->AllocatePayload();
		Payload->Owner			= this;
		Payload->ThreadPriority = TPri_Normal;
		Payload->Task			= Record.Task;
	 
		Record.Runnable = UCsManager_Runnable::Get(MyRoot)->Start(Payload);
	}
	// Bind delegate for Game Events
	{
		typedef FECsGameEventCoordinatorGroup GroupType;
		typedef EMCsGameEventCoordinatorGroup GroupMapType;

		UCsCoordinator_GameEvent* Coordinator_GameEvent = UCsCoordinator_GameEvent::Get(MyRoot);

		for (const GroupType& Group : GroupMapType::Get())
		{
			Coordinator_GameEvent->GetOnProcessGameEventInfo_Event(Group).AddUObject(this, &UCsManager_Playback::OnProcessGameEventInfo);
		}
	}

	bInitialized = true;
}

/*static*/ bool UCsManager_Playback::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Playback::CleanUp()
{
	typedef NCsRunnable::NManager::FLibrary RunnableManagerLibrary;

	// If Manager_Runnable is still active, clear the Owner on Record.Runnable so the
	// Record.Task gets freed
	if (UCsManager_Runnable* Manager_Runnable = RunnableManagerLibrary::GetSafe(MyRoot))
	{
		Record.Runnable->GetCache()->Owner = nullptr;
	}
	else
	{
		delete Record.Task;
	}
	Record.Runnable = nullptr;
	Record.Task = nullptr;

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Playback::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// State
#pragma region

void UCsManager_Playback::SetPlaybackState(const EPlaybackState& NewState)
{
	using namespace NCsManagerPlayback::NCached;

	const FString& Context = Str::SetPlaybackState;

	if (PlaybackState == NewState)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("%s: PlaybackStat is already: ."), *Context);
		return;
	}

	PlaybackState = NewState;

	// Record
	if (PlaybackState == EPlaybackState::Record)
	{
		typedef NCsLevel::NPersistent::FLibrary LevelLibrary;

		FSoftObjectPath LevelPath(LevelLibrary::GetNameChecked(Context, MyRoot));

		Record.Start(LevelPath);
	}
}

#pragma endregion State

void UCsManager_Playback::Update(const FCsDeltaTime& DeltaTime)
{
	// Playback
	// Record
	if (PlaybackState == EPlaybackState::Record)
	{
		if (IsRecording())
		{
			ResolveEvents();
			Record.Update(DeltaTime);
		}
	}
}

// Event
#pragma region

#define GameEventGroupType FECsGameEventCoordinatorGroup
void UCsManager_Playback::OnProcessGameEventInfo(const GameEventGroupType& Group, const FCsGameEventInfo& Info)
{
#undef GameEventGroupType

	if (!IsRecording())
		return;

	if (IgnoredGameEvents.Contains(Info.Event))
		return;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	const FCsDeltaTime& CurrentTime	   = UCsManager_Time::Get(MyRoot)->GetTimeSinceStart(UpdateGroup);
	Record.ElapsedTime				   = CurrentTime - Record.StartTime;

	FCsPlaybackByEvent& Preview_Event = Preview_Events[Info.Event.GetValue()];

	Preview_Event.Group	   = Group;
	Preview_Event.Event	   = Info.Event;
	Preview_Event.Value	   = Info.Value;
	Preview_Event.Location = Info.Location;

	bProcessedGameEventInfos = true;
}

void UCsManager_Playback::ResolveEvents()
{
	if (bProcessedGameEventInfos ||
		bProcessedGameEventInfos != Last_bProcessedGameEventInfos)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT(": DeltaTime: %f"), Record.ElapsedTime.Time);

		Last_bProcessedGameEventInfos = bProcessedGameEventInfos;
	}

	typedef FECsGameEventCoordinatorGroup GroupType;

	typedef ECsPlaybackEventRepeatedState RepeatedStateType;
	typedef EMCsPlaybackEventRepeatedState RepeatedStateMapType;

	bool AnyValid = false;

	const int32 Count = EMCsGameEvent::Get().Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsPlaybackByEvent& Preview_Event = Preview_Events[I];
		FCsPlaybackByEvent& Last_Event	  = Last_Events[I];
		FCsPlaybackByEvent& Final_Event   = Final_Events[I];

		const GroupType& Group = Preview_Event.Group;

		if (Preview_Event.IsValid())
		{
			if (Last_Event.IsValid())
			{
				if (Last_Event.Value == Preview_Event.Value &&
					Last_Event.Location == Preview_Event.Location)
				{
					// Start Repeated
					if (Last_Event.RepeatedState == RepeatedStateType::None)
					{
						Last_Event.RepeatedState = RepeatedStateType::Start;
						Final_Event				 = Last_Event;

						UE_LOG(LogCsPlayback, Warning, TEXT(": CHANGE: None -> Start\n%s"), *(Final_Event.ToString()));

						AnyValid = true;
					}
				}
				else
				{
					// End Repeated
					if (Last_Event.RepeatedState == RepeatedStateType::Start)
					{
						Final_Event.RepeatedState = RepeatedStateType::End;
					}
					else
					{
						Final_Event.RepeatedState = RepeatedStateType::None;
					}

					Final_Event.Group	 = Group;
					Final_Event.Event    = Preview_Event.Event;
					Final_Event.Value    = Preview_Event.Value;
					Final_Event.Location = Preview_Event.Location;

					UE_LOG(LogCsPlayback, Warning, TEXT(": CHANGE: %s -> %s\n%s"), RepeatedStateMapType::Get().ToChar(Last_Event.RepeatedState), RepeatedStateMapType::Get().ToChar(Final_Event.RepeatedState), *(Final_Event.ToString()));

					Last_Event = Final_Event;

					AnyValid = true;
				}
			}
			else
			{
				Final_Event.Group		  = Group;
				Final_Event.Event		  = Preview_Event.Event;
				Final_Event.Value		  = Preview_Event.Value;
				Final_Event.Location	  = Preview_Event.Location;
				Final_Event.RepeatedState = RepeatedStateType::None;

				UE_LOG(LogCsPlayback, Warning, TEXT(": NEW\n%s"), *(Final_Event.ToString()));

				Last_Event = Final_Event;

				AnyValid = true;
			}
		}
		else
		{
			if (Last_Event.IsValid() &&
				Last_Event.RepeatedState == RepeatedStateType::Start)
			{
				Final_Event				  = Last_Event;
				Final_Event.RepeatedState = RepeatedStateType::End;

				UE_LOG(LogCsPlayback, Warning, TEXT(": END\n%s"), *(Final_Event.ToString()));

				AnyValid = true;
			}
			Last_Event = FCsPlaybackByEvent::Invalid;
		}
		// Reset Preview Events
		Preview_Event = FCsPlaybackByEvent::Invalid;
	}

	if (AnyValid)
	{
		FCsPlaybackByEventsByDeltaTime& Events = Record.PlaybackByEvents.Events.AddDefaulted_GetRef();

		Events.DeltaTime = Record.ElapsedTime;

		for (FCsPlaybackByEvent& Final_Event : Final_Events)
		{
			if (Final_Event.IsValid())
			{
				UE_LOG(LogCsPlayback, Warning, TEXT(": Adding Event\n%s"), *(Final_Event.ToString()));

				Events.Events.Add(Final_Event);
			}
			Final_Event = FCsPlaybackByEvent::Invalid;
		}
	}

	bProcessedGameEventInfos = false;
}

#pragma endregion Event

// Record
#pragma region

void UCsManager_Playback::FRecord::Start(const FSoftObjectPath& LevelPath)
{
	PlaybackByEvents.Reset();

	PlaybackByEvents.Username = FString(FPlatformProcess::UserName());
	PlaybackByEvents.Level	  = LevelPath;
	PlaybackByEvents.Date	  = FDateTime::Now();

	Task->Events = PlaybackByEvents;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	StartTime = UCsManager_Time::Get(Outer->GetMyRoot())->GetTimeSinceStart(UpdateGroup);
}

void UCsManager_Playback::FRecord::Stop()
{
}

void UCsManager_Playback::FRecord::Update(const FCsDeltaTime& DeltaTime)
{
	if (Runnable->IsIdle() &&
		Task->IsReady())
	{
		bool PerformWriteTask = Task->Events.CopyFrom(PlaybackByEvents);

		if (PerformWriteTask)
		{
			Task->Start();
			Runnable->Start();
		}
	}
}

	// Task
#pragma region

void UCsManager_Playback::FRecord::FTask::Execute()
{
	// Struct to Json String
	FString OutString;
	bStructToJsonSuccess = FJsonObjectConverter::UStructToJsonObjectString<FCsPlaybackByEvents>(Events, OutString, 0, 0);

	// String to File
	if (bStructToJsonSuccess)
	{
		bSaveStrToFileSuccess = FFileHelper::SaveStringToFile(OutString, *FileName);
	}

	State = EState::Complete;
}

#pragma endregion Task

#pragma endregion Record