// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/Playback/CsTypes_Playback.h"
// Runnable
#include "Managers/Runnable/Task/CsRunnableTask.h"

#include "CsManager_Playback.generated.h"

class ICsGetManagerPlayback;
class FCsRunnable;

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

// State
#pragma region
public:

	enum class EPlaybackState : uint8
	{
		None,
		Playback,
		Record
	};

private:

	EPlaybackState PlaybackState;

public:

	void SetPlaybackState(const EPlaybackState& NewState);

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

// Record
#pragma region
private:

	struct FRecord
	{
		friend class UCsManager_Playback;

	private:

		UCsManager_Playback* Outer;

		bool bActive;

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
			bActive(false),
			PlaybackByEvents(),
			StartTime(),
			ElapsedTime(),
			Runnable(nullptr), 
			Task(nullptr)
		{
		}

		FORCEINLINE bool IsActive() const
		{
			return bActive;
		}

		void Start(const FSoftObjectPath& LevelPath);

		void Stop();

		void Update(const FCsDeltaTime& DeltaTime);
	};

	FRecord Record;

public:

	FORCEINLINE bool IsRecording() const
	{
		return PlaybackState == EPlaybackState::Record;
	}

#pragma endregion Record

// Playback
#pragma region
private:

	struct FPlayback
	{

	};

#pragma endregion Playback
};