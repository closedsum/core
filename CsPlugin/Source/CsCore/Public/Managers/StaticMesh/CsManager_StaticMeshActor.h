// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/Resource/CsManager_ResourceValueType.h"
// StaticMeshActor
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"
#include "Managers/StaticMesh/CsStaticMeshActor.h"
#include "Managers/StaticMesh/CsStaticMeshActorPooled.h"
#include "Managers/StaticMesh/CsSettings_Manager_StaticMeshActor.h"

#include "CsManager_StaticMeshActor.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerStaticMeshActor_OnSpawn, const FECsStaticMeshActor&, Type, TScriptInterface<ICsStaticMeshActor>, FXActor);

#pragma endregion Delegates

// Internal
#pragma region

class ICsStaticMeshActor;

class CSCORE_API FCsManager_StaticMeshActor_Internal : public TCsManager_PooledObject_Map<ICsStaticMeshActor, FCsStaticMeshActorPooled, NCsStaticMeshActor::NPayload::IPayload, FECsStaticMeshActor>
{
private:

	typedef TCsManager_PooledObject_Map<ICsStaticMeshActor, FCsStaticMeshActorPooled, NCsStaticMeshActor::NPayload::IPayload, FECsStaticMeshActor> Super;

public:

	FCsManager_StaticMeshActor_Internal();

	FORCEINLINE virtual const FString& KeyTypeToString(const FECsStaticMeshActor& Type) override
	{
		return Type.GetName();
	}
};

#pragma endregion Internal

class ICsGetManagerStaticMeshActor;
class ICsData_StaticMeshActor;
class UDataTable;

UCLASS()
class CSCORE_API UCsManager_StaticMeshActor : public UObject
{
	GENERATED_UCLASS_BODY()

public:	

// Singleton
#pragma region
public:

	static UCsManager_StaticMeshActor* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_StaticMeshActor> ManagerSoundClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerStaticMeshActor* Get_GetManagerStaticMeshActor(UObject* InRoot);
	static ICsGetManagerStaticMeshActor* GetSafe_GetManagerStaticMeshActor(UObject* Object);

	static UCsManager_StaticMeshActor* GetSafe(UObject* Object);

public:

	static UCsManager_StaticMeshActor* GetFromWorldContextObject(const UObject* WorldContextObject);

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
	static UCsManager_StaticMeshActor* s_Instance;
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

	FCsSettings_Manager_StaticMeshActor Settings;

public:

	FORCEINLINE void SetSettings(const FCsSettings_Manager_StaticMeshActor& InSettings)
	{
		Settings = InSettings;
	}

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of sounds. */
	FCsManager_StaticMeshActor_Internal Internal;
	
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
	void InitInternal(const FCsManager_StaticMeshActor_Internal::FCsManagerPooledObjectMapParams& Params);

	virtual void Clear();

	// Pool
#pragma region
public:

	/**
	* 
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const FECsStaticMeshActor& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TBaseDelegate<FCsStaticMeshActorPooled*, const FECsStaticMeshActor&>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsStaticMeshActorPooled* ConstructContainer(const FECsStaticMeshActor& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void, const FCsStaticMeshActorPooled*, const FCsManagerPooledObjectConstructParams&>& GetOnConstructObject_Event(const FECsStaticMeshActor& Type);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	void OnAddToPool(const FECsStaticMeshActor& Type, const FCsStaticMeshActorPooled* Object);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsStaticMeshActor.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsStaticMeshActor.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* AddToPool(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsStaticMeshActor.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsStaticMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* AddToPool(const FECsStaticMeshActor& Type, const FCsStaticMeshActorPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsStaticMeshActor or the UClass
	*  associated with the Object have ImplementsInterface(UCsSoundPooled::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsStaticMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* AddToPool(const FECsStaticMeshActor& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsStaticMeshActor.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsStaticMeshActor.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* AddToAllocatedObjects(const FECsStaticMeshActor& Type, ICsStaticMeshActor* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsStaticMeshActor.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsStaticMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* AddToAllocatedObjects(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsStaticMeshActor or the UClass
	*  associated with the Object have ImplementsInterface(UCsSoundPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsStaticMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* AddToAllocatedObjects(const FECsStaticMeshActor& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsStaticMeshActor.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsStaticMeshActorPooled*>& GetPool(const FECsStaticMeshActor& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsStaticMeshActor.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsStaticMeshActorPooled*>& GetAllocatedObjects(const FECsStaticMeshActor& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsStaticMeshActor& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsStaticMeshActor& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsStaticMeshActor& Type);

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
	*				Pooled Object implements the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* FindObject(const FECsStaticMeshActor& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsStaticMeshActor.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsStaticMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* FindObject(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsStaticMeshActor or the UClass
	*  associated with the Object have ImplementsInterface(UCsSoundPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsStaticMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* FindObject(const FECsStaticMeshActor& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsStaticMeshActorPooled* FindSafeObject(const FECsStaticMeshActor& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsStaticMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* FindSafeObject(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsStaticMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsStaticMeshActor.
	*/
	const FCsStaticMeshActorPooled* FindSafeObject(const FECsStaticMeshActor& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsStaticMeshActor CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsStaticMeshActor& Type);

	void OnUpdate_Object(const FECsStaticMeshActor& Type, const FCsStaticMeshActorPooled* Object);

	void OnPostUpdate_Pool(const FECsStaticMeshActor& Type);

#pragma endregion Update

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Size
	*/
	void ConstructPayloads(const FECsStaticMeshActor& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual NCsStaticMeshActor::NPayload::IPayload* ConstructPayload(const FECsStaticMeshActor& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsStaticMeshActor::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsStaticMeshActor::NPayload::IPayload.
	*/
	NCsStaticMeshActor::NPayload::IPayload* AllocatePayload(const FECsStaticMeshActor& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsStaticMeshActor::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsStaticMeshActor::NPayload::IPayload.
	*/
	template<typename PayloadTypeImpl>
	FORCEINLINE PayloadTypeImpl* AllocatePayload(const FECsStaticMeshActor& Type)
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
	const FCsStaticMeshActorPooled* Spawn(const FECsStaticMeshActor& Type, NCsStaticMeshActor::NPayload::IPayload* Payload);

	/**
	*
	*/
	//virtual const FCsFXActorPooled* ScriptSpawn(const FECsFX& Type, const FCsScriptProjectilePayload& ScriptPayload);

	/**
	* Delegate type after a Sound has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsStaticMeshActor& /*Type*/, const FCsStaticMeshActorPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerStaticMeshActor_OnSpawn OnSpawn_ScriptEvent;

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
	virtual bool Destroy(const FECsStaticMeshActor& Type, ICsStaticMeshActor* Object);

	virtual bool Destroy(ICsStaticMeshActor* Object);

	/**
	* Delegate type after a Sound has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsStaticMeshActor& /*Type*/, const FCsStaticMeshActorPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& Str);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsStaticMeshActorPooled* Object);

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

	// ICsStaticMeshActor
#pragma region
public:

#pragma endregion ICsStaticMeshActor

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
};