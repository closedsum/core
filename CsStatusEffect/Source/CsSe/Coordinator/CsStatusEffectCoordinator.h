// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
#include "Event/CsStatusEffectEvent.h"
#include "UniqueObject/CsTypes_UniqueObject.h"
#include "CsTypes_StatusEffect.h"
#include "CsStatusEffectCoordinator.generated.h"

// Structs
#pragma region

	// StatusEffect

struct CSSE_API FCsResource_StatusEffectEvent : public TCsResourceContainer<ICsStatusEffectEvent>
{
};

struct CSSE_API FCsManager_StatusEffectEvent : public TCsManager_ResourcePointerType_Fixed<ICsStatusEffectEvent, FCsResource_StatusEffectEvent, 0>
{
};

#pragma endregion Structs

class ICsGetStatusEffectCoordinator;
class ICsReceiveStatusEffect;

UCLASS()
class CSSE_API UCsStatusEffectCoordinator : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsStatusEffectCoordinator* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsStatusEffectCoordinator> StatusEffectCoordinatorClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetStatusEffectCoordinator* Get_GetStatusEffectCoordinator(UObject* InRoot);
	static ICsGetStatusEffectCoordinator* GetSafe_GetStatusEffectCoordinator(UObject* Object);

	static UCsStatusEffectCoordinator* GetSafe(UObject* Object);

public:

	static UCsStatusEffectCoordinator* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsStatusEffectCoordinator* s_Instance;
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
	*
	*
	* @param Event
	*/
	void OnEvent(const ICsStatusEffectEvent* Event);

	/**
	*
	*
	* @param Event
	*/
	void OnEventContainer(const FCsResource_StatusEffectEvent* Event);

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