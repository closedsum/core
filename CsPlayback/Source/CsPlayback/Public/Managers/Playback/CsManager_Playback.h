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

	static UCsManager_Playback* Get(UObject* InRoot = nullptr);

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot);

	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

	static void Shutdown();

#if WITH_EDITOR
protected:

	static ICsGetManagerPlayback* Get_GetManagerPlayback(UObject* InRoot);
	static ICsGetManagerPlayback* GetSafe_GetManagerPlayback(UObject* Object);

	static UCsManager_Playback* GetSafe(UObject* Object);

public:

	static UCsManager_Playback* GetFromWorldContextObject(const UObject* WorldContextObject);

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
private:

	enum class EPlaybackState : uint8
	{
		None,
		Playback,
		Record
	};

	EPlaybackState PlaybackState;

#pragma endregion State

private:

	FCsTime PlaybackStartTime;

	FCsDeltaTime PlaybackElapsedTime;

// Record
#pragma region
private:

	FCsTime RecordStartTime;

public:

	void Record();

	FORCEINLINE bool IsRecording() const
	{
		return PlaybackState == EPlaybackState::Record;
	}

#pragma endregion Record

public:

	void Update(const FCsDeltaTime& DeltaTime);

// Event
#pragma region
private:

	FCsPlaybackByEvents PlaybackByEvents;

	TArray<FCsPlaybackByEvent> Last_Events;
	TArray<FCsPlaybackByEvent> Preview_Events;
	TArray<FCsPlaybackByEvent> Final_Events;

public:

	void OnGameEventInfos(const TArray<FCsGameEventInfo>& Infos);

#pragma endregion Event

// Task
#pragma region
private:

	FCsRunnable* PlaybackByEventsRunnable;

	struct FTask : ICsRunnableTask
	{
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

		~FTask(){}

	// ICsRunnableTask
		
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
	};

	FTask* PlaybackByEventsWriteTask;

#pragma endregion Task
};