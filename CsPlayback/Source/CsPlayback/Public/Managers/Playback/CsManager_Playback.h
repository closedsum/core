// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/Playback/CsTypes_Playback.h"
// Utility
#include "Utility/CsPlaybackLog.h"
// Runnable
#include "Managers/Runnable/Task/CsRunnableTask.h"
// Coroutine
#include "Coroutine/CsRoutineHandle.h"

#include "CsManager_Playback.generated.h"

class ICsGetManagerPlayback;
class FCsRunnable;
struct FCsRoutine;

// NCsPlayback::NManager::FConsoleCommand
CS_FWD_DECLARE_CLASS_NAMESPACE_2(NCsPlayback, NManager, FConsoleCommand)

UCLASS(transient)
class CSPLAYBACK_API UCsManager_Playback : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Playback* Get(UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Playback* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	static bool IsValid(UObject* InRoot = nullptr);
#else
	FORCEINLINE static bool IsValid(UObject* InRoot = nullptr)
	{
		return !s_bShutdown && s_Instance != nullptr;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot);

	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
	static bool HasShutdown(UObject* InRoot = nullptr);
#else
	FORCEINLINE static bool HasShutdown(UObject* InRoot = nullptr)
	{
		return s_bShutdown;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
protected:

	static ICsGetManagerPlayback* Get_GetManagerPlayback(UObject* InRoot);
	static ICsGetManagerPlayback* GetSafe_GetManagerPlayback(UObject* Object);

	static UCsManager_Playback* GetSafe(UObject* Object);

public:

	static UCsManager_Playback* GetFromWorldContextObject(UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

	void CleanUp();

private:
	// Singleton data
	static UCsManager_Playback* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Console Command
#pragma region
private:

#define ConsoleCommandManagerType NCsPlayback::NManager::FConsoleCommand
	ConsoleCommandManagerType* Manager_ConsoleCommand;
#undef ConsoleCommandManagerType

#pragma endregion Console Command

// State
#pragma region

#define StateType NCsPlayback::EState

private:

	StateType PlaybackState;

public:

	void SetPlaybackState(const StateType& NewState);
	FORCEINLINE const StateType& GetPlaybackState() const { return PlaybackState; }

#undef StateType

#pragma endregion State

public:

	void Update(const FCsDeltaTime& DeltaTime);

// Event
#pragma region
private:

	TArray<FCsPlaybackByEvent> Last_Events;
	TArray<FCsPlaybackByEvent> Preview_Events;
	TArray<FCsPlaybackByEvent> Final_Events;

	TSet<FECsGameEvent> IgnoredGameEvents;

public:

#define GameEventGroupType FECsGameEventCoordinatorGroup
	void OnProcessGameEventInfo(const GameEventGroupType& Group, const FCsGameEventInfo& Info);
#undef GameEventGroupType

private:

	bool bProcessedGameEventInfos;
	bool Last_bProcessedGameEventInfos;

	void ResolveEvents();

#pragma endregion Event

// Save
#pragma region
private:

	FString SaveDirAbsolute;

public:

	FORCEINLINE const FString& GetSaveDirAbsolute() const { return SaveDirAbsolute; }

#pragma endregion Save

// Record
#pragma region
private:

	struct FRecord
	{
		friend class UCsManager_Playback;

	private:

		UCsManager_Playback* Outer;

		FCsPlaybackByEvents PlaybackByEvents;

		FCsDeltaTime StartTime;

		FCsDeltaTime ElapsedTime;

		FCsRunnable* Runnable;

	#define TaskType NCsRunnable::NTask::ITask

		struct FTask : TaskType
		{
			friend struct FRecord;

		private:

			enum class EState : uint8
			{
				None,
				Running,
				Complete
			};

			EState State;

			TArray<FCsOnRunnableTaskComplete> OnComplete_Events;

			TArray<FCsOnRunnableTaskComplete> OnComplete_AsyncEvents;

		public:

			FCsPlaybackByEvents Events;

			FString FileName;

			bool bStructToJsonSuccess;

			bool bSaveStrToFileSuccess;

			FTask() :
				State(EState::None),
				OnComplete_Events(),
				OnComplete_AsyncEvents(),
				Events(),
				FileName(),
				bStructToJsonSuccess(false),
				bSaveStrToFileSuccess(false)
			{
			}

			~FTask() {}

		// NCsRunnable::NTask::ITask
		#pragma region
		public:

			void Execute();

			FORCEINLINE bool IsRunning() const
			{
				return State == EState::Running;
			}

			FORCEINLINE bool IsComplete() const
			{
				return State == EState::Complete;
			}

			TArray<FCsOnRunnableTaskComplete>& GetOnComplete_Events()
			{
				return OnComplete_Events;
			}

			TArray< FCsOnRunnableTaskComplete>& GetOnComplete_AsyncEvents()
			{
				return OnComplete_AsyncEvents;
			}

			void Reset()
			{
				State = EState::None;
			}

			FORCEINLINE bool IsReady() const
			{
				return State == EState::None || State == EState::Complete;
			}

			FORCEINLINE void Start()
			{
				State = EState::Running;
			}

		#pragma endregion NCsRunnable::NTask::ITask
		};

	#undef TaskType

		FTask* Task;

	public:

		FRecord() :
			Outer(nullptr),
			PlaybackByEvents(),
			StartTime(),
			ElapsedTime(),
			Runnable(nullptr), 
			Task(nullptr)
		{
		}

	private:

		void Start(const FSoftObjectPath& LevelPath);

		void Stop();

	public:

		bool CanUpdate() const;

	private:

		void Update(const FCsDeltaTime& DeltaTime);

	public:

		bool CanPerformWriteTask() const;

		void LogEvent(const FString& Message) const;
	};

public:

	FRecord Record;

	FORCEINLINE bool IsRecording() const
	{
		return PlaybackState == NCsPlayback::EState::Record;
	}

#pragma endregion Record

// Playback
#pragma region
private:

	struct FPlayback
	{
		friend class UCsManager_Playback;

	private:

		UCsManager_Playback* Outer;

		FString FileName;

		DECLARE_DELEGATE(FMakeReadyImpl);

		FMakeReadyImpl MakeReadyImpl;

		DECLARE_DELEGATE_RetVal(bool, FIsReadyImpl);

		FIsReadyImpl IsReadyImpl;

		FCsPlaybackByEvents PlaybackByEvents;

		TMap<FECsGameEvent, FCsPlaybackByEvent> SustainedEventMap;

		int32 Index;

		FCsDeltaTime ElapsedTime;

	public:

		FPlayback() :
			Outer(nullptr),
			FileName(),
			MakeReadyImpl(),
			IsReadyImpl(),
			PlaybackByEvents(),
			SustainedEventMap(),
			Index(0),
			ElapsedTime(),
			PlayLatestHandle()
		{
		}

		bool SetLatest(const FString& Context, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning);

		FMakeReadyImpl& GetMakeReadyImpl() { return MakeReadyImpl; }
		FIsReadyImpl& GetIsReadyImpl() { return IsReadyImpl; }

		const FSoftObjectPath& GetLevelPath() const { return PlaybackByEvents.Level; }

		void PlayLatestChecked();

	private:

		char PlayLatest_Internal(FCsRoutine* R);

		FCsRoutineHandle PlayLatestHandle;

	public:

		void SafePlayLatest(const FString& Context, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning);

	private:

		char SafePlayLatest_Internal(FCsRoutine* R);

	public:

		void Start();

	private:

		void Update(const FCsDeltaTime& DeltaTime);

	public:

		FORCEINLINE bool IsSustainedGameEvent(const FECsGameEvent& Event) const
		{
			return SustainedEventMap.Find(Event) != nullptr;
		}

		void LogEvent(const FCsPlaybackByEvent& Event) const;
	};

public:

	FPlayback Playback;

	FORCEINLINE bool IsPlayingBack() const
	{
		return PlaybackState == NCsPlayback::EState::Playback;
	}

#pragma endregion Playback
};