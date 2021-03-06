// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/Creep/CsTdSettings_Manager_Creep.h"
#include "Managers/Creep/CsTdCreep.h"
#include "Managers/Creep/Payload/CsTdCreepPayload.h"
#include "CsTdManager_Creep.generated.h"

// Structs
#pragma region

#pragma endregion Structs

// Delegates
#pragma region

/**
*
*
* @param Type
* @param Creep
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsTdManagerCreep_OnSpawn, const FECsTdCreep&, Type, TScriptInterface<ICsTdCreep>, Creep);

#pragma endregion Delegates

// Internal
#pragma region

class ICsTdCreep;

class CSTD_API FCsTdManager_Creep_Internal : public TCsManager_PooledObject_Map<ICsTdCreep, FCsTdCreepPooled, ICsTdCreepPayload, FECsTdCreep>
{
private:

	typedef TCsManager_PooledObject_Map<ICsTdCreep, FCsTdCreepPooled, ICsTdCreepPayload, FECsTdCreep> Super;

public:

	FCsTdManager_Creep_Internal();

	FORCEINLINE virtual const FString& KeyTypeToString(const FECsTdCreep& Type) override
	{
		return Type.Name;
	}

	FORCEINLINE virtual bool IsValidKey(const FECsTdCreep& Type) override
	{
		return EMCsTdCreep::Get().IsValidEnum(Type);
	}
};

#pragma endregion Internal

class ICsTdGetManagerCreep;

UCLASS(config=Game, defaultconfig)
class CSTD_API UCsTdManager_Creep : public UObject
{
	GENERATED_UCLASS_BODY()

public:	

// Singleton
#pragma region
public:

	static UCsTdManager_Creep* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsTdManager_Creep> ManagerCreepClass, UObject* InOuter = nullptr);

	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsTdGetManagerCreep* Get_GetManagerCreep(UObject* InRoot);
	static ICsTdGetManagerCreep* GetSafe_GetManagerCreep(UObject* Object);

	static UCsTdManager_Creep* GetSafe(UObject* Object);

public:

	static UCsTdManager_Creep* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsTdManager_Creep* s_Instance;
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

	FCsTdSettings_Manager_Creep Settings;

public:

	FORCEINLINE void SetSettings(const FCsTdSettings_Manager_Creep& InSettings)
	{
		Settings = InSettings;
	}

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of Creep. */
	FCsTdManager_Creep_Internal Internal;
	
	/**
	* Setup the internal manager for handling the pool of Creeps.
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
	void InitInternal(const FCsTdManager_Creep_Internal::FCsManagerPooledObjectMapParams& Params);

	virtual void Clear();

	// Pool
#pragma region
public:

	/**
	* 
	* @param Type
	* @param Size
	*/
	void CreatePool(const FECsTdCreep& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TBaseDelegate<FCsTdCreepPooled*, const FECsTdCreep&>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsTdCreepPooled* ConstructContainer(const FECsTdCreep& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void, const FCsTdCreepPooled*>& GetOnConstructObject_Event(const FECsTdCreep& Type);

		// Add
#pragma region

			// Pool
#pragma region
public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsTdCreep.
	*
	* @param Type			Type of pool to add the Object to.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsTdCreep.
	*/
	const FCsTdCreepPooled* AddToPool(const FECsTdCreep& Type, ICsTdCreep* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsTdCreep.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsTdCreep.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsTdCreep.
	*/
	const FCsTdCreepPooled* AddToPool(const FECsTdCreep& Type, const FCsTdCreepPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsTdCreep or the UClass
	*  associated with the Object have ImplementsInterface(UCsTdCreep::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsTdCreep.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsTdCreep.
	*/
	const FCsTdCreepPooled* AddToPool(const FECsTdCreep& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsTdCreep.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsTdCreep.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsTdCreep.
	*/
	const FCsTdCreepPooled* AddToAllocatedObjects(const FECsTdCreep& Type, ICsTdCreep* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsTdCreep.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsTdCreep.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsTdCreep.
	*/
	const FCsTdCreepPooled* AddToAllocatedObjects(const FECsTdCreep& Type, ICsTdCreep* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsTdCreep or the UClass
	*  associated with the Object have ImplementsInterface(UCsTdCreep::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsTdCreep.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsTdCreep.
	*/
	const FCsTdCreepPooled* AddToAllocatedObjects(const FECsTdCreep& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsTdCreep.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsTdCreepPooled*>& GetPool(const FECsTdCreep& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsTdCreep.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsTdCreepPooled*>& GetAllocatedObjects(const FECsTdCreep& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsTdCreep& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsTdCreep& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsTdCreep& Type);

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
	*				Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsTdCreepPooled* FindObject(const FECsTdCreep& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsTdCreepPooled* FindObject(const FECsTdCreep& Type, ICsTdCreep* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsPooledObject or the UClass
	*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	const FCsTdCreepPooled* FindObject(const FECsTdCreep& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsTdCreepPooled* FindSafeObject(const FECsTdCreep& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsTdCreepPooled* FindSafeObject(const FECsTdCreep& Type, ICsTdCreep* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	const FCsTdCreepPooled* FindSafeObject(const FECsTdCreep& Type, UObject* Object);


#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsTdCreep CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsTdCreep& Type);

	void OnUpdate_Object(const FECsTdCreep& Type, const FCsTdCreepPooled* Object);

	void OnPostUpdate_Pool(const FECsTdCreep& Type);

#pragma endregion Update

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const FECsTdCreep& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual ICsTdCreepPayload* ConstructPayload(const FECsTdCreep& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPooledObjectPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsPooledObjectPayload.
	*/
	ICsTdCreepPayload* AllocatePayload(const FECsTdCreep& Type);

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
	const FCsTdCreepPooled* Spawn(const FECsTdCreep& Type, ICsTdCreepPayload* Payload);

	template<typename CreepContainerType, typename PayloadType>
	const CreepContainerType* Spawn(const FECsTdCreep& Type, PayloadType* Payload)
	{
		Internal->Spawn<CreepContainerType, PayloadType>(Type, Payload);
	}

	/**
	* Delegate type after a Creep has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsTdCreep& /*Type*/, const FCsTdCreepPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsTdManagerCreep_OnSpawn OnSpawn_ScriptEvent;

#pragma endregion Spawn

	// Destroy
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Projectile
	*/
	bool Destroy(const FECsTdCreep& Type, ICsTdCreep* Creep);

	/**
	*
	*
	* @param Creep
	* return
	*/
	bool Destroy(ICsTdCreep* Creep);

	/**
	* Delegate type after a Creep has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsTdCreep& /*Type*/, const FCsTdCreepPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

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

	// ICsTdCreep
#pragma region
public:

	/** Delegate for getting the Owner of a Creep. 
		 The Creep implements a script interface of type: ICsTdCreep. */
	//FCsTdCreepPooled::FScript_GetOwner Script_GetOwner_Impl;

	/** Delegate for getting the Instigator of a Creep. 
		 The Creep implements a script interface of type: ICsTdCreep. */
	//FCsTdCreepPooled::FScript_GetInstigator Script_GetInstigator_Impl;

#pragma endregion ICsTdCreep

	// ICsPooledObject
#pragma region
public:

	/** Delegate for getting the Cache associated with a Pooled Object. 
		 The Pooled Object implements a script interface of type: ICsPooledObject. */
	FCsPooledObject::FScript_GetCache Script_GetCache_Impl;

	/** Delegate called after allocating a Pooled Object. 
		 The Pooled Object implements a script interface of type: ICsPooledObject. */
	FCsPooledObject::FScript_Allocate Script_Allocate_Impl;

	/** Delegate called after deallocating a Pooled Object. 
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
};