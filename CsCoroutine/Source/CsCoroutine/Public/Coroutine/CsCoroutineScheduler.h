// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Coroutine/CsCoroutineSchedule.h"

#include "CsCoroutineScheduler.generated.h"

class ICsGetCoroutineScheduler;

UCLASS(transient)
class CSCOROUTINE_API UCsCoroutineScheduler : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	using DefaultScheduleType = NCsCoroutine::NSchedule::FDefault;
	using CustomScheduleType = NCsCoroutine::NSchedule::FCustom;
	using PayloadResourceType = NCsCoroutine::NPayload::FResource;
	using PayloadType = NCsCoroutine::NPayload::FImpl;
	using MessageType = NCsCoroutine::EMessage;

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsCoroutineScheduler* Get(UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsCoroutineScheduler* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	static UCsCoroutineScheduler* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsCoroutineScheduler* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetCoroutineScheduler* Get_GetCoroutineScheduler(UObject* InRoot);
	static ICsGetCoroutineScheduler* GetSafe_GetCoroutineScheduler(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsCoroutineScheduler* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
private:

	UObject* MyRoot;

public:

	FORCEINLINE void SetMyRoot(UObject* InRoot)
	{
		MyRoot = InRoot;
	}

	FORCEINLINE const UObject* GetMyRoot() const
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Owner
#pragma region
public:

	TWeakObjectPtr<UObject> MyOwner;

	FORCEINLINE UObject* GetMyOwner()
	{
		return MyOwner.IsValid() ? MyOwner.Get() : nullptr;
	}

#pragma endregion Owner

// Default
#pragma region
private:

	TArray<DefaultScheduleType> DefaultSchedules_Internal;

	/** */
	TArray<DefaultScheduleType*> DefaultSchedules;

	FORCEINLINE const DefaultScheduleType& GetDefaultSchedule(const FECsUpdateGroup& Group) const
	{
		checkf(Group != NCsUpdateGroup::Custom, TEXT("UCsCoroutineScheduler::GetDefaultSchedule: Group: Custom is NOT a Default Schedule. Use the Custom related functions."));
		return *(DefaultSchedules[Group.GetValue()]);
	}

	FORCEINLINE DefaultScheduleType& GetDefaultSchedule(const FECsUpdateGroup& Group)
	{
		checkf(Group != NCsUpdateGroup::Custom, TEXT("UCsCoroutineScheduler::GetDefaultSchedule: Group: Custom is NOT a Default Schedule. Use the Custom related functions."));
		return *(DefaultSchedules[Group.GetValue()]);
	}

	FORCEINLINE const DefaultScheduleType& GetDefaultSchedule(const PayloadType* Payload) const
	{
		return GetDefaultSchedule(Payload->Group);
	}

	FORCEINLINE DefaultScheduleType& GetDefaultSchedule(const PayloadType* Payload)
	{
		return GetDefaultSchedule(Payload->Group);
	}

	FORCEINLINE const DefaultScheduleType& GetDefaultSchedule(const PayloadResourceType* PayloadContainer) const
	{
		return GetDefaultSchedule(PayloadContainer->Get());
	}

	FORCEINLINE DefaultScheduleType& GetDefaultSchedule(const PayloadResourceType* PayloadContainer)
	{
		return GetDefaultSchedule(PayloadContainer->Get());
	}

	// Start
#pragma region
public:

	/**
	*
	*
	* @param PayloadContainer
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& Start(PayloadResourceType* PayloadContainer)
	{
		return GetDefaultSchedule(PayloadContainer).Start(PayloadContainer);
	}

	/**
	*
	*
	* @param Payload
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& Start(PayloadType* Payload)
	{
		return GetDefaultSchedule(Payload).Start(Payload);
	}

	/**
	*
	*
	* @param PayloadContainer
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& StartChild(PayloadResourceType* PayloadContainer)
	{
		return GetDefaultSchedule(PayloadContainer).StartChild(PayloadContainer);
	}

	/**
	*
	*
	* @param Payload
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& StartChild(PayloadType* Payload)
	{
		return GetDefaultSchedule(Payload).StartChild(Payload);
	}

#pragma endregion Start

	// Update
#pragma region
public:

	/**
	*
	*
	* @param Group
	* @param DeltaTime
	*/
	FORCEINLINE void Update(const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime)
	{
		GetDefaultSchedule(Group).Update(DeltaTime);
	}

#pragma endregion Update
	
	// End
#pragma region
public:

	/**
	*
	*
	* @param Group
	* return
	*/
	FORCEINLINE bool End(const FECsUpdateGroup& Group)
	{
		if (Group == NCsUpdateGroup::Custom)
		{
			for (CustomScheduleType& Schedule : CustomSchedules)
			{
				Schedule.End();
			}
		}
		return GetDefaultSchedule(Group).End();
	}

	/**
	*
	*
	* @param Group
	* @param Handle
	* return
	*/
	FORCEINLINE bool End(const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
	{
		if (Group == NCsUpdateGroup::Custom)
		{
			for (CustomScheduleType& Schedule : CustomSchedules)
			{
				Schedule.End(Handle);
			}
		}
		return GetDefaultSchedule(Group).End(Handle);
	}


	/**
	*
	*/
	void EndAll();

	/**
	* Check if a routine associated with the Group and Handle has already ended.
	* NOTE: This returns True if Handle is NOT Valid.
	* 
	* @param Group
	* @param Handle		Handle to a routine.
	* return			Whether the routine has already ended.
	*/
	FORCEINLINE bool HasEnded(const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle) const
	{
		return GetDefaultSchedule(Group).HasEnded(Handle);
	}

	/**
	* Check if a routine associated with the Group and Handle has just ended.
	*
	* @param Group
	* @param Handle		Handle to a routine.
	* return			Whether the routine has just ended.
	*/
	FORCEINLINE bool HasJustEnded(const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle) const
	{
		return GetDefaultSchedule(Group).HasJustEnded(Handle);
	}

#pragma endregion End

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param Group
	* return
	*/
	FORCEINLINE PayloadResourceType* AllocatePayloadContainer(const FECsUpdateGroup& Group)
	{
		return GetDefaultSchedule(Group).AllocatePayloadContainer();
	}

	/**
	*
	*
	* @param Group
	* return
	*/
	FORCEINLINE PayloadType* AllocatePayload(const FECsUpdateGroup& Group)
	{
		return GetDefaultSchedule(Group).AllocatePayload();
	}

#pragma endregion Payload

	// Handle
#pragma region
public:

	/**
	* 
	* 
	* @param Group
	* @param Handle
	* return
	*/
	FORCEINLINE bool IsHandleValid(const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle) const
	{
		return GetDefaultSchedule(Group).GetRoutineContainer(Handle) != nullptr;
	}

	/**
	* 
	* 
	* @param Group
	* @param Handle
	* return
	*/
	FORCEINLINE bool IsRunning(const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle) const
	{
		return GetDefaultSchedule(Group).IsRunning(Handle);
	}

#pragma endregion Handle

	// Routine
#pragma region

public:

	/**
	*
	*
	* @param Handle
	* return
	*/
	FORCEINLINE FCsRoutine* GetRoutine(const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle) const
	{
		return GetDefaultSchedule(Group).GetRoutine(Handle);
	}

#pragma endregion Routine

	// Message
#pragma region
public:

	FORCEINLINE void BroadcastMessage(const FECsUpdateGroup& Group, const MessageType& Type, const FName& Message, void* InOwner = nullptr)
	{
		if (Group == NCsUpdateGroup::Custom)
		{
			for (CustomScheduleType& Schedule : CustomSchedules)
			{
				Schedule.BroadcastMessage(Type, Message, InOwner);
			}
		}
		else
		{
			GetDefaultSchedule(Group).BroadcastMessage(Type, Message, InOwner);
		}
	}

#pragma endregion Message

#pragma endregion Default

// Custom
#pragma region
private:

	TArray<CustomScheduleType> CustomSchedules;

	FORCEINLINE const CustomScheduleType& GetCustomSchedule(const int32& GroupIndex) const 
	{
		checkf(GroupIndex >= 0 && GroupIndex < CustomSchedules.Num(), TEXT("UCsCoroutineScheduler::GetCustomSchedule: GroupIndex: %d is NOT in the Range [0, %d]."), GroupIndex, CustomSchedules.Num());
		return CustomSchedules[GroupIndex];
	}

	FORCEINLINE CustomScheduleType& GetCustomSchedule(const int32& GroupIndex) 
	{
		checkf(GroupIndex >= 0 && GroupIndex < CustomSchedules.Num(), TEXT("UCsCoroutineScheduler::GetCustomSchedule: GroupIndex: %d is NOT in the Range [0, %d]."), GroupIndex, CustomSchedules.Num());
		return CustomSchedules[GroupIndex];
	}

public:

	FORCEINLINE bool IsValidGroupIndex(const FString& Context, const int32& GroupIndex, void(*Log)(const FString&)) const 
	{
		if (GroupIndex < 0 || GroupIndex > CustomSchedules.Num())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: GroupIndex: %d is NOT in the Range [0, %d]."), *Context, GroupIndex, CustomSchedules.Num()));
			return false;
		}
		return true;
	}

	// Owner
#pragma region
public:

	void AllocateCustomGroupIndexAndOwnerID(int32& OutGroupIndex, int32& OutOwnerID);

	FORCEINLINE void DeallocateOwnerID(const int32& GroupIndex, const int32& OwnerID)
	{
		GetCustomSchedule(GroupIndex).DeallocateOwnerID(OwnerID);
	}

#pragma endregion Owner

	// Start
#pragma region
public:

	/**
	*
	* 
	* @param GroupIndex
	* @param OwnerID
	* @param PayloadContainer
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& CustomStart(const int32& GroupIndex, const int32& OwnerID, PayloadResourceType* PayloadContainer)
	{
		return GetCustomSchedule(GroupIndex).Start(OwnerID, PayloadContainer);
	}

	/**
	*
	*
	* @param GroupIndex
	* @param OwnerID
	* @param Payload
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& CustomStart(const int32& GroupIndex, const int32& OwnerID, PayloadType* Payload)
	{
		return GetCustomSchedule(GroupIndex).Start(OwnerID, Payload);
	}

	/**
	*
	*
	* @param GroupIndex
	* @param OwnerID
	* @param PayloadContainer
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& CustomStartChild(const int32& GroupIndex, const int32& OwnerID, PayloadResourceType* PayloadContainer)
	{
		return GetCustomSchedule(GroupIndex).StartChild(OwnerID, PayloadContainer);
	}

	/**
	*
	*
	* @param GroupIndex
	* @param OwnerID
	* @param Payload
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& CustomStartChild(const int32& GroupIndex, const int32& OwnerID, PayloadType* Payload)
	{
		return GetCustomSchedule(GroupIndex).StartChild(OwnerID, Payload);
	}

#pragma endregion Start

	// Update
#pragma region
public:

	/**
	*
	*
	* @param GroupIndex
	* @param OwnerID
	* @param DeltaTime
	*/
	FORCEINLINE void CustomUpdate(const int32& GroupIndex, const int32& OwnerID, const FCsDeltaTime& DeltaTime)
	{
		GetCustomSchedule(GroupIndex).Update(OwnerID, DeltaTime);
	}

#pragma endregion Update

	// End
#pragma region
public:

	/**
	*
	*
	* @param Group
	* @param Handle
	* return
	*/
	FORCEINLINE bool CustomEnd(const int32& GroupIndex, const FCsRoutineHandle& Handle)
	{
		return GetCustomSchedule(GroupIndex).End(Handle);
	}

	/**
	* Check if a routine associated with the Group: Custom, GroupIndex and Handle has already ended.
	* NOTE: This returns True if Handle is NOT Valid.
	* 
	* @param GroupIndex
	* @param Handle		Handle to a routine.
	* return			Whether the routine has already ended.
	*/
	FORCEINLINE bool HasCustomEnded(const int32& GroupIndex, const FCsRoutineHandle& Handle) const
	{
		return GetCustomSchedule(GroupIndex).HasEnded(Handle);
	}

	/**
	* Check if a routine associated with the Group: Custom, GroupIndex and Handle has just ended.
	*
	* @param GroupIndex
	* @param Handle		Handle to a routine.
	* return			Whether the routine has just ended.
	*/
	FORCEINLINE bool HasCustomJustEnded(const int32& GroupIndex, const FCsRoutineHandle& Handle) const
	{
		return GetCustomSchedule(GroupIndex).HasJustEnded(Handle);
	}

#pragma endregion End

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param GroupIndex
	* return
	*/
	FORCEINLINE PayloadResourceType* AllocateCustomPayloadContainer(const int32& GroupIndex)
	{
		return GetCustomSchedule(GroupIndex).AllocatePayloadContainer();
	}

	/**
	*
	*
	* @param GroupIndex
	* return
	*/
	FORCEINLINE PayloadType* AllocateCustomPayload(const int32& GroupIndex)
	{
		return GetCustomSchedule(GroupIndex).AllocatePayload();
	}

#pragma endregion Payload

	// Handle
#pragma region
public:

	/**
	* 
	* 
	* @param GroupIndex
	* @param Handle
	* return
	*/
	FORCEINLINE bool IsCustomHandleValid(const int32& GroupIndex, const FCsRoutineHandle& Handle) const
	{
		return GetCustomSchedule(GroupIndex).GetRoutineContainer(Handle) != nullptr;
	}

	/**
	* 
	* 
	* @param Group
	* @param Handle
	* return
	*/
	FORCEINLINE bool IsCustomRunning(const int32& GroupIndex, const FCsRoutineHandle& Handle) const
	{
		return GetCustomSchedule(GroupIndex).IsRunning(Handle);
	}

#pragma endregion Handle

	// Routine
#pragma region

public:

	/**
	*
	*
	* @param GroupIndex
	* @param Handle
	* return
	*/
	FORCEINLINE FCsRoutine* GetCustomRoutine(const int32& GroupIndex, const FCsRoutineHandle& Handle) const
	{
		return GetCustomSchedule(GroupIndex).GetRoutine(Handle);
	}

#pragma endregion Routine

#pragma endregion Custom
};