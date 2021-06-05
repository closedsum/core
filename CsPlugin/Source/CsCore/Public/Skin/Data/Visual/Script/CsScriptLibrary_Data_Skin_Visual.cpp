// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/Script/CsScriptLibrary_Data_Skin_Visual.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Object.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Log
#include "Utility/CsLog.h"

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

	void(*Log)(const FString&) = &FCsLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties matching interface: MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	typedef NCsProperty::FLibrary PropertyLibrary;

	bool Success = false;

	// Try FCsData_Skin_VisualMaterialImplSlice
	typedef FCsData_Skin_VisualMaterialImplSlice StructSliceType;

	if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Ctxt, Object, Object->GetClass(), Name::VisualMaterialSlice, nullptr))
	{
		return SliceAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		typedef FCsTArrayMaterialnterface StructType;

		StructType* MaterialsPtr = PropertyLibrary::GetStructPropertyValuePtr<StructType>(Ctxt, Object, Object->GetClass(), Name::Materials, nullptr);

		if (MaterialsPtr)
		{
			if (!MaterialsPtr->IsValid(Ctxt))
				return false;

			typedef NCsMaterial::FLibrary MaterialLibrary;

			return MaterialLibrary::SetSafe(Ctxt, Component, MaterialsPtr->Get());
		}
	}

	typedef NCsObject::FLibrary ObjectLibrary;

	UE_LOG(LogCs, Warning, TEXT("%s: Failed to find any properties from %s for interface: MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)."), *Ctxt, *(ObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualMaterialImplSlice with name: VisualMaterialSlice."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsTArrayMaterialnterface with name: Materials."), *Ctxt);

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

	void(*Log)(const FString&) = &FCsLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties matching interface: StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
	typedef NCsProperty::FLibrary PropertyLibrary;

	bool Success = false;

	// Try FCsData_Skin_VisualStaticMeshImplSlice
	typedef FCsData_Skin_VisualStaticMeshImplSlice StructSliceType;

	if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Ctxt, Object, Object->GetClass(), Name::VisualStaticMeshSlice, nullptr))
	{
		return SliceAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		typedef FCsStaticMesh StructType;

		StructType* MeshPtr = PropertyLibrary::GetStructPropertyValuePtr<StructType>(Ctxt, Object, Object->GetClass(), Name::Mesh, nullptr);

		if (MeshPtr)
		{
			if (!MeshPtr->IsValid(Ctxt))
				return false;

			CS_IS_PTR_NULL(Component)

			Component->SetStaticMesh(MeshPtr->Get());
			return true;
		}
	}

	typedef NCsObject::FLibrary ObjectLibrary;

	UE_LOG(LogCs, Warning, TEXT("%s: Failed to find any properties from %s for interface: StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)."), *Ctxt, *(ObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualStaticMeshImplSlice with name: VisualStaticMeshSlice."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsStaticMesh with name: Mesh."), *Ctxt);

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

	void(*Log)(const FString&) = &FCsLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties matching interface: SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
	typedef NCsProperty::FLibrary PropertyLibrary;

	bool Success = false;

	// Try FCsData_Skin_VisualSkeletalMeshImplSlice
	typedef FCsData_Skin_VisualSkeletalMeshImplSlice StructSliceType;

	if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Ctxt, Object, Object->GetClass(), Name::VisualSkeletalMeshSlice, nullptr))
	{
		return SliceAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		typedef FCsSkeletalMesh StructType;

		StructType* MeshPtr = PropertyLibrary::GetStructPropertyValuePtr<StructType>(Ctxt, Object, Object->GetClass(), Name::Mesh, nullptr);

		if (MeshPtr)
		{
			if (!MeshPtr->IsValid(Ctxt))
				return false;

			CS_IS_PTR_NULL(Component)

			Component->SetSkeletalMesh(MeshPtr->Get());
			return true;
		}
	}

	typedef NCsObject::FLibrary ObjectLibrary;

	UE_LOG(LogCs, Warning, TEXT("%s: Failed to find any properties from %s for interface: SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)."), *Ctxt, *(ObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualSkeletalMeshImplSlice with name: VisualSkeletalMeshSlice."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsSkeletalMesh with name: Mesh."), *Ctxt);

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

	void(*Log)(const FString&) = &FCsLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties matching interface: 
	// - StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
	// - MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	typedef NCsProperty::FLibrary PropertyLibrary;

	bool Success = false;

	// Try FCsData_Skin_VisualStaticMeshAndMaterialImpl
	typedef FCsData_Skin_VisualStaticMeshAndMaterialImpl StructImplType;

	if (StructImplType* ImplAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructImplType>(Ctxt, Object, Object->GetClass(), Name::VisualStaticMeshAndMaterialImpl, nullptr))
	{
		return ImplAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		FCsStaticMesh* MeshPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsStaticMesh>(Ctxt, Object, Object->GetClass(), Name::Mesh, nullptr);
		FCsTArrayMaterialnterface* MaterialsPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsTArrayMaterialnterface>(Ctxt, Object, Object->GetClass(), Name::Materials, nullptr);

		if (MeshPtr &&
			MaterialsPtr)
		{
			if (!MeshPtr->IsValid(Ctxt))
				return false;

			if (!MaterialsPtr->IsValid(Ctxt))
				return false;

			CS_IS_PTR_NULL(Component)

			Component->SetStaticMesh(MeshPtr->Get());

			typedef NCsMaterial::FLibrary MaterialLibrary;

			return MaterialLibrary::SetSafe(Ctxt, Component, MaterialsPtr->Get());
		}
	}

	typedef NCsObject::FLibrary ObjectLibrary;

	UE_LOG(LogCs, Warning, TEXT("%s: Failed to find any properties from %s for interface:"), *Ctxt, *(ObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCs, Warning, TEXT("%s: - StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualStaticMeshAndMaterialImpl with name: VisualStaticMeshAndMaterialImpl."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsStaticMesh with name: Mesh."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsTArrayMaterialnterface with name: Materials."), *Ctxt);

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

	void(*Log)(const FString&) = &FCsLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties matching interface: 
	// - SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
	// - MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
	typedef NCsProperty::FLibrary PropertyLibrary;

	bool Success = false;

	// Try FCsData_Skin_VisualSkeletalMeshAndMaterialImpl
	typedef FCsData_Skin_VisualSkeletalMeshAndMaterialImpl StructImplType;

	if (StructImplType* ImplAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructImplType>(Ctxt, Object, Object->GetClass(), Name::VisualSkeletalMeshAndMaterialImpl, nullptr))
	{
		return ImplAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		FCsSkeletalMesh* MeshPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsSkeletalMesh>(Ctxt, Object, Object->GetClass(), Name::Mesh, nullptr);
		FCsTArrayMaterialnterface* MaterialsPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsTArrayMaterialnterface>(Ctxt, Object, Object->GetClass(), Name::Materials, nullptr);

		if (MeshPtr &&
			MaterialsPtr)
		{
			if (!MeshPtr->IsValid(Ctxt))
				return false;

			if (!MaterialsPtr->IsValid(Ctxt))
				return false;

			CS_IS_PTR_NULL(Component)

			Component->SetSkeletalMesh(MeshPtr->Get());

			typedef NCsMaterial::FLibrary MaterialLibrary;

			return MaterialLibrary::SetSafe(Ctxt, Component, MaterialsPtr->Get());
		}
	}

	typedef NCsObject::FLibrary ObjectLibrary;

	UE_LOG(LogCs, Warning, TEXT("%s: Failed to find any properties from %s for interface:"), *Ctxt, *(ObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCs, Warning, TEXT("%s: - SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualSkeletalMeshAndMaterialImpl with name: VisualSkeletalMeshAndMaterialImpl."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsSkeletalMesh with name: Mesh."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsTArrayMaterialnterface with name: Materials."), *Ctxt);

	return false;
}