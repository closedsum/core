// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Components/ActorComponent.h"
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Managers/Projectile/CsProjectile.h"
#include "Managers/Resource/CsManager_ResourceValueType.h"
#include "CsManager_Projectile.generated.h"

// Structs
#pragma region

	// ProjectilePayload
#pragma region

class UObject;

struct CSCORE_API FCsProjectilePayload : public ICsProjectilePayload, public ICsPooledObjectPayload
{
public:

	FVector Direction;

	FVector Location;

	bool bAllocated;

	TWeakObjectPtr<UObject> Instigator;

	TWeakObjectPtr<UObject> Owner;

	TWeakObjectPtr<UObject> Parent;

	FCsProjectilePayload()
	{
		Reset();
	}

	virtual ~FCsProjectilePayload(){}

// ICsProjectilePayload
#pragma region
public:

	FORCEINLINE const FVector& GetDirection() const
	{
		return Direction;
	}

	FORCEINLINE const FVector& GetLocation() const
	{
		return Location;
	}

#pragma endregion ICsProjectilePayload

// ICsPooledObjectPayload
#pragma region
public:

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator.IsValid() ? Instigator.Get() : nullptr;
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Owner.IsValid() ? Owner.Get() : nullptr;
	}

	FORCEINLINE UObject* GetParent() const
	{
		return Parent.IsValid() ? Parent.Get() : nullptr;
	}

	FORCEINLINE void Allocate()
	{
		bAllocated = true;
	}

	void Reset()
	{
		Direction = FVector::ZeroVector;
		Location = FVector::ZeroVector;

		bAllocated = false;
		Instigator = nullptr;
		Owner = nullptr;
		Parent = nullptr;
	}

#pragma endregion ICsPooledObjectPayload

public:

	template<typename T>
	FORCEINLINE T* GetInstigator() const
	{
		return Cast<T>(GetInstigator());
	}

	template<typename T>
	FORCEINLINE T* GetOwner() const
	{
		return Cast<T>(GetOwner());
	}

	template<typename T>
	FORCEINLINE T* GetParent() const
	{
		return Cast<T>(GetParent());
	}
};

#pragma endregion ProjectilePayload

#pragma endregion Structs

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerProjectile_OnSpawn, const FECsProjectile&, Type, TScriptInterface<ICsProjectile>, Projectile);

#pragma endregion Delegates

// Internal
#pragma region

class ICsProjectile;

class CSCORE_API FCsManager_Projectile_Internal : public TCsManager_PooledObject_Map<ICsProjectile, FCsProjectilePooled, FCsProjectilePayload, FECsProjectile>
{
private:

	typedef TCsManager_PooledObject_Map<ICsProjectile, FCsProjectilePooled, FCsProjectilePayload, FECsProjectile> Super;

public:

	FCsManager_Projectile_Internal();

	FORCEINLINE virtual const FString& KeyTypeToString(const FECsProjectile& Type) override
	{
		return Type.Name;
	}

	/** Delegate for getting the Owner of a Projectile.
		 The Projectile implements a script interface of type: ICsProjectile. */
	FCsProjectilePooled::FScript_GetOwner Script_GetOwner_Impl;

	/** Delegate for getting the Instigator of a Projectile.
		 The Projectile implements a script interface of type: ICsProjectile. */
	FCsProjectilePooled::FScript_GetInstigator Script_GetInstigator_Impl;

	virtual void OnAddToPool_UpdateScriptDelegates(FCsProjectilePooled* Object) override;
};

#pragma endregion Internal

class ICsGetManagerProjectile;

UCLASS()
class CSCORE_API UCsManager_Projectile : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:	

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region
protected:

	virtual void OnRegister() override;

#pragma endregion UActorComponent Interface

// Singleton
#pragma region
public:

	static UCsManager_Projectile* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static void Init(UCsManager_Projectile* Manager);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerProjectile* Get_GetManagerProjectile(UObject* InRoot);
	static ICsGetManagerProjectile* GetSafe_GetManagerProjectile(UObject* Object);

	static UCsManager_Projectile* GetSafe(UObject* Object);

