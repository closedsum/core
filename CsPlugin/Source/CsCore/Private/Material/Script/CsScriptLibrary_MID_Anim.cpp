// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Material/Script/CsScriptLibrary_MID_Anim.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Material/CsLibrary_Material_Anim.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_MID_Anim)

// Cached
#pragma region

namespace NCsScriptLibraryMIDAnim
{
	namespace NCached
	{
		namespace Str
		{
			// Anim
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MID, PlayAnim);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_MID_Anim::UCsScriptLibrary_MID_Anim(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryMIDAnim::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryMIDAnim::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Anim
#pragma region

FCsRoutineHandle UCsScriptLibrary_MID_Anim::PlayAnim(const FString& Context, const UObject* WorldContextObject, const FCsMaterialAnim_Params& Params)
{
	CONDITIONAL_SET_CTXT(PlayAnim);

	FCsMaterialAnim_Params* ParamsPtr = const_cast<FCsMaterialAnim_Params*>(&Params);

	ParamsPtr->ConditionalSetSafeMIDs(Ctxt);
	ParamsPtr->Anim.UpdateFromPlaybackAndPlayRate();

	if (!Params.IsValid(Ctxt))
		return FCsRoutineHandle::Invalid;

	// Copy script params to native params.
	typedef NCsMaterial::NMID::NAnim::FLibrary MIDLibrary;
	typedef NCsMaterial::NAnim::NParams::FResource ParamsResourceType;
	typedef NCsMaterial::NAnim::NParams::FParams ParamsType;

	ParamsResourceType* ParmsContainer = MIDLibrary::Get().AllocateAnimParams();
	ParamsType* Parms				   = ParmsContainer->Get();

	Params.CopyToParamsAsValue(Parms);

	return MIDLibrary::SafePlayAnim(Ctxt, WorldContextObject, ParmsContainer);
}

#pragma endregion Anim

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT