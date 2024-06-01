// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Material/Parameter/Collection/Script/CsScriptLibrary_MPC.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Material/Parameter/Collection/CsLibrary_Material_Parameter_Collection.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_MPC)

// Cached
#pragma region

namespace NCsScriptLibraryMPC
{
	namespace NCached
	{
		namespace Str
		{
			// Scalar
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, SetScalarParameterValue);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, SetScalarParameterValue_UpdateMaterials);
			// Vector
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, SetVectorParameterValue);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, SetVectorParameterValue_UpdateMaterials);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, UpdateMaterial);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, UpdateMaterials);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_MPC::UCsScriptLibrary_MPC(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Scalar
#pragma region

bool UCsScriptLibrary_MPC::SetScalarParameterValue(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const float& Value)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetScalarParameterValue : Context;

#if WITH_EDITOR
	typedef NCsMaterial::NParameter::NCollection::FLibrary MPCLibrary;

	return MPCLibrary::Editor_SetSafeScalarParameter(Ctxt, Collection, ParamName, Value);
#else
	checkf(0, TEXT("%s: should ONLY be called in Editor"), *Context);
	return true;
#endif // #if WITH_EDITOR
}

bool UCsScriptLibrary_MPC::SetScalarParameterValue_UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const float& Value)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetScalarParameterValue_UpdateMaterials : Context;

#if WITH_EDITOR
	typedef NCsMaterial::NParameter::NCollection::FLibrary MPCLibrary;

	return MPCLibrary::Editor_SetSafeScalarParameter_UpdateMaterials(Ctxt, Collection, ParamName, Value);
#else
	checkf(0, TEXT("%s: should ONLY be called in Editor"), *Context);
	return true;
#endif // #if WITH_EDITOR
}

#pragma endregion Scalar

// Vector
#pragma region

bool UCsScriptLibrary_MPC::SetVectorParameterValue(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const FLinearColor& Value)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetVectorParameterValue : Context;

#if WITH_EDITOR
	typedef NCsMaterial::NParameter::NCollection::FLibrary MPCLibrary;

	return MPCLibrary::Editor_SetSafeVectorParameter(Ctxt, Collection, ParamName, Value);
#else
	checkf(0, TEXT("%s: should ONLY be called in Editor"), *Context);
	return true;
#endif // #if WITH_EDITOR
}

bool UCsScriptLibrary_MPC::SetVectorParameterValue_UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const FLinearColor& Value)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetVectorParameterValue_UpdateMaterials : Context;

#if WITH_EDITOR
	typedef NCsMaterial::NParameter::NCollection::FLibrary MPCLibrary;

	return MPCLibrary::Editor_SetSafeVectorParameter_UpdateMaterials(Ctxt, Collection, ParamName, Value);
#else
	checkf(0, TEXT("%s: should ONLY be called in Editor"), *Context);
	return true;
#endif // #if WITH_EDITOR
}

#pragma endregion Vector

bool UCsScriptLibrary_MPC::UpdateMaterial(const FString& Context, UMaterialParameterCollection* Collection, UMaterial* Material)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::UpdateMaterial : Context;

#if WITH_EDITOR
	typedef NCsMaterial::NParameter::NCollection::FLibrary MPCLibrary;

	return MPCLibrary::Editor_SafeUpdateMaterial(Ctxt, Collection, Material);
#else
	checkf(0, TEXT("%s: should ONLY be called in Editor"), *Context);
	return true;
#endif // #if WITH_EDITOR
}

bool UCsScriptLibrary_MPC::UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, TArray<UMaterial*>& Materials)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::UpdateMaterials : Context;

#if WITH_EDITOR
	typedef NCsMaterial::NParameter::NCollection::FLibrary MPCLibrary;

	return MPCLibrary::Editor_SafeUpdateMaterials(Ctxt, Collection, Materials);
#else
	checkf(0, TEXT("%s: should ONLY be called in Editor"), *Context);
	return true;
#endif // #if WITH_EDITOR
}