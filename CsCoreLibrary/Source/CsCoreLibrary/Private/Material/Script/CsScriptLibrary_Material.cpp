// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Material/Script/CsScriptLibrary_Material.h"
#include "CsCoreLibrary.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
// Material
#include "Materials/MaterialInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Material)

// Cached
#pragma region

namespace NCsScriptLibraryMaterial
{
	namespace NCached
	{
		namespace Str
		{
			// Load
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, LoadByStringPaths);
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, GetByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, GetSoftObjectAsStringByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, GetArrayByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, GetSoftObjectArrayAsStringByPath);
			// Set
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, SetAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, SetAt);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, Set);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, SetFromStruct);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, SetFromObject);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Material::UCsScriptLibrary_Material(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryMaterial::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryMaterial::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Load
#pragma region

UMaterialInterface* UCsScriptLibrary_Material::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return CsMaterialLibrary::SafeLoad(Ctxt, Path);
}

UMaterialInterface* UCsScriptLibrary_Material::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return CsMaterialLibrary::SafeLoad(Ctxt, Path);
}

bool UCsScriptLibrary_Material::LoadByStringPaths(const FString& Context, const TArray<FString>& Paths, TArray<UMaterialInterface*>& OutMaterials)
{
	CONDITIONAL_SET_CTXT(LoadByStringPaths);

	return CsMaterialLibrary::SafeLoad(Ctxt, Paths, OutMaterials);
}

#pragma endregion Load

// Get
#pragma region

UMaterialInterface* UCsScriptLibrary_Material::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByPath);

	return CsMaterialLibrary::GetSafe(Ctxt, Object, Path, OutSuccess);
}

bool UCsScriptLibrary_Material::GetSoftObjectAsStringByPath(const FString& Context, UObject* Object, const FString& Path, FString& OutPath, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetSoftObjectAsStringByPath);

	return CsMaterialLibrary::GetSafe(Ctxt, Object, Path, OutPath, OutSuccess);
}

bool UCsScriptLibrary_Material::GetArrayByPath(const FString& Context, UObject* Object, const FString& Path, TArray<UMaterialInterface*>& OutArray, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetArrayByPath);

	return CsMaterialLibrary::GetSafe(Ctxt, Object, Path, OutArray, OutSuccess);
}

bool UCsScriptLibrary_Material::GetSoftObjectArrayAsStringByPath(const FString& Context, UObject* Object, const FString& Path, TArray<FString>& OutArray, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetSoftObjectArrayAsStringByPath);

	return CsMaterialLibrary::GetSafe(Ctxt, Object, Path, OutArray, OutSuccess);
}

#pragma endregion Get

// Set
#pragma region

bool UCsScriptLibrary_Material::SetAll(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material)
{
	CONDITIONAL_SET_CTXT(SetAll);

	return CsMaterialLibrary::SetSafe(Ctxt, Component, Material);
}

bool UCsScriptLibrary_Material::SetAt(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index)
{
	CONDITIONAL_SET_CTXT(SetAt);

	return CsMaterialLibrary::SetSafe(Ctxt, Component, Material, Index);
}

bool UCsScriptLibrary_Material::Set(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials)
{
	CONDITIONAL_SET_CTXT(Set);

	return CsMaterialLibrary::SetSafe(Ctxt, Component, Materials);
}

bool UCsScriptLibrary_Material::SetFromStruct(const FString& Context, const FCsTArrayMaterialInterface& Materials, UPrimitiveComponent* Component)
{
	CONDITIONAL_SET_CTXT(SetFromStruct);

	return Materials.SetSafe(Ctxt, Component);
}

bool UCsScriptLibrary_Material::SetFromObject(const FString& Context, UObject* Object, const FName& PropertyName, UPrimitiveComponent* Component)
{
	CONDITIONAL_SET_CTXT(SetFromObject);

	void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties of type: FCsTArrayMaterialInterface or TArray<UMaterialInterface*> and name: PropertyName.

	// Try FCsTArrayMaterialInterface
	typedef FCsTArrayMaterialInterface StructSliceType;

	if (StructSliceType* SliceAsStruct = CsPropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Ctxt, Object, Object->GetClass(), PropertyName, nullptr))
	{
		return SliceAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		TArray<UMaterialInterface*>* MaterialsPtr = CsPropertyLibrary::GetArrayObjectPropertyValuePtr<UMaterialInterface>(Ctxt, Object, Object->GetClass(), PropertyName, nullptr);

		if (MaterialsPtr)
		{
			if (!Component)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Component is NULL."), *Ctxt));
				return false;
			}
			return CsMaterialLibrary::SetSafe(Ctxt, Component, *MaterialsPtr);
		}
	}
	
	UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Failed to find any properties from %s for Property: %s of type: TArray<UMaterialInterface*>"), *Ctxt, *(CsObjectLibrary::PrintObjectAndClass(Object)), *(PropertyName.ToString()));
	UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: - Failed to get struct property of type: FCsTArrayMaterialInterface."), *Ctxt);
	UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: - Failed to get array property of type: TArray<UMaterialInterface*>."), *Ctxt);

	return false;
}

#pragma endregion Set

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT