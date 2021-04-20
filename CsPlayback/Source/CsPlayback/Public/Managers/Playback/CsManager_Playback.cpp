// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Playback/CsManager_Playback.h"
#include "CsPlayback.h"

// Library
#include "Level/CsLibrary_Level.h"
// Settings
//#include "Settings/CsDeveloperSettings.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Runnable/CsManager_Runnable.h"
// Json
#include  "JsonObjectConverter.h"
// Level
#include "Engine/LevelScriptActor.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Playback/CsGetManagerPlayback.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

 namespace NCsManagerPlayback
 {
	namespace NCached
	{
		namespace Str
		{
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

#if !UE_BUILD_SHIPPING
/*static*/ UCsManager_Playback* UCsManager_Playback::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerPlayback(InRoot)->GetManager_Playback();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}
#endif // #if !UE_BUILD_SHIPPING

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

/*static*/ UCsManager_Playback* UCsManager_Playback::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Playback* Manager = GetSafe(World->GetGameInstance()))
			return Manager;

		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::GetFromWorldContextObject: Failed to Manager Item of type UCsManager_Playback from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
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

		Record.Task = new UCsManager_Playback::FRecord::FTask();

		// Set FileName
		{
			const FString Dir		 = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
			const FString SaveFolder = TEXT("Playback/") + FString(FPlatformProcess::UserName()) + TEXT("/");
			const FString FileName	 = Dir + SaveFolder + FDateTime::Now().ToString(TEXT("%Y%m%d%H%M%S%s")) + TEXT("_") + FGuid::NewGuid().ToString(EGuidFormats::Digits) + TEXT(".json");

			Record.Task->FileName = FileName;
		}

		FCsRunnablePayload* Payload = UCsManager_Runnable::Get(MyRoot)->AllocatePayload();
		Payload->Owner			= this;
		Payload->ThreadPriority = TPri_Normal;
		Payload->Task			= Record.Task;
	 
		Record.Runnable = UCsManager_Runnable::Get(MyRoot)->Start(Payload);
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
		UE_LOG(LogCsPlayback, Warning, TEXT(""));
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
		Record.Update(DeltaTime);
	}
}

// Event
#pragma region

void UCsManager_Playback::OnGameEventInfos(const TArray<FCsGameEventInfo>& Infos)
{
	if (!IsRecording())
		return;

	const FCsTime& CurrentTime = UCsManager_Time::Get(MyRoot)->GetTime(NCsUpdateGroup::GameState);
	Record.ElapsedTime	       = FCsDeltaTime::GetDeltaTime(CurrentTime, Record.StartTime);

	Final_Events.Reset(Final_Events.Max());
	Final_Events.AddDefaulted(Final_Events.Max());

	// Check mark Preview_Events to be used
	for (const FCsGameEventInfo& Info : Infos)
	{
		FCsPlaybackByEvent& Last_Event    = Last_Events[Info.Event.GetValue()];
		FCsPlaybackByEvent& Preview_Event = Preview_Events[Info.Event.GetValue()];
		FCsPlaybackByEvent& Final_Event   = Final_Events[Info.Event.GetValue()];

		if (Last_Event.IsValid() &&
			Last_Event.Event == Info.Event)
		{
			if (Last_Event.Value == Info.Value &&
				Last_Event.Location == Info.Location)
			{
				// Start Repeated
				if (Last_Event.RepeatedState == ECsPlaybackEventRepeatedState::None)
				{
					Last_Event.RepeatedState = ECsPlaybackEventRepeatedState::Start;
					Final_Event = Last_Event;
				}
			}
			else
			{
				Last_Event.RepeatedState = ECsPlaybackEventRepeatedState::None;
				Final_Event = Last_Event;
			}
		}
		else
		{
			Final_Event.Event = Info.Event;
			Final_Event.Value = Info.Value;
			Final_Event.Location = Info.Location;
		}

		Preview_Event.Event = Info.Event;
		Preview_Event.Value = Info.Value;
		Preview_Event.Location = Info.Location;
	}

	// Check for any repeated events that have ended
	for (FCsPlaybackByEvent& Last_Event : Last_Events)
	{
		FCsPlaybackByEvent& Preview_Event = Preview_Events[Last_Event.Event.GetValue()];
		FCsPlaybackByEvent& Final_Event   = Final_Events[Last_Event.Event.GetValue()];

		// Start -> End
		if (Last_Event.IsValid() &&
			!Preview_Event.IsValid() &&
			!Final_Event.IsValid() &&
			Last_Event.RepeatedState == ECsPlaybackEventRepeatedState::Start)
		{
			Last_Event.RepeatedState = ECsPlaybackEventRepeatedState::End;
			Final_Event = Last_Event;
		}

		Last_Event = Final_Event;

		Preview_Event.Reset();
	}

	FCsPlaybackByEventsByDeltaTime& Events = Record.PlaybackByEvents.Events.AddDefaulted_GetRef();

	Events.DeltaTime = Record.ElapsedTime;

	for (FCsPlaybackByEvent& Final_Event : Final_Events)
	{
		if (Final_Event.IsValid())
			Events.Events.Add(Final_Event);
	}
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

	StartTime.Reset();
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