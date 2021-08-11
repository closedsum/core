// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Material/Script/CsScriptLibrary_Material.h"
#include "CsCore.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"

// Cached
#pragma region

namespace NCsScriptLibraryMaterial
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, LoadByStringPaths);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, SetAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, SetAt);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, Set);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, SetFromStruct);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, SetFromObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, PlayAnim);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Material::UCsScriptLibrary_Material(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Load
#pragma region

UMaterialInterface* UCsScriptLibrary_Material::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SafeLoad(Context, Path);
}

UMaterialInterface* UCsScriptLibrary_Material::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SafeLoad(Ctxt, Path);
}

bool UCsScriptLibrary_Material::LoadByStringPaths(const FString& Context, const TArray<FString>& Paths, TArray<UMaterialInterface*>& OutMaterials)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPaths : Context;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SafeLoad(Ctxt, Paths, OutMaterials);
}

#pragma endregion Load

// Set
#pragma region

bool UCsScriptLibrary_Material::SetAll(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetAll : Context;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Material);
}

bool UCsScriptLibrary_Material::SetAt(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetAt : Context;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Material, Index);
}

bool UCsScriptLibrary_Material::Set(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Set : Context;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Materials);
}

bool UCsScriptLibrary_Material::SetFromStruct(const FString& Context, const FCsTArrayMaterialInterface& Materials, UPrimitiveComponent* Component)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromStruct : Context;

	return Materials.SetSafe(Ctxt, Component);
}

bool UCsScriptLibrary_Material::SetFromObject(const FString& Context, UObject* Object, const FName& PropertyName, UPrimitiveComponent* Component)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromObject : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	// Check for properties of type: FCsTArrayMaterialInterface or TArray<UMaterialInterface*> and name: PropertyName.
	typedef NCsProperty::FLibrary PropertyLibrary;

	// Try FCsTArrayMaterialInterface
	typedef FCsTArrayMaterialInterface StructSliceType;

	if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Ctxt, Object, Object->GetClass(), PropertyName, nullptr))
	{
		return SliceAsStruct->SetSafe(Ctxt, Component);
	}
	// Try individual properties
	else
	{
		TArray<UMaterialInterface*>* MaterialsPtr = PropertyLibrary::GetArrayObjectPropertyValuePtr<UMaterialInterface>(Ctxt, Object, Object->GetClass(), PropertyName, nullptr);

		if (MaterialsPtr)
		{
			if (!Component)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Component is NULL."), *Ctxt));
				return false;
			}

			typedef NCsMaterial::FLibrary MaterialLibrary;

			return MaterialLibrary::SetSafe(Ctxt, Component, *MaterialsPtr);
		}
	}
	
	typedef NCsObject::FLibrary ObjectLibrary;

	UE_LOG(LogCs, Warning, TEXT("%s: Failed to find any properties from %s for Property: %s of type: TArray<UMaterialInterface*>"), *Ctxt, *(ObjectLibrary::PrintObjectAndClass(Object)), *(PropertyName.ToString()));
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get struct property of type: FCsTArrayMaterialInterface."), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - OR"), *Ctxt);
	UE_LOG(LogCs, Warning, TEXT("%s: - Failed to get array property of type: TArray<UMaterialInterface*>."), *Ctxt);

	return false;
}

#pragma endregion Set

// Anim
#pragma region

FCsRoutineHandle UCsScriptLibrary_Material::PlayAnim(const FString& Context, const UObject* WorldContextObject, const FCsMaterialAnim_Params& Params)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::PlayAnim : Context;

	FCsMaterialAnim_Params* ParamsPtr = const_cast<FCsMaterialAnim_Params*>(&Params);

	ParamsPtr->ConditionalSetSafeMID(Ctxt);
	ParamsPtr->Anim.UpdateFromPlaybackAndPlayRate();

	if (!Params.IsValid(Ctxt))
		return FCsRoutineHandle::Invalid;

	// Copy script params to native params.
	typedef NCsMaterial::NMID::FLibrary MaterialLibrary;
	typedef NCsMaterial::NAnim::NParams::FResource ParamsResourceType;
	typedef NCsMaterial::NAnim::NParams::FParams ParamsType;

	ParamsResourceType* ParmsContainer = MaterialLibrary::Get().AllocateAnimParams();
	ParamsType* Parms				   = ParmsContainer->Get();

	Params.CopyToParamsAsValue(Parms);

	return MaterialLibrary::SafePlayAnim(Ctxt, WorldContextObject, ParmsContainer);
}

#pragma endregion Anim