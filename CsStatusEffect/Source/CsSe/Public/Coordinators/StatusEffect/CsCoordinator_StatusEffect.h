// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "Event/CsResource_StatusEffectEvent.h"
#include "UniqueObject/CsTypes_UniqueObject.h"
#include "CsTypes_StatusEffect.h"
#include "CsReceiveStatusEffect.h"

#include "CsCoordinator_StatusEffect.generated.h"

class ICsGetCoordinatorStatusEffect;

UCLASS()
class CSSE_API UCsCoordinator_StatusEffect : public UObject
{
	GENERATED_UCLASS_BODY()

#define EventType NCsStatusEffect::NEvent::IEvent
#define EventResourceType NCsStatusEffect::NEvent::FResource
#define EventManagerType NCsStatusEffect::NEvent::FManager

// Singleton
#pragma region
public:

	static UCsCoordinator_StatusEffect* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsCoordinator_StatusEffect> CoordinatorStatusEffectClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetCoordinatorStatusEffect* Get_GetCoordinatorStatusEffect(UObject* InRoot);
	static ICsGetCoordinatorStatusEffect* GetSafe_GetCoordinatorStatusEffect(UObject* Object);

	static UCsCoordinator_StatusEffect* GetSafe(UObject* Object);

public:

	static UCsCoordinator_StatusEffect* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

	virtual void CleanUp();

private:
	// Singleton data
	static UCsCoordinator_StatusEffect* s_Instance;
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

// Receive Status Effect
#pragma region
protected:

	TMap<FCsUniqueObjectId, ICsReceiveStatusEffect*> ReceiveStatusEffectMap;

public:

	void Add(ICsReceiveStatusEffect* Object);

	void Remove(ICsReceiveStatusEffect* Object);

#pragma endregion Receive Status Effect

// Event
#pragma region
protected:

	TArray<EventManagerType> Manager_Events;

	virtual EventType* ConstructEvent(const FECsStatusEffectEvent& Type);

public:

	/**
	*
	*
	* return
	*/
	EventResourceType* AllocateEvent(const FECsStatusEffectEvent& Type);

	/**
	* Get the type (interface) of the Event.
	*
	* @param Context	The calling context.
	* @param Event		Event of type: NCsStatusEffect::NEvent::IEvent.
	* return			Type of StatusEffectEvent.
	*/
	virtual const FECsStatusEffectEvent& GetEventType(const FString& Context, const EventType* Event);

	/**
	* Get the type (interface) of the Event.
	*
	* @param Context	The calling context.
	* @param Event		Container for event of type: NCsStatusEffect::NEvent::IEvent.
	* return			Type of StatusEffectEvent.
	*/
	virtual const FECsStatusEffectEvent& GetEventType(const FString& Context, const EventResourceType* Event);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Event
	*/
	void DeallocateEvent(const FString& Context, EventResourceType* Event);

	virtual bool CopyEvent(const FString& Context, const EventType* From, EventType* To);

	EventResourceType* CreateCopyOfEvent(const FString& Context, const EventType* Event);

	EventResourceType* CreateCopyOfEvent(const FString& Context, const EventResourceType* Event);

private:

	TArray<FCsReceiveStatusEffect> Local_Receivers;
	TArray<EventResourceType*> Local_Events;

public:

	/**
	* Process the Event
	*
	* @param Event	Event of type: NCsStatusEffect::NEvent::IEvent.
	*/
	void ProcessStatusEffectEvent(const EventType* Event);

	/**
	* Process the Event
	*
	* @param Event	Container for event of type: NCsStatusEffect::NEvent::IEvent.
	*/
	void ProcessStatusEffectEventContainer(const EventResourceType* Event);

	/**
	*
	*
	* @param Event
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnEvent, const EventType* /*Event*/);

	/** */
	FOnEvent OnEvent_Event;

#pragma endregion Event

// Log
#pragma region
public:

	//void LogEventPoint(const NCsStatusEffect::NEvent::IEvent* Event);

#pragma endregion Log

#undef EventType
#undef EventResourceType
#undef EventManagerType
};