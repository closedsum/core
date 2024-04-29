// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Actor/Script/CsScriptLibrary_Actor_Movement.h"
// Types
#include "CsMacro_Misc.h"
// CVar
#include "Script/CsCVars_Script.h"
// Library
#include "Actor/CsLibrary_Actor_Movement.h"
#include "Library/CsLibrary_Valid.h"

// Cached
#pragma region

namespace NCsScriptLibraryActorMovement
{
	namespace NCached
	{
		namespace Str
		{
			// Move
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, MoveByInterp);
		}
	}
}

#pragma endregion Cached

#define USING_NS_CACHED using namespace NCsScriptLibraryActorMovement::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryActorMovement::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define SET_LOG_WARNING void(*Log)(const FString&) = &FCsLog::Warning;
#define ActorLibrary NCsActor::NMovement::FLibrary

UCsScriptLibrary_Actor_Movement::UCsScriptLibrary_Actor_Movement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Move
#pragma region

FCsRoutineHandle UCsScriptLibrary_Actor_Movement::MoveByInterp(const FString& Context, const UObject* WorldContextObject, const FCsMoveByInterp_Params& Params)
{
	CONDITIONAL_SET_CTXT(MoveByInterp);
	SET_LOG_WARNING

	FCsMoveByInterp_Params* ParamsPtr = const_cast<FCsMoveByInterp_Params*>(&Params);

	ParamsPtr->ConditionalSetSafeMoveObject(Context, WorldContextObject);
	ParamsPtr->ConditionalSetSafeDestinationObject(Context, WorldContextObject);

	CS_IS_VALID_RET_VALUE2(Params, FCsRoutineHandle::Invalid)

	// Copy script params to native params.
	typedef NCsMovement::NTo::NInterp::NParams::FResource ParamsResourceType;
	typedef NCsMovement::NTo::NInterp::NParams::FParams ParamsType;

	ParamsResourceType* ParmsContainer = ActorLibrary::Get().AllocateMoveByInterpParams();
	ParamsType* Parms				   = ParmsContainer->Get();

	Params.CopyToParamsAsValue(Parms);

	return ActorLibrary::SafeMoveByInterp(Ctxt, WorldContextObject, ParmsContainer);
}

#pragma endregion Move

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef SET_LOG_WARNING
#undef ActorLibrary