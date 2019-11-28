// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Components/ActorComponent.h"
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Managers/Projectile/CsProjectile.h"
#include "CsManager_Projectile.generated.h"

// Structs
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

	virtual const FString& KeyTypeToString(const FECsProjectile& Type) override;
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

	TCsManager_Internal* Internal;
	 
	virtual void ConstructInternal();

public:

	void InitInternal(const TCsManager_Internal::FCsManagerPooledObjectMapParams& Params);

	virtual void Clear();

	virtual void CreatePool(const FECsProjectile& Type, const int32& Size);

protected:

	virtual TArray<FCsProjectile>& CheckAndAddType_Pools(const FECsProjectile& Type);

	virtual void AddToPool(const FECsProjectile& Type, ICsProjectile* Object);

protected:

	virtual void OnAddToPool(const FECsProjectile& Type, const FCsPooledObject& Object);

public:

	virtual void AddToActivePool(const FECsProjectile& Type, ICsProjectile* Object);

	const TArray<FCsPooledObject>& GetAllActiveObjects(const FECsProjectile& Type);

	const TArray<FCsPooledObject>& GetObjects(const FECsProjectile& Type);

	int32 GetActivePoolSize(const FECsProjectile& Type);

	bool IsExhausted(const FECsProjectile& Type);

	virtual void OnTick(const float& DeltaTime);

	// Payload
#pragma region
public:

	void CreatePayloads(const FECsProjectile& Type, const int32& Size);

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

	virtual const FCsProjectile& Spawn(const FECsProjectile& Type, ICsPooledObjectPayload* Payload);

	/**
	*
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsProjectile& /*Type*/, const FCsProjectile& /*Object*/);

	FOnSpawn OnSpawn_Event;

	FCsManagerProjectile_OnSpawn OnSpawn_ScriptEvent;

#pragma endregion Spawn

	// Destroy
#pragma region
public:

	virtual bool Destroy(const FECsProjectile& Type, ICsProjectile* Projectile);

	virtual bool Destroy(ICsProjectile* Projectile);

	/**
	*
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

	TMap<FECsProjectile, TArray<FCsProjectile>> ActiveObjects;

#pragma endregion Pool
};
