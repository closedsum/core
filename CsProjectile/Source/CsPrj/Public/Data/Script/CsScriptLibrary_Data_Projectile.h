// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Cached.h"
// Data
#include "Data/CsData_ProjectileImplSlice.h"
#include "Data/Collision/CsData_Projectile_CollisionImplSlice.h"
#include "Data/Visual/StaticMesh/CsData_Projectile_VisualStaticMeshImplSlice.h"
#include "Data/Visual/Impact/CsData_Projectile_VisualImpactImplSlice.h"
#include "Data/Damage/CsData_Projectile_DamagePointImplSlice.h"

#include "CsScriptLibrary_Data_Projectile.generated.h"

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsScriptLibrary_Data_Projectile)

UCLASS()
class CSPRJ_API UCsScriptLibrary_Data_Projectile : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	CS_USING_CACHED_FUNCTION_NAME(CsScriptLibrary_Data_Projectile);

public:

	/**
	* Constructs a data that implements the interface: NCsProjectile::NData::IData and
	* is of type: NCsProjectile::NData::FImplSlice
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @oaram Slice
	* return					Whether the data was successful created.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool Construct(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_ProjectileImplSlice& Slice);

	/**
	* Constructs a data that implements the interface: NCsProjectile::NData::IData with Name.
	* Adds slice of type: NCsProjectile::NData::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Object
	* return					Whether the data was successful created.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool ConstructFromObject(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: CollisionDataType (NCsProjectile::NData::NCollision::ICollision) to
	* data with Name.
	* Adds slice of type: NCsProjectile::NData::NCollision::FImplSlice.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_CollisionImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: CollisionDataType (NCsProjectile::NData::NCollision::ICollision) to
	* data with Name.
	* Adds slice of type: NCsProjectile::NData::NCollision::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh) to
	* data with Name.
	* Adds slice of type: NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_VisualStaticMeshImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh)
	* to data with Name.
	* Adds slice of type: NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: ImpactVisualDataType (NCsProjectile::NData::NVisual::NImpact::IImpact) to
	* data with Name.
	* Adds slice of type: NCsProjectile::NData::NVisual::NImpact::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_VisualImpact(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_VisualImpactImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: ImpactVisualDataType (NCsProjectile::NData::NVisual::NImpact::IImpact) to
	* data with Name.
	* Adds slice of type: NCsProjectile::NData::NVisual::NImpact::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_VisualImpact(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: DamageDataType (NCsProjectile::NData::NDamage::IDamage) to
	* data with Name.
	* Adds slice of type: NCsProjectile::NData::NDamage::NPoint::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_DamagePoint(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_DamagePointImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: DamageDataType (NCsProjectile::NData::NDamage::IDamage) to
	* data with Name.
	* Adds slice of type: NCsProjectile::NData::NDamage::NPoint::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_DamagePoint(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);
};