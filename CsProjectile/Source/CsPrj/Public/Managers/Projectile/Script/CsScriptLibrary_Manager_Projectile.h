// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Projectile/CsSettings_Manager_Projectile.h"
// Projectile
#include "Payload/CsPayload_ProjectileImpl.h"

#include "CsScriptLibrary_Manager_Projectile.generated.h"

// Delegates
#pragma region

#pragma endregion Delegates

class UCsManager_Projectile;
class ICsProjectile;

UCLASS()
class CSPRJ_API UCsScriptLibrary_Manager_Projectile : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get the reference to UCsManager_Projectile from a WorldContext.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* return				UCsManager_Projectile.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPrj|Library|Manager|Projecitle", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static UCsManager_Projectile* Get(const FString& Context, const UObject* WorldContextObject);

#pragma endregion Get

// Settings
#pragma region
public:

	/**
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutTypes			(out)
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPrj|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool GetTypeToSetAsArray(const FString& Context, const UObject* WorldContextObject, TArray<FECsProjectile>& OutTypes);

	/**
	*
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Key
	* @param Value
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPrj|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Key,Value"))
	static void SetTypeMapKeyValue(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Key, const FECsProjectile& Value);

	
	/**
	* 
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type
	* @param PoolParams
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPrj|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type,PoolParams"))
	static bool AddPoolParams(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type, const FCsSettings_Manager_Projectile_PoolParams& PoolParams);


#pragma endregion Settings

// Allocate / Deallocate
#pragma region
public:

	/**
	* Queue deallocating all Projectiles.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type
	* @param Pickup
	* return					Whether was successful performed or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPrj|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool QueueDeallocateAll(const FString& Context, const UObject* WorldContextObject);

#pragma endregion Allocate / Deallocate

// Pool
#pragma region
public:

	/**
	* Find a pooled Projectile Object that implements the interface: ICsProjectile with the
	* given Type and Index.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type
	* @param Index
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type,Index"))
	static UObject* FindObject(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type, const int32& Index);

	/**
	* Determine whether a pool as been created for the appropriate Type.
	*
	* @oaran Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type				Type of pool.
	* return					Whether the pool of Type has been created.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
	static bool HasPool(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type);

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsProjectile.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type				Type of pool to get.
	* @param OutPool			(out)
	* return				
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
	static bool GetPool(const FString& Context, const UObject* WorldContextObject, const FECsProjectile& Type, TArray<UObject*>& OutPool);

#pragma endregion Pool

// Spawn
#pragma region
public:

	/**
	* Spawn a Projectile with the given Payload
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Payload
	* @param OutIndex			(out)
	* return					Object of type ICsProjectile
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPrj|Library|Manager|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type,Payload"))
	static UObject* Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_Projectile& Payload, int32& OutIndex);

#pragma endregion Spawn
};