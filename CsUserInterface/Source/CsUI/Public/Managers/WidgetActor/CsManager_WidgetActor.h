// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/WidgetActor/CsWidgetActor.h"
#include "Managers/WidgetActor/CsWidgetActorPooled.h"
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActor.h"
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"
#include "Managers/WidgetActor/CsSettings_Manager_WidgetActor.h"

#include "CsManager_WidgetActor.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerWidgetActor_OnSpawn, const FECsWidgetActor&, Type, TScriptInterface<ICsWidgetActor>, WidgetActor);

#pragma endregion Delegates

// Internal
#pragma region

class ICsWidgetActor;

#define ManagerMapType NCsPooledObject::NManager::TTMap
#define PayloadType NCsWidgetActor::NPayload::IPayload

namespace NCsWidgetActor
{
	class CSUI_API FManager : public ManagerMapType<ICsWidgetActor, FCsWidgetActorPooled, PayloadType, FECsWidgetActor>
	{
	private:

		typedef ManagerMapType<ICsWidgetActor, FCsWidgetActorPooled, PayloadType, FECsWidgetActor> Super;

	public:

		FManager();

		FORCEINLINE virtual const FString& KeyTypeToString(const FECsWidgetActor& Type) const override
		{
			return Type.GetName();
		}

		FORCEINLINE virtual bool IsValidKey(const FECsWidgetActor& Type) const override
		{
			return EMCsWidgetActor::Get().IsValidEnum(Type);
		}
	};

#undef ManagerMapType
#undef PayloadType
}

#pragma endregion Internal

class ICsGetManagerWidgetActor;
class UDataTable;

// NCsPooledObject::NManager::NHandler::TClass
namespace NCsPooledObject {
	namespace NManager {
		namespace NHandler {
			template<typename InterfacePooledContainerType, typename InterfaceUStructContainerType, typename EnumType>
			class TClass; } } }
// NCsPooledObject::NManager::NHandler::TData
namespace NCsPooledObject {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData; } } }

// NCsWidgetActor::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWidgetActor, NData, IData)
// NCsWidgetActor::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWidgetActor, NData, FInterfaceMap)

