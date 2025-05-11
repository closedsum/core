// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Character/Script/CsScriptLibrary_AI_Character.h"
#include "CsAI.h"

// Library
#include "Character/CsLibrary_AI_Character.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_AI_Character)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_AI_Character)
	// Controller
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Character, GetController)
	// Blackboard
		// Object
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Character, Blackboard_SetValueAsObject)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Character, Blackboard_SetValueBySelectorAsObject)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Character, Blackboard_GetValueAsObject)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Character, Blackboard_GetValueBySelectorAsObject)
		// Class
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Character, Blackboard_SetValueAsClass)
		// Vector
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_AI_Character, Blackboard_SetValueAsVector)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_AI_Character::UCsScriptLibrary_AI_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Controller
#pragma region

AAIController* UCsScriptLibrary_AI_Character::GetController(const FString& Context, const ACharacter* Character)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetController);

	return CsAICharacterLibrary::GetSafeController(Ctxt, Character);
}

#pragma endregion Controller

// Blackboard
#pragma region

	// Object
#pragma region

bool UCsScriptLibrary_AI_Character::Blackboard_SetValueAsObject(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetValueAsObject);

	return CsAICharacterBlackboardLibrary::SetSafeValue(Ctxt, Character, KeyName, ObjectValue);
}

bool UCsScriptLibrary_AI_Character::Blackboard_SetValueBySelectorAsObject(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetValueBySelectorAsObject);

	return CsAICharacterBlackboardLibrary::SetSafeValue(Ctxt, Character, KeySelector, ObjectValue);
}

UObject* UCsScriptLibrary_AI_Character::Blackboard_GetValueAsObject(const FString& Context, const ACharacter* Character, const FName& KeyName)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetValueAsObject);

	return CsAICharacterBlackboardLibrary::GetSafeObject(Ctxt, Character, KeyName);
}

UObject* UCsScriptLibrary_AI_Character::Blackboard_GetValueBySelectorAsObject(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_GetValueBySelectorAsObject);

	return CsAICharacterBlackboardLibrary::GetSafeObject(Ctxt, Character, KeySelector);
}

#pragma endregion Object

bool UCsScriptLibrary_AI_Character::Blackboard_SetValueAsClass(const FString& Context, const ACharacter* Character, const FName& KeyName, UClass* ClassValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetValueAsClass);

	return CsAICharacterBlackboardLibrary::SetSafeValue(Ctxt, Character, KeyName, ClassValue);
}

bool UCsScriptLibrary_AI_Character::Blackboard_SetValueAsVector(const FString& Context, const ACharacter* Character, const FName& KeyName, const FVector& VectorValue)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Blackboard_SetValueAsVector);

	return CsAICharacterBlackboardLibrary::SetSafeValue(Ctxt, Character, KeyName, VectorValue);
}

#pragma endregion Blackboard