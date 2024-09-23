// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Playback/CsManager_Playback.h"
#include "CsPlayback.h"

// CVars
#include "Managers/Playback/CsCVars_Manager_Playback.h"
// Coroutine
#include "Coroutine/CsRoutine.h"
// Console Command
#include "Managers/Playback/CsConsoleCommand_Manager_Playback.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Managers/Playback/CsLibrary_Manager_Playback.h"
#include "Managers/Runnable/CsLibrary_Manager_Runnable.h"
	// Common
#include "Level/CsLibrary_Level.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Runnable/CsManager_Runnable.h"
// Coordinators
#include "Coordinators/GameEvent/CsCoordinator_GameEvent.h"
// Json
#include "JsonObjectConverter.h"
// Level
#include "Engine/LevelScriptActor.h"
// Runnable
#include "Managers/Runnable/Cache/CsCache_Runnable.h"
// Package
#include "UObject/Package.h"
// File
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"

#if WITH_EDITOR
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Playback/CsGetManagerPlayback.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Playback)

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

	namespace NRecord
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Playback::FRecord, Start);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Playback::FRecord, OnProcessGameEventInfo);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Playback::FRecord, ResolveEvents);			
			}
		}
	}

	namespace NPlayback
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Playback::FPlayback, PlayLatestChecked);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Playback::FPlayback, PlayLatest_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Playback::FPlayback, SafePlayLatest);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Playback::FPlayback, SafePlayLatest_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Playback::FPlayback, Start);			
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Playback::FPlayback, PlayLatest_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Playback::FPlayback, SafePlayLatest_Internal);
			}

			namespace Ext
			{
				const FString json = TEXT(".json");
			}
		}
	}
 }

#pragma endregion Cached

// static initializations
UCsManager_Playback* UCsManager_Playback::s_Instance;
bool UCsManager_Playback::s_bShutdown = false;

