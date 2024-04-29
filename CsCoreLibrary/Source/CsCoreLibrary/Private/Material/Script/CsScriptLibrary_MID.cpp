// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Material/Script/CsScriptLibrary_MID.h"

// Types
#include "CsMacro_Misc.h"
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

#define USING_NS_CACHED using namespace NCsScriptLibraryMID::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryMID::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define MIDLibrary NCsMaterial::NMID::FLibrary

// Scalar
#pragma region

bool UCsScriptLibrary_MID::SetScalarParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value)
{
	CONDITIONAL_SET_CTXT(SetScalarParameterValue);

	return MIDLibrary::SetSafeScalarParameterValue(Ctxt, MID, ParamName, Value);
}

bool UCsScriptLibrary_MID::SetArrayScalarParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value)
{
	CONDITIONAL_SET_CTXT(SetArrayScalarParameterValue);

	return MIDLibrary::SetSafeScalarParameterValue(Ctxt, MIDs, ParamName, Value);
}

#pragma endregion Scalar

// Vector
#pragma region

bool UCsScriptLibrary_MID::SetVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value)
{
	CONDITIONAL_SET_CTXT(SetVectorParameterValue);

	return MIDLibrary::SetSafeVectorParameterValue(Ctxt, MID, ParamName, Value);
}

#pragma endregion Vector

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef MIDLibrary