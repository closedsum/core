// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/Resource/CsManager_ResourceValueType.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"
#include "Managers/UserWidget/CsUserWidgetPooled.h"
#include "Managers/UserWidget/CsSettings_Manager_UserWidget.h"
#include "CsManager_UserWidget.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerUserWidget_OnSpawn, const FECsUserWidgetPooled&, Type, TScriptInterface<ICsUserWidgetPooled>, UserWidgetPooled);

#pragma endregion Delegates

// Internal
#pragma region

class ICsUserWidgetPooled;

class CSUI_API FCsManager_UserWidget_Internal : public TCsManager_PooledObject_Map<ICsUserWidgetPooled, FCsUserWidgetPooled, ICsPayload_UserWidget, FECsUserWidgetPooled>
{
private:

	typedef TCsManager_PooledObject_Map<ICsUserWidgetPooled, FCsUserWidgetPooled, ICsPayload_UserWidget, FECsUserWidgetPooled> Super;

public:

	FCsManager_UserWidget_Internal();

	FORCEINLINE virtual const FString& KeyTypeToString(const FECsUserWidgetPooled& Type) override
	{
		return Type.GetName();
	}
};

#pragma endregion Internal

class ICsGetManagerUserWidget;
class ICsData_FX;
class UDataTable;

template<typename InterfacePooledContainerType, typename InterfaceUStructContainerType, typename EnumType>
class TCsManager_PooledObject_ClassHandler;

template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
class TCsManager_PooledObject_DataHandler;

class ICsData_UserWidget;
struct FCsData_UserWidgetInterfaceMap;

UCLASS()
class CSUI_API UCsManager_UserWidget : public UObject
{
	GENERATED_UCLASS_BODY()

public:	

// Singleton
#pragma region
public:

	static UCsManager_UserWidget* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_UserWidget> ManagerFXActorClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerUserWidget* Get_GetManagerUserWidget(UObject* InRoot);
	static ICsGetManagerUserWidget* GetSafe_GetManagerUserWidget(UObject* Object);

	static UCsManager_UserWidget* GetSafe(UObject* Object);

public:

	static UCsManager_UserWidget* GetFromWorldContextObject(const UObject* WorldContextObject);

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
	static UCsManager_UserWidget* s_Instance;
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

	FCsSettings_Manager_UserWidget Settings;

public:

	FORCEINLINE void SetSettings(const FCsSettings_Manager_UserWidget& InSettings)
	{
		Settings = InSettings;
	}

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of fx actors. */
	FCsManager_UserWidget_Internal Internal;
	
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
	void InitInternal(const FCsManager_UserWidget_Internal::FCsManagerPooledObjectMapParams& Params);

	virtual void Clear();

	// Pool
#pragma region
public:

	/**
	* 
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const FECsUserWidgetPooled& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TBaseDelegate<FCsUserWidgetPooled*, const FECsUserWidgetPooled&>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsUserWidgetPooled* ConstructContainer(const FECsUserWidgetPooled& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void, const FCsUserWidgetPooled*, const FCsManagerPooledObjectConstructParams&>& GetOnConstructObject_Event(const FECsUserWidgetPooled& Type);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	void OnAddToPool(const FECsUserWidgetPooled& Type, const FCsUserWidgetPooled* Object);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsUserWidgetPooled.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsUserWidgetPooled.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToPool(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsUserWidgetPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToPool(const FECsUserWidgetPooled& Type, const FCsUserWidgetPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsUserWidgetPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToPool(const FECsUserWidgetPooled& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsUserWidgetPooled.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsUserWidgetPooled.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToAllocatedObjects(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsUserWidgetPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToAllocatedObjects(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsUserWidgetPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToAllocatedObjects(const FECsUserWidgetPooled& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsUserWidgetPooled.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsUserWidgetPooled*>& GetPool(const FECsUserWidgetPooled& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsUserWidgetPooled.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsUserWidgetPooled*>& GetAllocatedObjects(const FECsUserWidgetPooled& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsUserWidgetPooled& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsUserWidgetPooled& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsUserWidgetPooled& Type);

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
	*				Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindObject(const FECsUserWidgetPooled& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsUserWidgetPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindObject(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsUserWidgetPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindObject(const FECsUserWidgetPooled& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindSafeObject(const FECsUserWidgetPooled& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindSafeObject(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindSafeObject(const FECsUserWidgetPooled& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsUserWidgetPooled CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsUserWidgetPooled& Type);

	void OnUpdate_Object(const FECsUserWidgetPooled& Type, const FCsUserWidgetPooled* Object);

	void OnPostUpdate_Pool(const FECsUserWidgetPooled& Type);

#pragma endregion Update

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const FECsUserWidgetPooled& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual ICsPayload_UserWidget* ConstructPayload(const FECsUserWidgetPooled& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPayload_PooledObject.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsPayload_UserWidget.
	*/
	ICsPayload_UserWidget* AllocatePayload(const FECsUserWidgetPooled& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPayload_PooledObject.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsPayload_UserWidget.
	*/
	template<typename PayloadTypeImpl>
	FORCEINLINE PayloadTypeImpl* AllocatePayload(const FECsUserWidgetPooled& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(Type);
	}

	//virtual ICsPayload_UserWidget* ScriptAllocatePayload(const FECsUserWidgetPooled& Type, const FCsScriptProjectilePayload& ScriptPayload);

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
	const FCsUserWidgetPooled* Spawn(const FECsUserWidgetPooled& Type, ICsPayload_UserWidget* Payload);

	/**
	*
	*/
	//virtual const FCsUserWidgetPooled* ScriptSpawn(const FECsUserWidgetPooled& Type, const FCsScriptProjectilePayload& ScriptPayload);

	/**
	* Delegate type after an FX Actor object has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsUserWidgetPooled& /*Type*/, const FCsUserWidgetPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerUserWidget_OnSpawn OnSpawn_ScriptEvent;

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
	virtual bool Destroy(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object);

	virtual bool Destroy(ICsUserWidgetPooled* Object);

	/**
	* Delegate type after an FX Actor object has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsUserWidgetPooled& /*Type*/, const FCsUserWidgetPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& /*Str*/);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsUserWidgetPooled* Object);

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

	// ICsUserWidgetPooled
#pragma region
public:

#pragma endregion ICsUserWidgetPooled

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

	// ICsOnConstructObject
#pragma region

	/** Delegate to execute after an object has been constructed.
		 The object implements a script interface of type: ICsOnConstructObject. */
	FCsPooledObject::FScript_OnConstructObject Script_OnConstructObject_Impl;

#pragma endregion 

#pragma endregion Script

// Class
#pragma region
protected:

	//TCsManager_PooledObject_ClassHandler<FCsUserWidgetPtr, FCsUserWidgetPtr, FECsUserWidgetClass>* ClassHandler;

	//TCsManager_PooledObject_ClassHandler<FCsUserWidgetPooled, FCsUserWidgetPtr, FECsUserWidgetClass>* ClassHandler;

	//virtual void ConstructClassHandler();

public:

	/**
	* Get the UserWidget container (Interface (ICsUserWidgetPooled), UObject, and / or UClass) associated
	* with the user widget Type.
	*
	* @param Type	Type of the user widget.
	* return		UserWidget container (Interface (ICsUserWidgetPooled), UObject, and / or UClass).
	*/
	FCsUserWidgetPooled* GetUserWidget(const FECsUserWidgetPooled& Type);

	/**
	* Get the UserWidget container (Interface (ICsUserWidgetPooled), UObject, and / or UClass) associated
	* with the user widget class Type.
	*
	* @param Type	Class type of the UserWidget.
	* return		UserWidget container (Interface (ICsUserWidgetPooled), UObject, and / or UClass).
	*/
	FCsUserWidgetPooled* GetUserWidget(const FECsUserWidgetPooledClass& Type);

	/**
	* Get the UserWidget container (Interface (ICsUserWidgetPooled), UObject, and / or UClass) associated
	* with the user widget class Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Class type of the user widget.
	* return			UserWidget container (Interface (ICsUserWidgetPooled), UObject, and / or UClass).
	*/
	FCsUserWidgetPooled* GetUserWidgetChecked(const FString& Context, const FECsUserWidgetPooledClass& Type);

#pragma endregion Class

// Data
#pragma region
protected:

#pragma endregion Data
};