UCsManager_Playback::UCsManager_Playback(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Singleton
	bInitialized(false),
	MyRoot(nullptr),
	// Console Command
	Manager_ConsoleCommand(nullptr),
	// State
	PlaybackState(NCsPlayback::EState::None),
	// Save
	SaveDirAbsolute(),
	// Record
	Record(),
	// Playback
	Playback()
{
}

#define USING_NS_CACHED using namespace NCsManagerPlayback::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsManagerPlayback::NCached; \
	const FString& Context = Str::__FunctionName

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

#endif // #if WITH_EDITOR

void UCsManager_Playback::Initialize()
{
	typedef NCsPlayback::NManager::FConsoleCommand ConsoleCommandManagerType;

	Manager_ConsoleCommand = new ConsoleCommandManagerType(MyRoot);

	// Record
	{
		// Event
		{
			Record.Outer = this;

			Record.Task = new UCsManager_Playback::FRecord::FTask();

			// Set FileName
			{
				const FString Dir		 = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
				const FString SaveFolder = TEXT("Playback/") + FString(FPlatformProcess::UserName());

				SaveDirAbsolute = Dir + SaveFolder;

				const FString FileName = FDateTime::Now().ToString(TEXT("%Y%m%d%H%M%S%s")) + TEXT("_") + FGuid::NewGuid().ToString(EGuidFormats::Digits) + TEXT(".json");
				const FString FilePath = SaveDirAbsolute + TEXT("/") + FileName;

				Record.Task->FileName = FilePath;
			}

			typedef NCsRunnable::NPayload::FImpl PayloadType;

			PayloadType* Payload	= UCsManager_Runnable::Get(MyRoot)->AllocatePayload();
			Payload->Owner			= this;
			Payload->ThreadPriority = TPri_Normal;
			Payload->Task			= Record.Task;
	 
			Record.Runnable = UCsManager_Runnable::Get(MyRoot)->Start(Payload);
		}
	}
	// Playback
	{
		Playback.Outer = this;
	}
	// Bind delegate for Game Events
	{
		typedef FECsGameEventCoordinatorGroup GroupType;
		typedef EMCsGameEventCoordinatorGroup GroupMapType;

		UCsCoordinator_GameEvent* Coordinator_GameEvent = UCsCoordinator_GameEvent::Get(MyRoot);

		for (const GroupType& Group : GroupMapType::Get())
		{
			Coordinator_GameEvent->GetOnProcessGameEventInfo_Event(Group).AddRaw(&Record, &UCsManager_Playback::FRecord::OnProcessGameEventInfo);
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
	delete Manager_ConsoleCommand;
	Manager_ConsoleCommand = nullptr;

	// If Manager_Runnable is still active, clear the Owner on Record.Runnable so the
	// Record.Task gets freed
	if (UCsManager_Runnable* Manager_Runnable = CsRunnableManagerLibrary::GetSafe(MyRoot))
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

void UCsManager_Playback::SetPlaybackState(const CsPlaybackStateType& NewState)
{
	SET_CONTEXT(SetPlaybackState);

	if (PlaybackState == NewState)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("%s: PlaybackState is already: %s."), *Context, CsPlaybackStateMapType::Get().ToChar(PlaybackState));
		return;
	}

	PlaybackState = NewState;

	// Playback
	if (PlaybackState == CsPlaybackStateType::Playback)
	{
		Playback.Start();
	}
	// Record
	else
	if (PlaybackState == CsPlaybackStateType::Record)
	{
		FSoftObjectPath LevelPath(CsPersistentLevelLibrary::GetLongPackageNameChecked(Context, MyRoot));

		Record.Start(LevelPath);
	}
}

#pragma endregion State

void UCsManager_Playback::Update(const FCsDeltaTime& DeltaTime)
{
	// Playback
	if (PlaybackState == CsPlaybackStateType::Playback)
	{
		Playback.Update(DeltaTime);
	}
	// Record
	else
	if (PlaybackState == CsPlaybackStateType::Record)
	{
		Record.Update(DeltaTime);
	}
}

// Record
#pragma

#define USING_NS_CACHED2 using namespace NCsManagerPlayback::NRecord::NCached;
#define SET_CONTEXT2(__FunctionName) using namespace NCsManagerPlayback::NRecord::NCached; \
	const FString& Context = Str::__FunctionName

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

void UCsManager_Playback::FRecord::Start(const FSoftObjectPath& LevelPath)
{
	SET_CONTEXT2(Start);

	PlaybackByEvents.Reset();

	PlaybackByEvents.Username = FString(FPlatformProcess::UserName());
	PlaybackByEvents.Level	  = LevelPath;
	PlaybackByEvents.Date	  = FDateTime::Now();

	Task->Events = PlaybackByEvents;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	StartTime = CsTimeManagerLibrary::GetTimeSinceStartChecked(Context, Outer->GetMyRoot(), UpdateGroup);
}

void UCsManager_Playback::FRecord::Stop()
{
}

#define GameEventGroupType FECsGameEventCoordinatorGroup
void UCsManager_Playback::FRecord::OnProcessGameEventInfo(const GameEventGroupType& Group, const FCsGameEventInfo& Info)
{
	SET_CONTEXT2(OnProcessGameEventInfo);

	if (!Outer->IsRecording())
		return;

	if (IgnoredGameEvents.Contains(Info.Event))
		return;

	UObject* ContextRoot			   = Outer->GetMyRoot();
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	const FCsDeltaTime& CurrentTime	   = CsTimeManagerLibrary::GetTimeSinceStartChecked(Context, ContextRoot, UpdateGroup);
	ElapsedTime						   = CurrentTime - StartTime;

	FCsPlaybackByEvent& Preview_Event = Preview_Events[Info.Event.GetValue()];

	Preview_Event.Group	   = Group;
	Preview_Event.Event	   = Info.Event;
	Preview_Event.Value	   = Info.Value;
	Preview_Event.Location = Info.Location;

	bProcessedGameEventInfos = true;
}
#undef GameEventGroupType

void UCsManager_Playback::FRecord::ResolveEvents()
{
	SET_CONTEXT2(ResolveEvents);

	if (bProcessedGameEventInfos ||
		bProcessedGameEventInfos != Last_bProcessedGameEventInfos)
	{
		CS_NON_SHIPPING_EXPR(LogEvent(FString::Printf(TEXT("%s: DeltaTime: %f"), *Context, ElapsedTime.Time)));

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

						CS_NON_SHIPPING_EXPR(LogEvent(FString::Printf(TEXT("%s: CHANGE: None -> Start\n%s"), *Context, *(Final_Event.ToString()))));
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

					CS_NON_SHIPPING_EXPR(LogEvent(FString::Printf(TEXT("%s: CHANGE: %s -> %s\n%s"), *Context, RepeatedStateMapType::Get().ToChar(Last_Event.RepeatedState), RepeatedStateMapType::Get().ToChar(Final_Event.RepeatedState), *(Final_Event.ToString()))));

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

				CS_NON_SHIPPING_EXPR(LogEvent(FString::Printf(TEXT("%s: NEW\n%s"), *Context, *(Final_Event.ToString()))));

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

				CS_NON_SHIPPING_EXPR(LogEvent(FString::Printf(TEXT("%s: END\n%s"), *Context, *(Final_Event.ToString()))));
				AnyValid = true;
			}
			Last_Event = FCsPlaybackByEvent::Invalid;
		}
		// Reset Preview Events
		Preview_Event = FCsPlaybackByEvent::Invalid;
	}

	if (AnyValid)
	{
		FCsPlaybackByEventsByDeltaTime& Events = PlaybackByEvents.Events.AddDefaulted_GetRef();

		Events.DeltaTime = ElapsedTime;

		for (FCsPlaybackByEvent& Final_Event : Final_Events)
		{
			if (Final_Event.IsValid())
			{
				CS_NON_SHIPPING_EXPR(LogEvent(FString::Printf(TEXT("%s: Adding Event\n%s"), *Context, *(Final_Event.ToString()))));
				Events.Events.Add(Final_Event);
			}
			Final_Event = FCsPlaybackByEvent::Invalid;
		}
	}

	bProcessedGameEventInfos = false;
}

