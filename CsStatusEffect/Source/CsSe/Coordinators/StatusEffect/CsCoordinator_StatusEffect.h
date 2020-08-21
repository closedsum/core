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

	TArray<FCsManager_StatusEffectEvent> Manager_Events;

	virtual ICsStatusEffectEvent* ConstructEvent(const FECsStatusEffectEvent& Type);

public:

	/**
	*
	*
	* return
	*/
	FCsResource_StatusEffectEvent* AllocateEvent(const FECsStatusEffectEvent& Type);

	/**
	* Get the type (interface) of the Event.
	*
	* @param Event	Event of type: ICsStatusEffectEvent.
	* return		Type of StatusEffectEvent.
	*/
	const FECsStatusEffectEvent& GetTypeFromEvent(ICsStatusEffectEvent* Event);

	/**
	* Get the type (interface) of the Event.
	*
	* @param Event	Container for event of type: ICsStatusEffectEvent.
	* return		Type of StatusEffectEvent.
	*/
	const FECsStatusEffectEvent& GetTypeFromEvent(FCsResource_StatusEffectEvent* Event);

	/**
	*
	*
	* @param Event
	*/
	void DeallocateEvent(FCsResource_StatusEffectEvent* Event);

private:

	TArray<FCsReceiveStatusEffect> Local_Receivers;

public:

	/**
	* Process the Event
	*
	* @param Event	Event of type: ICsStatusEffectEvent.
	*/
	void ProcessStatusEffectEvent(const ICsStatusEffectEvent* Event);

	/**
	* Process the Event
	*
	* @param Event	Container for event of type: ICsStatusEffectEvent.
	*/
	void ProcessStatusEffectEventContainer(const FCsResource_StatusEffectEvent* Event);

	/**
	*
	*
	* @param Event
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnEvent, const ICsStatusEffectEvent* /*Event*/);

	/** */
	FOnEvent OnEvent_Event;

#pragma endregion Event

// Log
#pragma region
public:

	//void LogEventPoint(const ICsStatusEffectEvent* Event);

#pragma endregion Log
};