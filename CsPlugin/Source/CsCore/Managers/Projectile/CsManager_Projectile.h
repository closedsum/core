// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Components/ActorComponent.h"
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Managers/Projectile/CsProjectile.h"
#include "Managers/MemoryResource/CsManager_MemoryResource.h"
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

struct CSCORE_API FCsMemoryResource_Projectile : public TCsMemoryResource<FCsProjectile>
{
};

struct CSCORE_API FCsManager_MemoryResource_Projectile : public TCsManager_MemoryResource<FCsProjectile, FCsMemoryResource_Projectile>
{
};

#pragma endregion Structs

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerProjectile_OnSpawn, const FECsProjectile&, Type, TScriptInterface<ICsProjectile>, Projectile);

#pragma endregion Delegates

// Internal
#pragma region

class ICsProjectile;

class CSCORE_API FCsManager_Projectile_Internal : public TCsManager_PooledObject_Map<FECsProjectile>
{
private:

	typedef TCsManager_PooledObject_Map<FECsProjectile> Super;

public:

	FCsManager_Projectile_Internal();

	FORCEINLINE virtual const FString& KeyTypeToString(const FECsProjectile& Type) override
	{
		return Type.Name;
	}
};

#pragma endregion Internal

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

	static UCsManager_Projectile* Get();
	
	template<typename T>
	static T* Get()
	{
		return Cast<T>(Get());
	}

	static void Init(UCsManager_Projectile* Manager);
	static void Shutdown();

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Projectile* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton

// Internal
#pragma region

	typedef TCsManager_PooledObject_Map<FECsProjectile> TCsManager_Internal;

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
protected:

	/**
	*
	* @param Type
	*/
	virtual TArray<FCsProjectile>& CheckAndAddType_Pools(const FECsProjectile& Type);

public:

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	virtual void AddToPool(const FECsProjectile& Type, ICsProjectile* Object);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	virtual void AddToPool(const FECsProjectile& Type, const FCsProjectile& Object);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	virtual void AddToPool(const FECsProjectile& Type, UObject* Object);

	virtual void OnAddToPool(const FECsProjectile& Type, const FCsPooledObject& Object);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	virtual void AddToAllocatedPool(const FECsProjectile& Type, ICsProjectile* Object);

#pragma endregion Add

public:

	const TArray<FCsPooledObject>& GetAllAllocatedObjects(const FECsProjectile& Type);

	const TArray<FCsPooledObject>& GetPool(const FECsProjectile& Type);

	const int32& GetPoolSize(const FECsProjectile& Type);
	int32 GetAllocatedPoolSize(const FECsProjectile& Type);

	bool IsExhausted(const FECsProjectile& Type);

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const float& DeltaTime);

#pragma endregion Update

	// Payload
#pragma region
public:

	void ConstructPayloads(const FECsProjectile& Type, const int32& Size);

	ICsPooledObjectPayload* AllocatePayload(const FECsProjectile& Type);

	template<typename T>
	T* AllocatePayload(const FECsProjectile& Type)
	{
#if !UE_BUILD_SHIPPING
		T* Payload = dynamic_cast<T>(AllocatePayload(Type));

		check(Payload);

		return Payload;
#else
		return (T*)AllocatePayload(Type);
#endif // #if !UE_BUILD_SHIPPING
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
	virtual const FCsProjectile& Spawn(const FECsProjectile& Type, ICsPooledObjectPayload* Payload);

	/**
	* Delegate type after a Projectile has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsProjectile& /*Type*/, const FCsProjectile& /*Object*/);

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
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsProjectile& /*Type*/, const FCsProjectile& /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

#pragma endregion Internal

// Pool
#pragma region
protected:

	TMap<FECsProjectile, TArray<FCsProjectile>> Pools;

	UPROPERTY()
	TArray<UObject*> Pool;

	TMap<FECsProjectile, TArray<FCsProjectile>> AllocatedObjects;

#pragma endregion Pool

// Script
#pragma region
public:

	// ICsProjectile
#pragma region
public:

	/** Delegate for getting the Owner of a Projectile. 
		 The Projectile implements a script interface of type: ICsProjectile. */
	FCsProjectile::FScript_GetOwner Script_GetOwner_Impl;

	/** Delegate for getting the Instigator of a Projectile. 
		 The Projectile implements a script interface of type: ICsProjectile. */
	FCsProjectile::FScript_GetInstigator Script_GetInstigator_Impl;

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

#pragma endregion Script
};