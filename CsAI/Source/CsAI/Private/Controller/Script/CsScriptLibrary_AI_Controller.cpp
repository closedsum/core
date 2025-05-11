// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Controller/Script/CsScriptLibrary_AI_Controller.h"
#include "CsAI.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Controller/CsLibrary_AI_Controller.h"
#include "Library/CsLibrary_Valid.h"
// AI
#include "AIController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_AI_Controller)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_AI_Controller)
	// Blackboard
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, GetBlackboard)
		// Object
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetObject)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectBySelector)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectBySelectorChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetObject2)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectBySelector2)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectChecked2)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetObjectBySelectorChecked2)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetObject)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetObjectBySelector)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetObjectChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetObjectBySelectorChecked)
		// Pawn
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetPawn)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnBySelector)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnBySelectorChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetPawn2)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnBySelector2)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnChecked2)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetPawnBySelectorChecked2)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetPawn)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetPawnBySelector)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetPawnChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetPawnBySelectorChecked)
		// Enum
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetEnum)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetEnumBySelector)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetEnumChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_SetEnumBySelectorChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetEnum)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetEnumBySelector)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetEnumChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, Blackboard_GetEnumBySelectorChecked)

	// Move To
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, MoveTo)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, MoveToChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, SimpleMoveTo_ActorByTag)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Controller, GetDefaultNavigationFilterClass)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_AI_Controller::UCsScriptLibrary_AI_Controller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define SET_LOG_WARNING void(*Log)(const FString&) = &NCsAI::FLog::Warning;
#define LogError &NCsAI::FLog::Error

// Blackboard
#pragma region

UBlackboardComponent* UCsScriptLibrary_AI_Controller::GetBlackboard(const FString& Context, const AAIController* Controller)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetBlackboard);

	return CsAIControllerLibrary::GetSafeBlackboard(Ctxt, Controller);
}

	// Object
#pragma region

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObject(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetObject);

	return CsAIBlackboardLibrary::SetSafeObject(Ctxt, Controller, KeyName, ObjectValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetObjectBySelector);

	return CsAIBlackboardLibrary::SetSafeObject(Ctxt, Controller, KeySelector, ObjectValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetObjectChecked);

	CS_SCRIPT_SET_CHECKED(CsAIBlackboardLibrary::SetObjectChecked(Ctxt, Controller, KeyName, ObjectValue), CsAIBlackboardLibrary::SetSafeObject(Ctxt, Controller, KeyName, ObjectValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetObjectBySelectorChecked);

	CS_SCRIPT_SET_CHECKED(CsAIBlackboardLibrary::SetObjectChecked(Ctxt, Controller, KeySelector, ObjectValue), CsAIBlackboardLibrary::SetSafeObject(Ctxt, Controller, KeySelector, ObjectValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObject2(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetObject2);

	return CsAIBlackboardLibrary::SetSafeObject(Ctxt, Controller, KeyName, ObjectValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectBySelector2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetObjectBySelector2);

	return CsAIBlackboardLibrary::SetSafeObject2(Ctxt, Controller, KeySelector, ObjectValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectChecked2(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetObjectChecked2);

	CS_SCRIPT_SET_CHECKED(CsAIBlackboardLibrary::SetObjectChecked(Ctxt, Controller, KeyName, ObjectValue), CsAIBlackboardLibrary::SetSafeObject2(Ctxt, Controller, KeyName, ObjectValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetObjectBySelectorChecked2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetObjectBySelectorChecked2);

	CS_SCRIPT_SET_CHECKED(CsAIBlackboardLibrary::SetObjectChecked(Ctxt, Controller, KeySelector, ObjectValue), CsAIBlackboardLibrary::SetSafeObject2(Ctxt, Controller, KeySelector, ObjectValue, LogError))
}

UObject* UCsScriptLibrary_AI_Controller::Blackboard_GetObject(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetObject);

	return CsAIBlackboardLibrary::GetSafeObject(Ctxt, Controller, KeyName, OutSuccess);
}

UObject* UCsScriptLibrary_AI_Controller::Blackboard_GetObjectBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetObjectBySelector);

	return CsAIBlackboardLibrary::GetSafeObject(Ctxt, Controller, KeySelector, OutSuccess);
}

UObject* UCsScriptLibrary_AI_Controller::Blackboard_GetObjectChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetObjectChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsAIBlackboardLibrary::GetObjectChecked(Ctxt, Controller, KeyName), CsAIBlackboardLibrary::GetSafeObject(Ctxt, Controller, KeyName, OutSuccess, LogError));
}

