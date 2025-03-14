// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/Script/CsScriptLibrary_Data_Skin_Visual.h"
#include "CsSkin.h"

// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Log
#include "Utility/CsSkinLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Data_Skin_Visual)

// Cached
#pragma region

namespace NCsScriptLibraryDataSkinVisual
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Skin_Visual, SetFromSlice_Material);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Skin_Visual, SetFromObject_Material);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Skin_Visual, SetFromSlice_StaticMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Skin_Visual, SetFromObject_StaticMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Skin_Visual, SetFromSlice_SkeletalMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Skin_Visual, SetFromObject_SkeletalMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Skin_Visual, SetFromImpl_StaticMeshAndMaterial);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Skin_Visual, SetFromObject_StaticMeshAndMaterial);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Skin_Visual, SetFromImpl_SkeletalMeshAndMaterial);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Skin_Visual, SetFromObject_SkeletalMeshAndMaterial);
		}

		namespace Name
		{
			const FName VisualMaterialSlice = FName("VisualMaterialSlice");
			const FName VisualStaticMeshSlice = FName("VisualStaticMeshSlice");
			const FName VisualSkeletalMeshSlice = FName("VisualSkeletalMeshSlice");
			const FName VisualStaticMeshAndMaterialImpl = FName("VisualStaticMeshAndMaterialImpl");
			const FName VisualSkeletalMeshAndMaterialImpl = FName("VisualSkeletalMeshAndMaterialImpl");

			const FName Materials = FName("Materials");
			const FName Mesh = FName("Mesh");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Data_Skin_Visual::UCsScriptLibrary_Data_Skin_Visual(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Data_Skin_Visual::SetFromSlice_Material(const FString& Context, const FCsData_Skin_VisualMaterialImplSlice& Slice, UPrimitiveComponent* Component)
{
	using namespace NCsScriptLibraryDataSkinVisual::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromSlice_Material : Context;

	return Slice.SetSafe(Ctxt, Component);
}

bool UCsScriptLibrary_Data_Skin_Visual::SetFromObject_Material(const FString& Context, UObject* Object, UPrimitiveComponent* Component)
{
	using namespace NCsScriptLibraryDataSkinVisual::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromObject_Material : Context;

	void(*Log)(const FString&) = &NCsSkin::FLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties matching interface: CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	bool Success = false;

	// Try FCsData_Skin_VisualMaterialImplSlice
	using StructSliceType = FCsData_Skin_VisualMaterialImplSlice;

	if (StructSliceType* SliceAsStruct = CsPropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Ctxt, Object, Object->GetClass(), Name::VisualMaterialSlice, nullptr))
	{
		return SliceAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		using StructType = FCsTArrayMaterialInterface;

		StructType* MaterialsPtr = CsPropertyLibrary::GetStructPropertyValuePtr<StructType>(Ctxt, Object, Object->GetClass(), Name::Materials, nullptr);

		if (MaterialsPtr)
		{
			if (!MaterialsPtr->IsValid(Ctxt))
				return false;
			return CsMaterialLibrary::SetSafe(Ctxt, Component, MaterialsPtr->Get());
		}
	}

	UE_LOG(LogCsSkin, Warning, TEXT("%s: Failed to find any properties from %s for interface: CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)."), *Ctxt, *(CsObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualMaterialImplSlice with name: VisualMaterialSlice."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsTArrayMaterialInterface with name: Materials."), *Ctxt);
	return false;
}

bool UCsScriptLibrary_Data_Skin_Visual::SetFromSlice_StaticMesh(const FString& Context, const FCsData_Skin_VisualStaticMeshImplSlice& Slice, UStaticMeshComponent* Component)
{
	using namespace NCsScriptLibraryDataSkinVisual::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromSlice_StaticMesh : Context;

	return Slice.SetSafe(Ctxt, Component);
}

bool UCsScriptLibrary_Data_Skin_Visual::SetFromObject_StaticMesh(const FString& Context, UObject* Object, UStaticMeshComponent* Component)
{
	using namespace NCsScriptLibraryDataSkinVisual::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromObject_StaticMesh : Context;

	void(*Log)(const FString&) = &NCsSkin::FLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties matching interface: CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
	bool Success = false;

	// Try FCsData_Skin_VisualStaticMeshImplSlice
	using StructSliceType = FCsData_Skin_VisualStaticMeshImplSlice;

	if (StructSliceType* SliceAsStruct = CsPropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Ctxt, Object, Object->GetClass(), Name::VisualStaticMeshSlice, nullptr))
	{
		return SliceAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		using StructType = FCsStaticMesh;

		StructType* MeshPtr = CsPropertyLibrary::GetStructPropertyValuePtr<StructType>(Ctxt, Object, Object->GetClass(), Name::Mesh, nullptr);

		if (MeshPtr)
		{
			if (!MeshPtr->IsValid(Ctxt))
				return false;

			CS_IS_PTR_NULL(Component)

			Component->SetStaticMesh(MeshPtr->Get());
			return true;
		}
	}

	UE_LOG(LogCsSkin, Warning, TEXT("%s: Failed to find any properties from %s for interface: CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)."), *Ctxt, *(CsObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualStaticMeshImplSlice with name: VisualStaticMeshSlice."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsStaticMesh with name: Mesh."), *Ctxt);
	return false;
}

