// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Event/CsResource_StatusEffectEvent.h"
#include "UniqueObject/CsTypes_UniqueObject.h"
#include "Types/CsTypes_StatusEffect.h"
// Interface
#include "CsReceiveStatusEffect.h"
// StatusEffect
#include "CsResource_StatusEffect.h"

#include "CsCoordinator_StatusEffect.generated.h"

class ICsGetCoordinatorStatusEffect;

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)
// NCsStatusEffect::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, FInterfaceMap)

// NCsData::NManager::NHandler::TData
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData;
		}
	}
}

UCLASS()
class CSSE_API UCsCoordinator_StatusEffect : public UObject
{
	GENERATED_UCLASS_BODY()

#define StatusEffectType NCsStatusEffect::IStatusEffect

#define EventType NCsStatusEffect::NEvent::IEvent
#define EventResourceType NCsStatusEffect::NEvent::FResource
#define EventManagerType NCsStatusEffect::NEvent::FManager

#define DataHandlerType NCsData::NManager::NHandler::TData
#define DataType NCsStatusEffect::NData::IData
#define DataInterfaceMapType NCsStatusEffect::NData::FInterfaceMap

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsCoordinator_StatusEffect* Get(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsCoordinator_StatusEffect* Get(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	FORCEINLINE static T* Get(const UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsCoordinator_StatusEffect* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsCoordinator_StatusEffect* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	static bool IsValid(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static bool IsValid(const UObject* InRoot = nullptr)
	{
		return s_Instance != nullptr;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsCoordinator_StatusEffect> CoordinatorStatusEffectClass, UObject* InOuter = nullptr);
	
	static void Shutdown(const UObject* InRoot = nullptr);
	static bool HasShutdown(const UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetCoordinatorStatusEffect* Get_GetCoordinatorStatusEffect(const UObject* InRoot);
	static ICsGetCoordinatorStatusEffect* GetSafe_GetCoordinatorStatusEffect(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(const UObject* InRoot);

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

// StatusEffect
#pragma region

#define SeResourceType NCsStatusEffect::FResource
#define SeManagerType NCsStatusEffect::FManager

protected:

	TArray<SeManagerType> Manager_StatusEffects;

	virtual StatusEffectType* ConstructStatusEffect(const FECsStatusEffectImpl& Type);

public:

	SeResourceType* AllocateStatusEffect(const FECsStatusEffectImpl& Type);

	void DeallocateStatusEffect(const FString& Context, const FECsStatusEffectImpl& Type, SeResourceType* StatusEffect);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Value
	* return
	*/
	virtual const FECsStatusEffectImpl& GetStatusEffectImplType(const FString& Context, const StatusEffectType* StatusEffect);

	SeResourceType* CreateCopyOfStatusEffect(const FString& Context, const StatusEffectType* StatusEffect);

	SeResourceType* CreateCopyOfStatusEffect(const FString& Context, const SeResourceType* StatusEffect);

#undef SeResourceType
#undef SeManagerType

#pragma endregion StatusEffect

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

	EventResourceType* CreateEvent(const FString& Context, const FECsStatusEffect& Type, DataType* Data, UObject* Instigator, UObject* Causer, UObject* Receiver);

private:

	TArray<FCsReceiveStatusEffect> Local_Receivers;

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
	void ProcessStatusEffectEventContainer(const EventResourceType* EventContainer);

	/**
	*
	*
	* @param Event
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnEvent, const EventType* /*Event*/);

	/** */
	FOnEvent OnEvent_Event;

#pragma endregion Event

// Data
#pragma region
protected:

	DataHandlerType<DataType, FCsData_StatusEffectPtr, DataInterfaceMapType>* DataHandler;

	virtual void ConstructDataHandler();

public:

	FORCEINLINE DataHandlerType<DataType, FCsData_StatusEffectPtr, DataInterfaceMapType>* GetDataHandler() const { return DataHandler; }

	/**
	* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Name of the character type.
	*
	* @param Name	Name of the Status Effect.
	* return		Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
	*/
	DataType* GetData(const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Name of the character type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Status Effect.
	* return			Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FName& Name);

	/**
	* Safely get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Name of the weapon type.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Status Effect.
	* return			Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Type.
	*
	* @param Type	Status Effect type.
	* return		Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
	*/
	DataType* GetData(const FECsStatusEffect& Type);

	/**
	* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Status Effect type.
	* return			Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FECsStatusEffect& Type);

	/**
	* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Type.
	*
	* @param Context	The calling context.
	* @param Type		Status Effect type.
	* return			Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FECsStatusEffect& Type);

	void ProcessDataChecked(const FString& Context, const FECsStatusEffect& Type, DataType* Data, UObject* Instigator, UObject* Causer, UObject* Receiver);

	void ProcessDataChecked(const FString& Context, const FECsStatusEffect& Type, UObject* Instigator, UObject* Causer, UObject* Receiver);

#pragma endregion Data

// Log
#pragma region
public:

	bool LogEvent(const EventType* Event);

#pragma endregion Log

#undef StatusEffectType

#undef EventType
#undef EventResourceType
#undef EventManagerType

#undef DataHandlerType
#undef DataType
#undef DataInterfaceMapType
};