// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_Material.h"
#include "CsCore.h"

// Library
#include "Material/CsLibrary_Material.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, SetAt);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Material, Set);
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

#pragma endregion Load

// Set
#pragma region

void UCsScriptLibrary_Material::SetAt(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetAt : Context;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Material, Index);
}

void UCsScriptLibrary_Material::Set(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Set : Context;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Materials);
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