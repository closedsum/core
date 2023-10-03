// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Controller/Script/CsScriptLibrary_AI_Controller.h"
#include "CsAI.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Controller/CsLibrary_AI_Controller.h"
// AI
#include "AIController.h"

// Cached
#pragma region

namespace NCsScriptLibraryAIController
{
	namespace NCached
	{
		namespace Str
		{
			// Blackboard
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, GetBlackboard);
				// Object
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectBySelector);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectBySelectorChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetObject2);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectBySelector2);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectChecked2);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectBySelectorChecked2);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetObjectBySelector);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetObjectChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetObjectBySelectorChecked);
				// Pawn
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetPawn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnBySelector);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnBySelectorChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetPawn2);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnBySelector2);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnChecked2);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnBySelectorChecked2);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetPawn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetPawnBySelector);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetPawnChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetPawnBySelectorChecked);
				// Enum
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetEnum);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetEnumBySelector);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetEnumChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_SetEnumBySelectorChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetEnum);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetEnumBySelector);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetEnumChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, Blackboard_GetEnumBySelectorChecked);

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, MoveTo);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Controller, GetDefaultNavigationFilterClass);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AI_Controller::UCsScriptLibrary_AI_Controller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define LogError &NCsAI::FLog::Error
#define AIControllerLibrary NCsAI::NController::FLibrary

// Blackboard
#pragma region

UBlackboardComponent* UCsScriptLibrary_AI_Controller::GetBlackboard(const FString& Context, const AAIController* Controller)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetBlackboard : Context;

	return AIControllerLibrary::GetSafeBlackboard(Ctxt, Controller);
}

#define BlackboardLibrary NCsAI::NController::NBlackboard::FLibrary

	// Object
