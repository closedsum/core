// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Data
#include "Data/Collision/CsData_Projectile_CollisionImplSlice.h"
#include "Data/Visual/StaticMesh/CsData_Projectile_VisualStaticMeshImplSlice.h"

#include "CsScriptLibrary_Data_Projectile.generated.h"

UCLASS()
class CSPRJ_API UCsScriptLibrary_Data_Projectile : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* Constructs a data
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static void Construct(const FString& Context, const UObject* WorldContextObject, const FString& Name);

	/**
	* Adds a data slice which implements the interface: CollisionDataType (NCsProjectile::NData::NCollision::ICollision) to
	* data with Name.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static void AddSlice_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_CollisionImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh) to
	* data with Name.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Projectile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static void AddSlice_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_VisualStaticMeshImplSlice& Slice);
};