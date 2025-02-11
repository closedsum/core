// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Data
#include "Data/Visual/Material/CsData_Skin_VisualMaterialImplSlice.h"
#include "Data/Visual/StaticMesh/CsData_Skin_VisualStaticMeshImplSlice.h"
#include "Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMeshImplSlice.h"
#include "Data/Visual/CsData_Skin_VisualStaticMeshAndMaterialImpl.h"
#include "Data/Visual/CsData_Skin_VisualSkeletalMeshAndMaterialImpl.h"

#include "CsScriptLibrary_Data_Skin_Visual.generated.h"

class UPrimitiveComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;

UCLASS()
class CSSKIN_API UCsScriptLibrary_Data_Skin_Visual : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* Set any material information related to the interface: CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	* from Slice to Component (StaticMeshComponent or SkeletalMeshComponent).
	* 
	* @param Context			The calling context.
	* @param Slice
	* @param Component
	* return					Whether the operation was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Skin", meta = (AutoCreateRefTerm = "Context,Slice"))
	static bool SetFromSlice_Material(const FString& Context, const FCsData_Skin_VisualMaterialImplSlice& Slice, UPrimitiveComponent* Component);

	/**
	* Set any material information related to the interface: CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	* from Object to Component (StaticMeshComponent or SkeletalMeshComponent).
	*
	* @param Context			The calling context.
	* @param Object
	* @param Component
	* return					Whether the operation was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Skin", meta = (AutoCreateRefTerm = "Context"))
	static bool SetFromObject_Material(const FString& Context, UObject* Object, UPrimitiveComponent* Component);

	/**
	* Set any static mesh information related to the interface: CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
	* from Slice to Component (StaticMeshComponent).
	* 
	* @param Context			The calling context.
	* @param Slice
	* @param Component
	* return					Whether the operation was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Skin", meta = (AutoCreateRefTerm = "Context,Slice"))
	static bool SetFromSlice_StaticMesh(const FString& Context, const FCsData_Skin_VisualStaticMeshImplSlice& Slice, UStaticMeshComponent* Component);

	/**
	* Set any static mesh information related to the interface: CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
	* from Object to Component (StaticMeshComponent).
	*
	* @param Context			The calling context.
	* @param Object
	* @param Component
	* return					Whether the operation was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Skin", meta = (AutoCreateRefTerm = "Context"))
	static bool SetFromObject_StaticMesh(const FString& Context, UObject* Object, UStaticMeshComponent* Component);

	/**
	* Set any skeletal mesh information related to the interface: CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
	* from Slice to Component (SkeletalMeshComponent).
	* 
	* @param Context			The calling context.
	* @param Slice
	* @param Component
	* return					Whether the operation was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Skin", meta = (AutoCreateRefTerm = "Context,Slice"))
	static bool SetFromSlice_SkeletalMesh(const FString& Context, const FCsData_Skin_VisualSkeletalMeshImplSlice& Slice, USkeletalMeshComponent* Component);

	/**
	* Set any skeletal mesh information related to the interface: CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
	* from Object to Component (SkeletalMeshComponent).
	*
	* @param Context			The calling context.
	* @param Object
	* @param Component
	* return					Whether the operation was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Skin", meta = (AutoCreateRefTerm = "Context"))
	static bool SetFromObject_SkeletalMesh(const FString& Context, UObject* Object, USkeletalMeshComponent* Component);

	/**
	* Set any static mesh and material information related to the interfaces: 
	* - CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
	* - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	* from Slice to Component (StaticMeshComponent).
	* 
	* @param Context			The calling context.
	* @param Impl
	* @param Component
	* return					Whether the operation was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Skin", meta = (AutoCreateRefTerm = "Context,Impl"))
	static bool SetFromImpl_StaticMeshAndMaterial(const FString& Context, const FCsData_Skin_VisualStaticMeshAndMaterialImpl& Impl, UStaticMeshComponent* Component);

	/**
	* Set any static mesh and material information related to the interface: 
	* - CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
	* - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	* from Object to Component (StaticMeshComponent).
	*
	* @param Context			The calling context.
	* @param Object
	* @param Component
	* return					Whether the operation was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Skin", meta = (AutoCreateRefTerm = "Context"))
	static bool SetFromObject_StaticMeshAndMaterial(const FString& Context, UObject* Object, UStaticMeshComponent* Component);

	/**
	* Set any skeletal mesh and material information related to the interfaces: 
	* - CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
	* - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	* from Slice to Component (SkeletalMeshComponent).
	* 
	* @param Context			The calling context.
	* @param Impl
	* @param Component
	* return					Whether the operation was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Skin", meta = (AutoCreateRefTerm = "Context,Impl"))
	static bool SetFromImpl_SkeletalMeshAndMaterial(const FString& Context, const FCsData_Skin_VisualSkeletalMeshAndMaterialImpl& Impl, USkeletalMeshComponent* Component);

	/**
	* Set any skeletal mesh and material information related to the interface: 
	* - CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
	* - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	* from Object to Component (SkeletalMeshComponent).
	*
	* @param Context			The calling context.
	* @param Object
	* @param Component
	* return					Whether the operation was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Skin", meta = (AutoCreateRefTerm = "Context"))
	static bool SetFromObject_SkeletalMeshAndMaterial(const FString& Context, UObject* Object, USkeletalMeshComponent* Component);
};