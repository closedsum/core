// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/Resource/CsManager_ResourceValueType.h"
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/FX/Payload/CsFXPooledPayload.h"
#include "Managers/FX/Actor/CsFXActorPooled.h"
#include "Managers/FX/Actor/CsSettings_Manager_FX_Actor.h"
#include "CsManager_FX_Actor.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerFXActor_OnSpawn, const FECsFX&, Type, TScriptInterface<ICsFXActorPooled>, FXActor);

#pragma endregion Delegates

// Internal
#pragma region

class ICsFXActorPooled;

class CSCORE_API FCsManager_FX_Actor_Internal : public TCsManager_PooledObject_Map<ICsFXActorPooled, FCsFXActorPooled, ICsFXPooledPayload, FECsFX>
{
private:

	typedef TCsManager_PooledObject_Map<ICsFXActorPooled, FCsFXActorPooled, ICsFXPooledPayload, FECsFX> Super;

public:

	FCsManager_FX_Actor_Internal();

	FORCEINLINE virtual const FString& KeyTypeToString(const FECsFX& Type) override
	{
		return Type.GetName();
	}
};

#pragma endregion Internal

class ICsGetManagerFXActor;
class ICsData_FX;
class UDataTable;

UCLASS()
class CSCORE_API UCsManager_FX_Actor : public UObject
{
	GENERATED_UCLASS_BODY()

public:	

// Singleton
#pragma region
public:

	static UCsManager_FX_Actor* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_FX_Actor> ManagerFXActorClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerFXActor* Get_GetManagerFXActor(UObject* InRoot);
	static ICsGetManagerFXActor* GetSafe_GetManagerFXActor(UObject* Object);

	static UCsManager_FX_Actor* GetSafe(UObject* Object);

public:

	static UCsManager_FX_Actor* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_FX_Actor* s_Instance;
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

	FCsSettings_Manager_FX_Actor Settings;

public:

	FORCEINLINE void SetSettings(const FCsSettings_Manager_FX_Actor& InSettings)
	{
		Settings = InSettings;
	}

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of fx actors. */
	FCsManager_FX_Actor_Internal Internal;
	
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
	void InitInternal(const FCsManager_FX_Actor_Internal::FCsManagerPooledObjectMapParams& Params);

	virtual void Clear();

	// Pool
#pragma region
public:

	/**
	* 
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const FECsFX& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TBaseDelegate<FCsFXActorPooled*, const FECsFX&>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsFXActorPooled* ConstructContainer(const FECsFX& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void, const FCsFXActorPooled*>& GetOnConstructObject_Event(const FECsFX& Type);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	void OnAddToPool(const FECsFX& Type, const FCsFXActorPooled* Object);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsFXActorPooled.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsFXActorPooled.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToPool(const FECsFX& Type, ICsFXActorPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsFXActorPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToPool(const FECsFX& Type, const FCsFXActorPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsFXActorPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToPool(const FECsFX& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsFXActorPooled.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsFXActorPooled.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToAllocatedObjects(const FECsFX& Type, ICsFXActorPooled* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsFXActorPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToAllocatedObjects(const FECsFX& Type, ICsFXActorPooled* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsFXActorPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToAllocatedObjects(const FECsFX& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsFXActorPooled.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsFXActorPooled*>& GetPool(const FECsFX& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsFXActorPooled.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsFXActorPooled*>& GetAllocatedObjects(const FECsFX& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsFX& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsFX& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsFX& Type);

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
	*				Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindObject(const FECsFX& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsFXActorPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindObject(const FECsFX& Type, ICsFXActorPooled* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsFXActorPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindObject(const FECsFX& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindSafeObject(const FECsFX& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindSafeObject(const FECsFX& Type, ICsFXActorPooled* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindSafeObject(const FECsFX& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsFX CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsFX& Type);

	void OnUpdate_Object(const FECsFX& Type, const FCsFXActorPooled* Object);

	void OnPostUpdate_Pool(const FECsFX& Type);

#pragma endregion Update

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const FECsFX& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual ICsFXPooledPayload* ConstructPayload(const FECsFX& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPooledObjectPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsFXPooledPayload.
	*/
	ICsFXPooledPayload* AllocatePayload(const FECsFX& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPooledObjectPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsFXPooledPayload.
	*/
	template<typename PayloadTypeImpl>
	FORCEINLINE PayloadTypeImpl* AllocatePayload(const FECsFX& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(Type);
	}

	//virtual ICsFXPooledPayload* ScriptAllocatePayload(const FECsFX& Type, const FCsScriptProjectilePayload& ScriptPayload);

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
	const FCsFXActorPooled* Spawn(const FECsFX& Type, ICsFXPooledPayload* Payload);

	/**
	*
	*/
	//virtual const FCsFXActorPooled* ScriptSpawn(const FECsFX& Type, const FCsScriptProjectilePayload& ScriptPayload);

	/**
	* Delegate type after an FX Actor object has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsFX& /*Type*/, const FCsFXActorPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerFXActor_OnSpawn OnSpawn_ScriptEvent;

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
	virtual bool Destroy(const FECsFX& Type, ICsFXActorPooled* Object);

	virtual bool Destroy(ICsFXActorPooled* Object);

	/**
	* Delegate type after an FX Actor object has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsFX& /*Type*/, const FCsFXActorPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& /*Str*/);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsFXActorPooled* Object);

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

	// ICsFXActorPooled
#pragma region
public:

#pragma endregion ICsFXActorPooled

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

// Data
#pragma region
protected:

	TMap<FName, ICsData_FX*> DataMap;

public:

	virtual void PopulateDataMapFromSettings();

	virtual void DeconstructData(ICsData_FX* Data);

	ICsData_FX* GetData(const FName& Name);

private:

	UPROPERTY()
	TMap<FECsFX, UClass*> ClassMap;

	UPROPERTY()
	TArray<UDataTable*> DataTables;

#pragma endregion Data
};