bool UCsManager_Playback::FRecord::CanUpdate() const
{
	return Runnable->IsIdle() && Task->IsReady();
}

void UCsManager_Playback::FRecord::Update(const FCsDeltaTime& DeltaTime)
{
	ResolveEvents();

	if (CanUpdate())
	{
		bool PerformWriteTask = Task->Events.CopyFrom(PlaybackByEvents);

		if (PerformWriteTask)
		{
			Task->Start();
			Runnable->Start();
		}
	}
}

bool UCsManager_Playback::FRecord::CanPerformWriteTask() const
{
	return Task->Events.ShouldCopyFrom(PlaybackByEvents);
}

void UCsManager_Playback::FRecord::LogEvent(const FString& Message) const
{
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerPlaybackRecordEvent))
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("%s"), *Message);
	}
}

#undef USING_NS_CACHED2
#undef SET_CONTEXT2

#pragma endregion Record

// Playback
#pragma region

#define USING_NS_CACHED2 using namespace NCsManagerPlayback::NPlayback::NCached;
#define SET_CONTEXT2(__FunctionName) using namespace NCsManagerPlayback::NPlayback::NCached; \
	const FString& Context = Str::__FunctionName

bool UCsManager_Playback::FPlayback::SetLatest(const FString& Context, void(*Log)(const FString&) /*=&NCsPlayback::FLog::Warning*/)
{
	USING_NS_CACHED2
	
	TArray<FString> FoundFiles;

	const FString& Dir = Outer->GetSaveDirAbsolute();

	if (Dir.IsEmpty())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: SaveDirAbsolute is EMPTY."), *Context));
		return false;
	}

	IFileManager::Get().FindFiles(FoundFiles, *Dir, *Ext::json);

	if (FoundFiles.Num() > CS_EMPTY)
	{
		int32 LatestIndex	 = 0;
		FileName			 = Dir + TEXT("/") + FoundFiles[LatestIndex];
		FDateTime LatestTime = IFileManager::Get().GetTimeStamp(*FileName);

		const int32 Count = FoundFiles.Num();

		for (int32 I = 1; I < Count; ++I)
		{
			const FString& File = FoundFiles[I];
			FString Path		= Dir + TEXT("/") + File;

			FDateTime Time = IFileManager::Get().GetTimeStamp(*Path);

			if (Time > LatestTime)
			{
				LatestIndex = I;
				FileName    = Path;
				LatestTime  = Time;
			}
		}

		// File to String
		FString OutString;
		bool Success = FFileHelper::LoadFileToString(OutString, *FileName);

		if (!Success)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load File @ %s to string."), *Context, *FileName));

			FileName = TEXT("");
			return false;
		}
		// Json String to Struct
		Success = FJsonObjectConverter::JsonObjectStringToUStruct<FCsPlaybackByEvents>(OutString, &PlaybackByEvents, 0, 0);

		if (!Success)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to convert File @ %s to UStruct of type: FCsPlaybackByEvents."), *Context, *FileName));

			FileName = TEXT("");
			return false;
		}

		if (!PlaybackByEvents.IsValid(Context, Log))
			return false;
		return true;
	}

	CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Files found @ %s."), *Context, *Dir));
	return false;
}

