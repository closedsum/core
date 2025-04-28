// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Data
#include "Data/CsData_BeamImplSlice.h"
#include "Data/Collision/CsData_Beam_CollisionImplSlice.h"
#include "Data/Visual/StaticMesh/CsData_Beam_VisualStaticMeshImplSlice.h"
#include "Data/Visual/Impact/CsData_Beam_VisualImpactImplSlice.h"
#include "Data/Damage/CsData_Beam_DamagePointImplSlice.h"

#include "CsScriptLibrary_Data_Beam.generated.h"

UCLASS()
class CSBEAM_API UCsScriptLibrary_Data_Beam : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* Constructs a data that implements the interface: NCsBeam::NData::IData and
	* is of type: NCsBeam::NData::FImplSlice
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @oaram Slice
	* return					Whether the data was successful created.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Data|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool Construct(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_BeamImplSlice& Slice);

	/**
	* Constructs a data that implements the interface: NCsBeam::NData::IData with Name.
	* Adds slice of type: NCsBeam::NData::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Object
	* return					Whether the data was successful created.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Data|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool ConstructFromObject(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: CollisionDataType (NCsBeam::NData::NCollision::ICollision) to
	* data with Name.
	* Adds slice of type: NCsBeam::NData::NCollision::NImplSlice::FImplSlice.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Data|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Beam_CollisionImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: CollisionDataType (NCsBeam::NData::NCollision::ICollision) to
	* data with Name.
	* Adds slice of type: NCsBeam::NData::NCollision::NImplSlice::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Data|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: StaticMeshVisualDataType (NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh) to
	* data with Name.
	* Adds slice of type: NCsBeam::NData::NVisual::NStaticMesh::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Data|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Beam_VisualStaticMeshImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: StaticMeshVisualDataType (NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh)
	* to data with Name.
	* Adds slice of type: NCsBeam::NData::NVisual::NStaticMesh::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Data|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact) to
	* data with Name.
	* Adds slice of type: NCsBeam::NData::NVisual::NImpact::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Data|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_VisualImpact(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Beam_VisualImpactImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact) to
	* data with Name.
	* Adds slice of type: NCsBeam::NData::NVisual::NImpact::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Data|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_VisualImpact(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);

	/**
	* Adds a data slice which implements the interface: DamageDataType (NCsBeam::NData::NDamage::IDamage) to
	* data with Name.
	* Adds slice of type: NCsBeam::NData::NDamage::NPoint::NImplSlice::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Data|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool AddSlice_DamagePoint(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Beam_DamagePointImplSlice& Slice);

	/**
	* Adds a data slice which implements the interface: DamageDataType (NCsBeam::NData::NDamage::IDamage) to
	* data with Name.
	* Adds slice of type: NCsBeam::NData::NDamage::NPoint::NImplSlice::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Slice
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Data|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool AddSliceFromObject_DamagePoint(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);
};