bool UCsScriptLibrary_Data_Skin_Visual::SetFromSlice_SkeletalMesh(const FString& Context, const FCsData_Skin_VisualSkeletalMeshImplSlice& Slice, USkeletalMeshComponent* Component)
{
	using namespace NCsScriptLibraryDataSkinVisual::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromSlice_SkeletalMesh : Context;

	return Slice.SetSafe(Ctxt, Component);
}

bool UCsScriptLibrary_Data_Skin_Visual::SetFromObject_SkeletalMesh(const FString& Context, UObject* Object, USkeletalMeshComponent* Component)
{
	using namespace NCsScriptLibraryDataSkinVisual::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromObject_SkeletalMesh : Context;

	void(*Log)(const FString&) = &NCsSkin::FLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties matching interface: CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
	bool Success = false;

	// Try FCsData_Skin_VisualSkeletalMeshImplSlice
	using StructSliceType = FCsData_Skin_VisualSkeletalMeshImplSlice;

	if (StructSliceType* SliceAsStruct = CsPropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Ctxt, Object, Object->GetClass(), Name::VisualSkeletalMeshSlice, nullptr))
	{
		return SliceAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		using StructType = FCsSkeletalMesh;

		StructType* MeshPtr = CsPropertyLibrary::GetStructPropertyValuePtr<StructType>(Ctxt, Object, Object->GetClass(), Name::Mesh, nullptr);

		if (MeshPtr)
		{
			if (!MeshPtr->IsValid(Ctxt))
				return false;

			CS_IS_PTR_NULL(Component)

			Component->SetSkeletalMesh(MeshPtr->Get());
			return true;
		}
	}

	UE_LOG(LogCsSkin, Warning, TEXT("%s: Failed to find any properties from %s for interface: CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)."), *Ctxt, *(CsObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualSkeletalMeshImplSlice with name: VisualSkeletalMeshSlice."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsSkeletalMesh with name: Mesh."), *Ctxt);
	return false;
}

bool UCsScriptLibrary_Data_Skin_Visual::SetFromImpl_StaticMeshAndMaterial(const FString& Context, const FCsData_Skin_VisualStaticMeshAndMaterialImpl& Impl, UStaticMeshComponent* Component)
{
	using namespace NCsScriptLibraryDataSkinVisual::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromImpl_StaticMeshAndMaterial : Context;

	return Impl.SetSafe(Ctxt, Component);
}