void UCsManager_Playback::FPlayback::PlayLatestChecked()
{
	SET_CONTEXT2(PlayLatestChecked);

	CS_IS_DELEGATE_BOUND_CHECKED(MakeReadyImpl)
	CS_IS_DELEGATE_BOUND_CHECKED(IsReadyImpl)

	CS_COROUTINE_SETUP_RAW(UCsManager_Playback::FPlayback, PlayLatest_Internal, NCsUpdateGroup::GameInstance, this, Outer, Outer->GetMyRoot());

	CS_COROUTINE_START(Outer);
}

char UCsManager_Playback::FPlayback::PlayLatest_Internal(FCsRoutine* R)
{
	SET_CONTEXT2(PlayLatest_Internal);

	CS_COROUTINE_BEGIN(R);

	Outer->SetPlaybackState(CsPlaybackStateType::None);

	// Wait until the Record's Task is IDLE and NOT Writing
	CS_COROUTINE_WAIT_UNTIL(R, Outer->Record.CanUpdate() && !Outer->Record.CanPerformWriteTask());

	// Set Latest
	{
		bool Success = SetLatest(Context);

		checkf(Success, TEXT("%s: Failed to SetLatest."), *Context);
	}

	MakeReadyImpl.Execute();

	CS_COROUTINE_WAIT_UNTIL(R, IsReadyImpl.Execute());

	Outer->SetPlaybackState(CsPlaybackStateType::QueuePlayback);

	CS_COROUTINE_END(R);
}

void UCsManager_Playback::FPlayback::SafePlayLatest(const FString& Context, void(*Log)(const FString&) /*=&NCsPlayback::FLog::Warning*/)
{
	using namespace NCsManagerPlayback::NPlayback::NCached;

	CS_IS_DELEGATE_BOUND_EXIT(MakeReadyImpl)
	CS_IS_DELEGATE_BOUND_EXIT(IsReadyImpl)

	CS_COROUTINE_SETUP_RAW(UCsManager_Playback::FPlayback, SafePlayLatest_Internal, NCsUpdateGroup::GameInstance, this, Outer, Outer->GetMyRoot());

	CS_COROUTINE_START(Outer);
}

char UCsManager_Playback::FPlayback::SafePlayLatest_Internal(FCsRoutine* R)
{
	SET_CONTEXT2(SafePlayLatest_Internal);

	// TODO: Fix
	static const int32 LOG	   = 0;
	void* Ptr				   = R->GetValue_Void(LOG);
	void(*Log)(const FString&) = (void(*)(const FString&))Ptr;

	CS_COROUTINE_BEGIN(R);

	Outer->SetPlaybackState(CsPlaybackStateType::None);
	
	// Wait until the Record's Task is IDLE and NOT Writing
	CS_COROUTINE_WAIT_UNTIL(R, Outer->Record.CanUpdate() && !Outer->Record.CanPerformWriteTask());

	// Set Latest
	{
		bool Success = SetLatest(Context, Log);

		if (!Success)
		{
			CS_COROUTINE_EXIT(R);
		}
	}

	MakeReadyImpl.Execute();

	CS_COROUTINE_WAIT_UNTIL(R, IsReadyImpl.Execute());

	Outer->SetPlaybackState(CsPlaybackStateType::Playback);

	CS_COROUTINE_END(R);
}

