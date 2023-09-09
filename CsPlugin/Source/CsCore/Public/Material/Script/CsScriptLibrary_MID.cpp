// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Material/Script/CsScriptLibrary_MID.h"
#include "CsCore.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"

// Cached
#pragma region

namespace NCsScriptLibraryMID
{
	namespace NCached
	{
		namespace Str
		{
			// Scalar
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MID, SetScalarParameterValue);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MID, SetArrayScalarParameterValue);
			// Anim
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MID, PlayAnim);
			// Vector
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MID, SetVectorParameterValue);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_MID::UCsScriptLibrary_MID(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Scalar
#pragma region

bool UCsScriptLibrary_MID::SetScalarParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value)
{
	using namespace NCsScriptLibraryMID::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetScalarParameterValue : Context;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	return MIDLibrary::SetSafeScalarParameterValue(Ctxt, MID, ParamName, Value);
}

bool UCsScriptLibrary_MID::SetArrayScalarParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value)
{
	using namespace NCsScriptLibraryMID::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetArrayScalarParameterValue : Context;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	return MIDLibrary::SetSafeScalarParameterValue(Ctxt, MIDs, ParamName, Value);
}

#pragma endregion Scalar

// Vector
#pragma region

bool UCsScriptLibrary_MID::SetVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value)
{
	using namespace NCsScriptLibraryMID::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetVectorParameterValue : Context;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	return MIDLibrary::SetSafeVectorParameterValue(Ctxt, MID, ParamName, Value);
}

#pragma endregion Vector

// Anim
#pragma region

FCsRoutineHandle UCsScriptLibrary_MID::PlayAnim(const FString& Context, const UObject* WorldContextObject, const FCsMaterialAnim_Params& Params)
{
	using namespace NCsScriptLibraryMID::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::PlayAnim : Context;

	FCsMaterialAnim_Params* ParamsPtr = const_cast<FCsMaterialAnim_Params*>(&Params);

	ParamsPtr->ConditionalSetSafeMIDs(Ctxt);
	ParamsPtr->Anim.UpdateFromPlaybackAndPlayRate();

	if (!Params.IsValid(Ctxt))
		return FCsRoutineHandle::Invalid;

	// Copy script params to native params.
	typedef NCsMaterial::NMID::FLibrary MIDLibrary;
	typedef NCsMaterial::NAnim::NParams::FResource ParamsResourceType;
	typedef NCsMaterial::NAnim::NParams::FParams ParamsType;

	ParamsResourceType* ParmsContainer = MIDLibrary::Get().AllocateAnimParams();
	ParamsType* Parms				   = ParmsContainer->Get();

	Params.CopyToParamsAsValue(Parms);

	return MIDLibrary::SafePlayAnim(Ctxt, WorldContextObject, ParmsContainer);
}

#pragma endregion Anim