UCLASS()
class CSUI_API UCsManager_WidgetActor : public UObject
{
	GENERATED_UCLASS_BODY()

#define ManagerType NCsWidgetActor::FManager
#define ManagerParamsType NCsWidgetActor::FManager::FParams
#define PayloadType NCsWidgetActor::NPayload::IPayload
#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
#define ClassHandlerType NCsPooledObject::NManager::NHandler::TClass
#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
#define DataType NCsWidgetActor::NData::IData
#define DataInterfaceMapType NCsWidgetActor::NData::FInterfaceMap

public:	

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_WidgetActor* Get(UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_WidgetActor* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR
	
	template<typename T>
	FORCEINLINE static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static bool IsValid(UObject* InRoot = nullptr);
#else
	FORCEINLINE static bool IsValid(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? false : s_Instance != nullptr;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_WidgetActor> ManagerWidgetActorClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
	static bool HasShutdown(UObject* InRoot = nullptr);
#else
	FORCEINLINE static bool HasShutdown(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? true : s_Instance == nullptr;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
protected:

	static ICsGetManagerWidgetActor* Get_GetManagerWidgetActor(UObject* InRoot);
	static ICsGetManagerWidgetActor* GetSafe_GetManagerWidgetActor(UObject* Object);

	static UCsManager_WidgetActor* GetSafe(UObject* Object);

public:

	static UCsManager_WidgetActor* GetFromWorldContextObject(const UObject* WorldContextObject);

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
	static UCsManager_WidgetActor* s_Instance;
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

// Settings
#pragma region
protected:

	FCsSettings_Manager_WidgetActor Settings;

	/** */
	TArray<FECsWidgetActor> TypeMapArray;

public:

	FORCEINLINE void SetSettings(const FCsSettings_Manager_WidgetActor& InSettings)
	{
		Settings = InSettings;
	}

	/**
	* If SET,
	* - Get the type this WidgetActor has been mapped to for pooling.
	*   i.e. If the widget actor is completely data driven, then many widget actors could share
	*   the same class.
	* If NOT set,
	* - Return the same type.
	*
	* @param Type
	* return WidgetActor Type 
	*/
	FORCEINLINE const FECsWidgetActor& GetTypeFromTypeMap(const FECsWidgetActor& Type)
	{
		return TypeMapArray[Type.GetValue()];
	}

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of fx actors. */
	ManagerType Internal;
	
	/**
	* Setup the internal manager for handling the pool of projectiles.
	*/
	virtual void SetupInternal();

public:

	/**
	*
	*/
	void InitInternalFromSettings();

	/**
	*
	*
	* @param Params
	*/
	void InitInternal(const ManagerParamsType& Params);

	virtual void Clear();

	// Pool
#pragma region
public:

	/**
	* 
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const FECsWidgetActor& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TDelegate<FCsWidgetActorPooled*(const FECsWidgetActor&)>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsWidgetActorPooled* ConstructContainer(const FECsWidgetActor& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void(const FCsWidgetActorPooled*, const ConstructParamsType&)>& GetOnConstructObject_Event(const FECsWidgetActor& Type);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	void OnAddToPool(const FECsWidgetActor& Type, const FCsWidgetActorPooled* Object);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsWidgetActor.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsWidgetActor.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* AddToPool(const FECsWidgetActor& Type, ICsWidgetActor* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsWidgetActor.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsWidgetActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* AddToPool(const FECsWidgetActor& Type, const FCsWidgetActorPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsWidgetActor or the UClass
	*  associated with the Object have ImplementsInterface(UCsWidgetActor::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsWidgetActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* AddToPool(const FECsWidgetActor& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsWidgetActor.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsWidgetActor.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* AddToAllocatedObjects(const FECsWidgetActor& Type, ICsWidgetActor* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsWidgetActor.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsWidgetActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* AddToAllocatedObjects(const FECsWidgetActor& Type, ICsWidgetActor* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsWidgetActor or the UClass
	*  associated with the Object have ImplementsInterface(UCsWidgetActor::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsWidgetActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* AddToAllocatedObjects(const FECsWidgetActor& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsWidgetActor.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsWidgetActorPooled*>& GetPool(const FECsWidgetActor& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsWidgetActor.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsWidgetActorPooled*>& GetAllocatedObjects(const FECsWidgetActor& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsWidgetActor& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsWidgetActor& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsWidgetActor& Type);

	// Find
#pragma region
public:

	/**
	* Find the container holding reference to a pooled object from the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* FindObject(const FECsWidgetActor& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsWidgetActor.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsWidgetActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* FindObject(const FECsWidgetActor& Type, ICsWidgetActor* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsWidgetActor or the UClass
	*  associated with the Object have ImplementsInterface(UCsWidgetActor::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsWidgetActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* FindObject(const FECsWidgetActor& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* FindSafeObject(const FECsWidgetActor& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsWidgetActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsWidgetActor.
	*/
	const FCsWidgetActorPooled* FindSafeObject(const FECsWidgetActor& Type, ICsWidgetActor* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsWidgetActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsFXActorPooled.
	*/
	const FCsWidgetActorPooled* FindSafeObject(const FECsWidgetActor& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsWidgetActor CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsWidgetActor& Type);

	void OnUpdate_Object(const FECsWidgetActor& Type, const FCsWidgetActorPooled* Object);

	void OnPostUpdate_Pool(const FECsWidgetActor& Type);

#pragma endregion Update

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const FECsWidgetActor& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual PayloadType* ConstructPayload(const FECsWidgetActor& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsWidgetActor::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsWidgetActor::NPayload::IPayload.
	*/
	PayloadType* AllocatePayload(const FECsWidgetActor& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsWidgetActor::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsWidgetActor::NPayload::IPayload.
	*/
	template<typename PayloadTypeImpl>
	FORCEINLINE PayloadTypeImpl* AllocatePayload(const FECsWidgetActor& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(Type);
	}

#pragma endregion Payload

	// Spawn
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Payload
	*/
	const FCsWidgetActorPooled* Spawn(const FECsWidgetActor& Type, PayloadType* Payload);

	/**
	* Delegate type after an Widget Actor object has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsWidgetActor& /*Type*/, const FCsWidgetActorPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerWidgetActor_OnSpawn OnSpawn_ScriptEvent;

#pragma endregion Spawn

	// Destroy
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	virtual bool Destroy(const FECsWidgetActor& Type, ICsWidgetActor* Object);

	virtual bool Destroy(ICsWidgetActor* Object);

	/**
	* Delegate type after an FX Actor object has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsWidgetActor& /*Type*/, const FCsWidgetActorPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& /*Str*/);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsWidgetActorPooled* Object);

#pragma endregion Log

#pragma endregion Internal

// Pool
#pragma region
protected:

	UPROPERTY()
	TArray<UObject*> Pool;

#pragma endregion Pool

// Script
#pragma region
public:

	// ICsWidgetActor
#pragma region
public:

#pragma endregion ICsWidgetActor

	// ICsPooledObject
#pragma region
public:

	/** Delegate for getting the Cache associated with a Pooled Object. 
		 The Pooled Object implements a script interface of type: ICsPooledObject. */
	FCsPooledObject::FScript_GetCache Script_GetCache_Impl;

	/** Delegate called after allocating a Pooled Object. 
		 The Pooled Object implements a script interface of type: ICsPooledObject. */
	FCsPooledObject::FScript_Allocate Script_Allocate_Impl;

	/** Delegate called after allocating a Pooled Object. 
		 The Pooled Object implements a script interface of type: ICsPooledObject.*/
	FCsPooledObject::FScript_Deallocate Script_Deallocate_Impl;

#pragma endregion ICsPooledObject

	// ICsUpdate
#pragma region
public:

	/** Delegate for updating a Pooled Object.
		The Pooled Object implements a script interface of type: ICsPooledObject. */
	FCsPooledObject::FScript_Update Script_Update_Impl;

#pragma endregion ICsUpdate

#pragma endregion Script

// Class
#pragma region
protected:

	ClassHandlerType<FCsWidgetActorPooled, FCsWidgetActorPtr, FECsWidgetActorClass>* ClassHandler;

	virtual void ConstructClassHandler();

public:

	/**
	* Get the WidgetActor container (Interface (ICsWidgetActor), UObject, and / or UClass) associated
	* with the widget actor Type.
	*
	* @param Type	Type of the widget actor.
	* return		WidgetActor container (Interface (ICsWidgetActor), UObject, and / or UClass).
	*/
	FCsWidgetActorPooled* GetWidgetActor(const FECsWidgetActor& Type);

	/**
	* Get the WidgetActor container (Interface (ICsWidgetActor), UObject, and / or UClass) associated
	* with the widget actor class Type.
	*
	* @param Type	Class type of the WidgetActor.
	* return		WidgetActor container (Interface (ICsWidgetActor), UObject, and / or UClass).
	*/
	FCsWidgetActorPooled* GetWidgetActor(const FECsWidgetActorClass& Type);

	/**
	* Get the WidgetActor container (Interface (ICsWidgetActor), UObject, and / or UClass) associated
	* with the widget actor class Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Class type of the widget actor.
	* return			WidgetActor container (Interface (ICsWidgetActor), UObject, and / or UClass).
	*/
	FCsWidgetActorPooled* GetWidgetActorChecked(const FString& Context, const FECsWidgetActorClass& Type);

#pragma endregion Class

// Data
#pragma region
protected:

	DataHandlerType<DataType, FCsData_WidgetActorPtr, DataInterfaceMapType>* DataHandler;

	virtual void ConstructDataHandler();

public:

	/**
	* Get the Data (implements interface: DataType (NCsWidgetActor::NData::IData)) associated with Name of the character type.
	*
	* @param Name	Name of the WidgetActor.
	* return		Data that implements the interface: DataType (NCsWidgetActor::NData::IData).
	*/
	DataType* GetData(const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsWidgetActor::NData::IData)) associated with Type.
	*
	* @param Type	WidgetActor type.
	* return		Data that implements the interface: DataType (NCsWidgetActor::NData::IData).
	*/
	DataType* GetData(const FECsWidgetActor& Type);

	/**
	* Get the Data (implements interface: DataType (NCsWidgetActor::NData::IData)) associated with Name of the character type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Name		Name of the WidgetActor.
	* return			Data that implements the interface: DataType (NCsWidgetActor::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsWidgetActor::NData::IData)) associated with Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Character type.
	* return			Data that implements the interface: DataType (NCsWidgetActor::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FECsWidgetActor& Type);

#pragma endregion Data

#undef ManagerType
#undef ManagerParamsType
#undef PayloadType
#undef ConstructParamsType
#undef ClassHandlerType
#undef DataHandlerType
#undef DataType
#undef DataInterfaceMapType
};