void UCsManager_Playback::FPlayback::Start()
{
	SET_CONTEXT2(Start);

	checkf(!FileName.IsEmpty(), TEXT("%s: No FileName set for Playback."), *Context);

	Index = CS_FIRST;
	ElapsedTime.Reset();
}

void UCsManager_Playback::FPlayback::Update(const FCsDeltaTime& DeltaTime)
{
	// TODO: Check for other ways to end Playback
	if (Index >= PlaybackByEvents.Events.Num())
	{
		Outer->SetPlaybackState(CsPlaybackStateType::None);
		return;
	}

	UObject* ContextRoot							= Outer->GetMyRoot();
	UCsCoordinator_GameEvent* Coordinator_GameEvent = UCsCoordinator_GameEvent::Get(ContextRoot);

	bool ProccessedGameEventInfo = false;

	const FCsPlaybackByEventsByDeltaTime& Events = PlaybackByEvents.Events[Index];

	if (ElapsedTime >= Events.DeltaTime)
	{
		for (const FCsPlaybackByEvent& Event : Events.Events)
		{
			typedef ECsPlaybackEventRepeatedState RepeatedStateType;

			const RepeatedStateType& RepeatedState = Event.RepeatedState;

			// None Broadcast Event
			if (RepeatedState == RepeatedStateType::None)
			{
				CS_NON_SHIPPING_EXPR(LogEvent(Event));

				FCsGameEventInfo Info(Event.Event, Event.Value, Event.Location);

				Coordinator_GameEvent->ProcessGameEventInfo(Event.Group, Info);

				ProccessedGameEventInfo = true;
			}
			// Start -> Add to SustainedEvents
			else
			if (RepeatedState == RepeatedStateType::Start)
			{
				SustainedEventMap.Add(Event.Event, Event);
			}
			// End -> Remove SustainedEvents and Broadcast Event
			else
			if (RepeatedState == RepeatedStateType::End)
			{
				SustainedEventMap.Remove(Event.Event);

				CS_NON_SHIPPING_EXPR(LogEvent(Event));

				FCsGameEventInfo Info(Event.Event, Event.Value, Event.Location);

				Coordinator_GameEvent->ProcessGameEventInfo(Event.Group, Info);

				ProccessedGameEventInfo = true;
			}
		}
		++Index;
	}
	// Broadcast any Sustained Events
	for (const TPair<FECsGameEvent, FCsPlaybackByEvent>& Pair : SustainedEventMap)
	{
		const FCsPlaybackByEvent& Event = Pair.Value;

		CS_NON_SHIPPING_EXPR(LogEvent(Event));

		FCsGameEventInfo Info(Event.Event, Event.Value, Event.Location);

		Coordinator_GameEvent->ProcessGameEventInfo(Event.Group, Info);
		
		ProccessedGameEventInfo = true;
	}

#if !UE_BUILD_SHIPPING
	if (!ProccessedGameEventInfo &&
		CS_CVAR_LOG_IS_SHOWING(LogManagerPlaybackPlaybackUpdate))
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::FPlayback::Update: None. [%s]"), *(ElapsedTime.ToCompactString()));
	}
#endif // #if !UE_BUILD_SHIPPING

	ElapsedTime += DeltaTime;
}

void UCsManager_Playback::FPlayback::LogEvent(const FCsPlaybackByEvent& Event) const
{
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerPlaybackPlaybackUpdate) ||
		CS_CVAR_LOG_IS_SHOWING(LogManagerPlaybackPlaybackEvent))
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::FPlayback::Update: Broadcasting. [%s]\n%s"), *(ElapsedTime.ToCompactString()), *(Event.ToString()));
	}
}

#undef USING_NS_CACHED2
#undef SET_CONTEXT2

#pragma endregion Playback

#undef USING_NS_CACHED
#undef SET_CONTEXT