public:

	static UCsManager_Projectile* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Projectile* s_Instance;
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

// Internal
#pragma region
protected:

	typedef TCsManager_PooledObject_Map<ICsProjectile, FCsProjectilePooled, FCsProjectilePayload, FECsProjectile> TCsManager_Internal;

protected:
	
	/** Reference to the internal manager for handling the pool of projectiles. */
	TCsManager_Internal* Internal;
	
	/**
	* Construct the internal manager for handling the pool of projectiles.
	*/
	virtual void ConstructInternal();

public:

	/**
	*
	*
	* @param Params
	*/
	void InitInternal(const TCsManager_Internal::FCsManagerPooledObjectMapParams& Params);

	virtual void Clear();

	// Pool
#pragma region
public:

	/**
	* 
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const FECsProjectile& Type, const int32& Size);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsProjectile.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsProjectile.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToPool(const FECsProjectile& Type, ICsProjectile* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsProjectile.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsProjectile.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToPool(const FECsProjectile& Type, const FCsProjectilePooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsProjectile or the UClass
	*  associated with the Object have ImplementsInterface(UCsProjectile::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsProjectile.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToPool(const FECsProjectile& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsProjectile.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsProjectile.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsProjectile.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsProjectile.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsProjectile or the UClass
	*  associated with the Object have ImplementsInterface(UCsProjectile::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsProjectile.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToAllocatedObjects(const FECsProjectile& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsProjectile.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsProjectilePooled*>& GetPool(const FECsProjectile& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsProjectile.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsProjectilePooled*>& GetAllocatedObjects(const FECsProjectile& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsProjectile& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsProjectile& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsProjectile& Type);

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
	const FCsProjectilePooled* FindObject(const FECsProjectile& Type, const int32& Index);

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
	const FCsProjectilePooled* FindObject(const FECsProjectile& Type, ICsProjectile* Object);

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
	const FCsProjectilePooled* FindObject(const FECsProjectile& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsProjectilePooled* FindSafeObject(const FECsProjectile& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsProjectilePooled* FindSafeObject(const FECsProjectile& Type, ICsProjectile* Object);

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
	const FCsProjectilePooled* FindSafeObject(const FECsProjectile& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsProjectile CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsProjectile& Type);

	void OnUpdate_Object(const FECsProjectile& Type, const FCsProjectilePooled* Object);

	void OnPostUpdate_Pool(const FECsProjectile& Type);

#pragma endregion Update

	// Payload
#pragma region
public:

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPooledObjectPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsPooledObjectPayload.
	*/
	FCsProjectilePayload* AllocatePayload(const FECsProjectile& Type);

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
	virtual const FCsProjectilePooled* Spawn(const FECsProjectile& Type, FCsProjectilePayload* Payload);

	/**
	* Delegate type after a Projectile has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsProjectile& /*Type*/, const FCsProjectilePooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerProjectile_OnSpawn OnSpawn_ScriptEvent;

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
	virtual bool Destroy(const FECsProjectile& Type, ICsProjectile* Projectile);

	virtual bool Destroy(ICsProjectile* Projectile);

	/**
	* Delegate type after a Projectile has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsProjectile& /*Type*/, const FCsProjectilePooled* /*Object*/);

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

	// ICsProjectile
#pragma region
public:

	/** Delegate for getting the Owner of a Projectile. 
		 The Projectile implements a script interface of type: ICsProjectile. */
	FCsProjectilePooled::FScript_GetOwner Script_GetOwner_Impl;

	/** Delegate for getting the Instigator of a Projectile. 
		 The Projectile implements a script interface of type: ICsProjectile. */
	FCsProjectilePooled::FScript_GetInstigator Script_GetInstigator_Impl;

#pragma endregion ICsProjectile

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

#pragma endregion ICsUpdate

#pragma endregion Script
};