#pragma region

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObject(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetObject : Context;

	return BlackboardLibrary::SetSafeObject(Ctxt, Controller, KeyName, ObjectValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetObjectBySelector : Context;

	return BlackboardLibrary::SetSafeObject(Ctxt, Controller, KeySelector, ObjectValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetObjectChecked : Context;

	CS_SCRIPT_SET_CHECKED(BlackboardLibrary::SetObjectChecked(Ctxt, Controller, KeyName, ObjectValue), BlackboardLibrary::SetSafeObject(Ctxt, Controller, KeyName, ObjectValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetObjectBySelectorChecked : Context;

	CS_SCRIPT_SET_CHECKED(BlackboardLibrary::SetObjectChecked(Ctxt, Controller, KeySelector, ObjectValue), BlackboardLibrary::SetSafeObject(Ctxt, Controller, KeySelector, ObjectValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObject2(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetObject2 : Context;

	return BlackboardLibrary::SetSafeObject(Ctxt, Controller, KeyName, ObjectValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectBySelector2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetObjectBySelector2 : Context;

	return BlackboardLibrary::SetSafeObject2(Ctxt, Controller, KeySelector, ObjectValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectChecked2(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetObjectChecked2 : Context;

	CS_SCRIPT_SET_CHECKED(BlackboardLibrary::SetObjectChecked(Ctxt, Controller, KeyName, ObjectValue), BlackboardLibrary::SetSafeObject2(Ctxt, Controller, KeyName, ObjectValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectBySelectorChecked2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetObjectBySelectorChecked2 : Context;

	CS_SCRIPT_SET_CHECKED(BlackboardLibrary::SetObjectChecked(Ctxt, Controller, KeySelector, ObjectValue), BlackboardLibrary::SetSafeObject2(Ctxt, Controller, KeySelector, ObjectValue, LogError))
}


UObject* UCsScriptLibrary_AI_Controller::Blackboard_GetObject(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetObject : Context;

	return BlackboardLibrary::GetSafeObject(Ctxt, Controller, KeyName, OutSuccess);
}

UObject* UCsScriptLibrary_AI_Controller::Blackboard_GetObjectBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetObjectBySelector : Context;

	return BlackboardLibrary::GetSafeObject(Ctxt, Controller, KeySelector, OutSuccess);
}

UObject* UCsScriptLibrary_AI_Controller::Blackboard_GetObjectChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetObjectChecked : Context;

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(BlackboardLibrary::GetObjectChecked(Ctxt, Controller, KeyName), BlackboardLibrary::GetSafeObject(Ctxt, Controller, KeyName, OutSuccess, LogError));
}

UObject* UCsScriptLibrary_AI_Controller::Blackboard_GetObjectBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetObjectBySelectorChecked : Context;

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(BlackboardLibrary::GetObjectChecked(Ctxt, Controller, KeySelector), BlackboardLibrary::GetSafeObject(Ctxt, Controller, KeySelector, OutSuccess, LogError));
}

#pragma endregion Object

	// Pawn
#pragma region

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawn(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetPawn : Context;

	return BlackboardLibrary::SetSafePawn(Ctxt, Controller, KeyName, PawnValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetPawnBySelector : Context;

	return BlackboardLibrary::SetSafePawn(Ctxt, Controller, KeySelector, PawnValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetPawnChecked : Context;

	CS_SCRIPT_SET_CHECKED(BlackboardLibrary::SetPawnChecked(Ctxt, Controller, KeyName, PawnValue), BlackboardLibrary::SetSafePawn(Ctxt, Controller, KeyName, PawnValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetPawnBySelectorChecked : Context;

	CS_SCRIPT_SET_CHECKED(BlackboardLibrary::SetPawnChecked(Ctxt, Controller, KeySelector, PawnValue), BlackboardLibrary::SetSafePawn(Ctxt, Controller, KeySelector, PawnValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawn2(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetPawn2 : Context;

	return BlackboardLibrary::SetSafePawn2(Ctxt, Controller, KeyName, PawnValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnBySelector2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetPawnBySelector2 : Context;

	return BlackboardLibrary::SetSafePawn2(Ctxt, Controller, KeySelector, PawnValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnChecked2(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetPawnChecked2 : Context;

	CS_SCRIPT_SET_CHECKED(BlackboardLibrary::SetPawnChecked(Ctxt, Controller, KeyName, PawnValue), BlackboardLibrary::SetSafePawn2(Ctxt, Controller, KeyName, PawnValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnBySelectorChecked2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetPawnBySelectorChecked2 : Context;

	CS_SCRIPT_SET_CHECKED(BlackboardLibrary::SetPawnChecked(Ctxt, Controller, KeySelector, PawnValue), BlackboardLibrary::SetSafePawn2(Ctxt, Controller, KeySelector, PawnValue, LogError))
}

APawn* UCsScriptLibrary_AI_Controller::Blackboard_GetPawn(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetPawn : Context;

	return BlackboardLibrary::GetSafePawn(Ctxt, Controller, KeyName, OutSuccess);
}

APawn* UCsScriptLibrary_AI_Controller::Blackboard_GetPawnBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetPawnBySelector : Context;

	return BlackboardLibrary::GetSafePawn(Ctxt, Controller, KeySelector, OutSuccess);
}

APawn* UCsScriptLibrary_AI_Controller::Blackboard_GetPawnChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetPawnChecked : Context;

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(BlackboardLibrary::GetPawnChecked(Ctxt, Controller, KeyName), BlackboardLibrary::GetSafePawn(Ctxt, Controller, KeyName, OutSuccess, LogError));
}

APawn* UCsScriptLibrary_AI_Controller::Blackboard_GetPawnBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetPawnBySelectorChecked : Context;

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(BlackboardLibrary::GetPawnChecked(Ctxt, Controller, KeySelector), BlackboardLibrary::GetSafePawn(Ctxt, Controller, KeySelector, OutSuccess, LogError));
}

#pragma endregion Pawn

	// Enum
#pragma region

bool UCsScriptLibrary_AI_Controller::Blackboard_SetEnum(const FString& Context, const AAIController* Controller, const FName& KeyName, const uint8& EnumValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetEnum : Context;

	return BlackboardLibrary::SetSafeEnum(Ctxt, Controller, KeyName, EnumValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetEnumBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetEnumBySelector : Context;

	return BlackboardLibrary::SetSafeEnum(Ctxt, Controller, KeySelector, EnumValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetEnumChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const uint8& EnumValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetEnumChecked : Context;

	CS_SCRIPT_SET_CHECKED(BlackboardLibrary::SetEnumChecked(Ctxt, Controller, KeyName, EnumValue), BlackboardLibrary::SetSafeEnum(Ctxt, Controller, KeyName, EnumValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetEnumBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetEnumBySelectorChecked : Context;

	CS_SCRIPT_SET_CHECKED(BlackboardLibrary::SetEnumChecked(Ctxt, Controller, KeySelector, EnumValue), BlackboardLibrary::SetSafeEnum(Ctxt, Controller, KeySelector, EnumValue, LogError))
}

uint8 UCsScriptLibrary_AI_Controller::Blackboard_GetEnum(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetEnum : Context;

	return BlackboardLibrary::GetSafeEnum(Ctxt, Controller, KeyName, OutSuccess);
}

uint8 UCsScriptLibrary_AI_Controller::Blackboard_GetEnumBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetEnumBySelector : Context;

	return BlackboardLibrary::GetSafeEnum(Ctxt, Controller, KeySelector, OutSuccess);
}

uint8 UCsScriptLibrary_AI_Controller::Blackboard_GetEnumChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetEnumChecked : Context;

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(BlackboardLibrary::GetEnumChecked(Ctxt, Controller, KeyName), BlackboardLibrary::GetSafeEnum(Ctxt, Controller, KeyName, OutSuccess, LogError));
}

uint8 UCsScriptLibrary_AI_Controller::Blackboard_GetEnumBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_GetEnumBySelectorChecked : Context;

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(BlackboardLibrary::GetEnumChecked(Ctxt, Controller, KeySelector), BlackboardLibrary::GetSafeEnum(Ctxt, Controller, KeySelector, OutSuccess, LogError));
}

#pragma endregion Enum

#undef BlackboardLibrary

#pragma endregion Blackboard

FCsPathFollowingRequestResult UCsScriptLibrary_AI_Controller::MoveTo(const FString& Context, AAIController* Controller, const FCsAIMoveRequest& MoveRequest)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::MoveTo : Context;

	if (!Controller)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Controller is NULL."), *Ctxt);
		return FCsPathFollowingRequestResult();
	}

	// TODO: Check Is Valid
	FAIMoveRequest Request;
	MoveRequest.CopyTo(Request);

	FPathFollowingRequestResult Result = Controller->MoveTo(Request);

	FCsPathFollowingRequestResult RequestResult;
	RequestResult.MoveId = Result.MoveId;
	RequestResult.Code   = Result.Code;

	return RequestResult;
}

TSubclassOf<UNavigationQueryFilter> UCsScriptLibrary_AI_Controller::GetDefaultNavigationFilterClass(const FString& Context, AAIController* Controller)
{
	using namespace NCsScriptLibraryAIController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDefaultNavigationFilterClass : Context;

	if (!Controller)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Controller is NULL."), *Ctxt);
		return nullptr;
	}
	return Controller->GetDefaultNavigationFilterClass();
}

#undef LogError
#undef AIControllerLibrary