// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Data
#include "Data/CsData_WeaponImplSlice.h"
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"
#include "Data/Types/CsData_GetProjectileTypeImplSlice.h"
#include "Projectile/Data/Visual/CsData_ProjectileWeapon_VisualFireImplSlice.h"
#include "Projectile/Data/Sound/CsData_ProjectileWeapon_SoundFireImplSlice.h"
// Params
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_LaunchTrace.h"

#include "CsScriptLibrary_Data_Weapon.generated.h"

UCLASS()
class CSWP_API UCsScriptLibrary_Data_Weapon : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* Constructs a data that implements the interface: NCsWeapon::NData::IData and
	* is of type: NCsWeapon::NData::FImplSlice
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @oaram Slice
	* return					Whether the data was successful created.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool Construct(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_WeaponImplSlice& Slice);

	/**
	* Constructs a data that implements the interface: NCsWeapon::NData::IData with Name.
	* Adds slice of type: NCsWeapon::NData::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Object
	* return					Whether the data was successful created.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool ConstructFromObject(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: PrjWeaponDataType (NCsProjectile::NData::NCollision::ICollision) to
	* data with Name.
	* Adds slice of type: NCsWeapon::NProjectile::NData::FImplSlice.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_ProjectileWeapon(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_ProjectileWeaponImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: PrjWeaponDataType (NCsProjectile::NData::NCollision::ICollision) to
	* data with Name.
	* Adds slice of type: NCsWeapon::NProjectile::NData::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Object
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_ProjectileWeapon(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds the LaunchParams of type: NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl which implements the interfaces:
	* - LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)
	* - LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
	* to Data slice which implements the interface: PrjWeaponDataType (NCsProjectile::NData::NCollision::ICollision) to
	* data with Name.
	* Adds slice of type: NCsWeapon::NProjectile::NData::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddToSlice_ProjectileWeapon_LaunchTraceParams(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsProjectileWeaponLaunchTraceParams& Params);

	/**
	* Adds the LaunchParams of type: NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl which implements the interfaces:
	* - LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)
	* - LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
	* to Data slice which implements the interface: PrjWeaponDataType (NCsProjectile::NData::NCollision::ICollision) to
	* data with Name.
	* Adds slice of type: NCsWeapon::NProjectile::NData::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Object
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddToSliceFromObject_ProjectileWeapon_LaunchTraceParams(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: ICsData_GetProjectileType to
	* data with Name.
	* Adds slice of type: NProjectile::NData::NType::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_GetProjectileType(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_GetProjectileTypeImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: ICsData_GetProjectileType to
	* data with Name.
	* Adds slice of type: NProjectile::NData::NType::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Object
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_GetProjectileType(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: VisualFireDataType (NCsProjectile::NData::NVisual::NFire::IFire) to
	* data with Name.
	* Adds slice of type: NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_ProjectileWeapon_VisualFire(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_ProjectileWeapon_VisualFireImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: VisualFireDataType (NCsProjectile::NData::NVisual::NFire::IFire) to
	* data with Name.
	* Adds slice of type: NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Object
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_ProjectileWeapon_VisualFire(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: SoundFireDataType (NCsProjectile::NData::NSound::NFire::IFire) to
	* data with Name.
	* Adds slice of type: NCsWeapon::NProjectile::NData::NSound::NFire::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_ProjectileWeapon_SoundFire(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_ProjectileWeapon_SoundFireImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: VisualFireDataType (NCsProjectile::NData::NSound::NFire::IFire) to
	* data with Name.
	* Adds slice of type: NCsWeapon::NProjectile::NData::NSound::NFire::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Object
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Weapon", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_ProjectileWeapon_SoundFire(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);
};