UObject* UCsScriptLibrary_AI_Controller::Blackboard_GetObjectBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetObjectBySelectorChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsAIBlackboardLibrary::GetObjectChecked(Ctxt, Controller, KeySelector), CsAIBlackboardLibrary::GetSafeObject(Ctxt, Controller, KeySelector, OutSuccess, LogError));
}

#pragma endregion Object

	// Pawn
#pragma region

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawn(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetPawn);

	return CsAIBlackboardLibrary::SetSafePawn(Ctxt, Controller, KeyName, PawnValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetPawnBySelector);

	return CsAIBlackboardLibrary::SetSafePawn(Ctxt, Controller, KeySelector, PawnValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetPawnChecked);

	CS_SCRIPT_SET_CHECKED(CsAIBlackboardLibrary::SetPawnChecked(Ctxt, Controller, KeyName, PawnValue), CsAIBlackboardLibrary::SetSafePawn(Ctxt, Controller, KeyName, PawnValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetPawnBySelectorChecked);

	CS_SCRIPT_SET_CHECKED(CsAIBlackboardLibrary::SetPawnChecked(Ctxt, Controller, KeySelector, PawnValue), CsAIBlackboardLibrary::SetSafePawn(Ctxt, Controller, KeySelector, PawnValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawn2(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetPawn2);

	return CsAIBlackboardLibrary::SetSafePawn2(Ctxt, Controller, KeyName, PawnValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnBySelector2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetPawnBySelector2);

	return CsAIBlackboardLibrary::SetSafePawn2(Ctxt, Controller, KeySelector, PawnValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnChecked2(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetPawnChecked2);

	CS_SCRIPT_SET_CHECKED(CsAIBlackboardLibrary::SetPawnChecked(Ctxt, Controller, KeyName, PawnValue), CsAIBlackboardLibrary::SetSafePawn2(Ctxt, Controller, KeyName, PawnValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetPawnBySelectorChecked2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetPawnBySelectorChecked2);

	CS_SCRIPT_SET_CHECKED(CsAIBlackboardLibrary::SetPawnChecked(Ctxt, Controller, KeySelector, PawnValue), CsAIBlackboardLibrary::SetSafePawn2(Ctxt, Controller, KeySelector, PawnValue, LogError))
}

APawn* UCsScriptLibrary_AI_Controller::Blackboard_GetPawn(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetPawn);

	return CsAIBlackboardLibrary::GetSafePawn(Ctxt, Controller, KeyName, OutSuccess);
}

APawn* UCsScriptLibrary_AI_Controller::Blackboard_GetPawnBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetPawnBySelector);

	return CsAIBlackboardLibrary::GetSafePawn(Ctxt, Controller, KeySelector, OutSuccess);
}

APawn* UCsScriptLibrary_AI_Controller::Blackboard_GetPawnChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetPawnChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsAIBlackboardLibrary::GetPawnChecked(Ctxt, Controller, KeyName), CsAIBlackboardLibrary::GetSafePawn(Ctxt, Controller, KeyName, OutSuccess, LogError));
}

APawn* UCsScriptLibrary_AI_Controller::Blackboard_GetPawnBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetPawnBySelectorChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsAIBlackboardLibrary::GetPawnChecked(Ctxt, Controller, KeySelector), CsAIBlackboardLibrary::GetSafePawn(Ctxt, Controller, KeySelector, OutSuccess, LogError));
}

#pragma endregion Pawn

	// Enum
#pragma region