bool UCsScriptLibrary_Data_Skin_Visual::SetFromObject_StaticMeshAndMaterial(const FString& Context, UObject* Object, UStaticMeshComponent* Component)
{
	using namespace NCsScriptLibraryDataSkinVisual::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromObject_StaticMeshAndMaterial : Context;

	void(*Log)(const FString&) = &NCsSkin::FLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties matching interface: 
	// - CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
	// - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	bool Success = false;

	// Try FCsData_Skin_VisualStaticMeshAndMaterialImpl
	using StructImplType = FCsData_Skin_VisualStaticMeshAndMaterialImpl;

	if (StructImplType* ImplAsStruct = CsPropertyLibrary::GetStructPropertyValuePtr<StructImplType>(Ctxt, Object, Object->GetClass(), Name::VisualStaticMeshAndMaterialImpl, nullptr))
	{
		return ImplAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		FCsStaticMesh* MeshPtr					 = CsPropertyLibrary::GetStructPropertyValuePtr<FCsStaticMesh>(Ctxt, Object, Object->GetClass(), Name::Mesh, nullptr);
		FCsTArrayMaterialInterface* MaterialsPtr = CsPropertyLibrary::GetStructPropertyValuePtr<FCsTArrayMaterialInterface>(Ctxt, Object, Object->GetClass(), Name::Materials, nullptr);

		if (MeshPtr &&
			MaterialsPtr)
		{
			if (!MeshPtr->IsValid(Ctxt))
				return false;

			if (!MaterialsPtr->IsValid(Ctxt))
				return false;

			CS_IS_PTR_NULL(Component)

			Component->SetStaticMesh(MeshPtr->Get());
			return CsMaterialLibrary::SetSafe(Ctxt, Component, MaterialsPtr->Get());
		}
	}

	UE_LOG(LogCsSkin, Warning, TEXT("%s: Failed to find any properties from %s for interface:"), *Ctxt, *(CsObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualStaticMeshAndMaterialImpl with name: VisualStaticMeshAndMaterialImpl."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsStaticMesh with name: Mesh."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsTArrayMaterialInterface with name: Materials."), *Ctxt);
	return false;
}

bool UCsScriptLibrary_Data_Skin_Visual::SetFromImpl_SkeletalMeshAndMaterial(const FString& Context, const FCsData_Skin_VisualSkeletalMeshAndMaterialImpl& Impl, USkeletalMeshComponent* Component)
{
	using namespace NCsScriptLibraryDataSkinVisual::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromImpl_SkeletalMeshAndMaterial : Context;

	return Impl.SetSafe(Ctxt, Component);
}

bool UCsScriptLibrary_Data_Skin_Visual::SetFromObject_SkeletalMeshAndMaterial(const FString& Context, UObject* Object, USkeletalMeshComponent* Component)
{
	using namespace NCsScriptLibraryDataSkinVisual::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromObject_SkeletalMeshAndMaterial : Context;

	void(*Log)(const FString&) = &NCsSkin::FLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties matching interface: 
	// - CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
	// - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	bool Success = false;

	// Try FCsData_Skin_VisualSkeletalMeshAndMaterialImpl
	using StructImplType = FCsData_Skin_VisualSkeletalMeshAndMaterialImpl;

	if (StructImplType* ImplAsStruct = CsPropertyLibrary::GetStructPropertyValuePtr<StructImplType>(Ctxt, Object, Object->GetClass(), Name::VisualSkeletalMeshAndMaterialImpl, nullptr))
	{
		return ImplAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		FCsSkeletalMesh* MeshPtr				 = CsPropertyLibrary::GetStructPropertyValuePtr<FCsSkeletalMesh>(Ctxt, Object, Object->GetClass(), Name::Mesh, nullptr);
		FCsTArrayMaterialInterface* MaterialsPtr = CsPropertyLibrary::GetStructPropertyValuePtr<FCsTArrayMaterialInterface>(Ctxt, Object, Object->GetClass(), Name::Materials, nullptr);

		if (MeshPtr &&
			MaterialsPtr)
		{
			if (!MeshPtr->IsValid(Ctxt))
				return false;

			if (!MaterialsPtr->IsValid(Ctxt))
				return false;

			CS_IS_PTR_NULL(Component)

			Component->SetSkeletalMesh(MeshPtr->Get());
			return CsMaterialLibrary::SetSafe(Ctxt, Component, MaterialsPtr->Get());
		}
	}

	UE_LOG(LogCsSkin, Warning, TEXT("%s: Failed to find any properties from %s for interface:"), *Ctxt, *(CsObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualSkeletalMeshAndMaterialImpl with name: VisualSkeletalMeshAndMaterialImpl."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsSkeletalMesh with name: Mesh."), *Ctxt);
	UE_LOG(LogCsSkin, Warning, TEXT("%s: - Failed to get struct property of type: FCsTArrayMaterialInterface with name: Materials."), *Ctxt);
	return false;
}