bool UCsScriptLibrary_AI_Controller::Blackboard_SetEnum(const FString& Context, const AAIController* Controller, const FName& KeyName, const uint8& EnumValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetEnum);

	return CsAIBlackboardLibrary::SetSafeEnum(Ctxt, Controller, KeyName, EnumValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetEnumBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetEnumBySelector);

	return CsAIBlackboardLibrary::SetSafeEnum(Ctxt, Controller, KeySelector, EnumValue);
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetEnumChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const uint8& EnumValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetEnumChecked);

	CS_SCRIPT_SET_CHECKED(CsAIBlackboardLibrary::SetEnumChecked(Ctxt, Controller, KeyName, EnumValue), CsAIBlackboardLibrary::SetSafeEnum(Ctxt, Controller, KeyName, EnumValue, LogError))
}

bool UCsScriptLibrary_AI_Controller::Blackboard_SetEnumBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetEnumBySelectorChecked);

	CS_SCRIPT_SET_CHECKED(CsAIBlackboardLibrary::SetEnumChecked(Ctxt, Controller, KeySelector, EnumValue), CsAIBlackboardLibrary::SetSafeEnum(Ctxt, Controller, KeySelector, EnumValue, LogError))
}

uint8 UCsScriptLibrary_AI_Controller::Blackboard_GetEnum(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetEnum);

	return CsAIBlackboardLibrary::GetSafeEnum(Ctxt, Controller, KeyName, OutSuccess);
}

uint8 UCsScriptLibrary_AI_Controller::Blackboard_GetEnumBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetEnumBySelector);

	return CsAIBlackboardLibrary::GetSafeEnum(Ctxt, Controller, KeySelector, OutSuccess);
}

uint8 UCsScriptLibrary_AI_Controller::Blackboard_GetEnumChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetEnumChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsAIBlackboardLibrary::GetEnumChecked(Ctxt, Controller, KeyName), CsAIBlackboardLibrary::GetSafeEnum(Ctxt, Controller, KeyName, OutSuccess, LogError));
}

uint8 UCsScriptLibrary_AI_Controller::Blackboard_GetEnumBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetEnumBySelectorChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsAIBlackboardLibrary::GetEnumChecked(Ctxt, Controller, KeySelector), CsAIBlackboardLibrary::GetSafeEnum(Ctxt, Controller, KeySelector, OutSuccess, LogError));
}

#pragma endregion Enum

#pragma endregion Blackboard

// Move To
#pragma region

FCsPathFollowingRequestResult UCsScriptLibrary_AI_Controller::MoveTo(const FString& Context, AAIController* Controller, const FCsAIMoveRequest& MoveRequest)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(MoveTo);

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

FCsPathFollowingRequestResult UCsScriptLibrary_AI_Controller::MoveToChecked(const FString& Context, AAIController* Controller, const FCsAIMoveRequest& MoveRequest, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(MoveToChecked);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_RET_VALUE2(Controller, FCsPathFollowingRequestResult())

	FAIMoveRequest Request;
	MoveRequest.CopyTo(Request);

	FPathFollowingRequestResult Result = Controller->MoveTo(Request);

	FCsPathFollowingRequestResult RequestResult;
	RequestResult.MoveId = Result.MoveId;
	RequestResult.Code   = Result.Code;

	return RequestResult;
}

bool UCsScriptLibrary_AI_Controller::SimpleMoveTo_ActorByTag(const FString& Context, APawn* Pawn, const FName& Tag)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(SimpleMoveTo_ActorByTag);	

	return CsAIControllerLibrary::SafeSimpleMoveTo_ActorByTag(Ctxt, Pawn, Tag);
}

#pragma endregion Move To

TSubclassOf<UNavigationQueryFilter> UCsScriptLibrary_AI_Controller::GetDefaultNavigationFilterClass(const FString& Context, AAIController* Controller)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetDefaultNavigationFilterClass);

	if (!Controller)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Controller is NULL."), *Ctxt);
		return nullptr;
	}
	return Controller->GetDefaultNavigationFilterClass();
}

#undef SET_LOG_WARNING
#undef LogError