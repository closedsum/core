// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Character/Script/CsScriptLibrary_AI_Character.h"
#include "CsAI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Character/CsLibrary_AI_Character.h"

// Cached
#pragma region

namespace NCsScriptLibraryAICharacter
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Character, Blackboard_SetValueAsObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Character, Blackboard_SetValueAsClass);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Character, Blackboard_SetValueAsVector);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AI_Character::UCsScriptLibrary_AI_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Blackboard
#pragma region

#define BlackboardLibrary NCsAI::NCharacter::NBlackboard::FLibrary

bool UCsScriptLibrary_AI_Character::Blackboard_SetValueAsObject(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue)
{
	using namespace NCsScriptLibraryAICharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetValueAsObject : Context;

	return BlackboardLibrary::SetSafeValue(Ctxt, Character, KeyName, ObjectValue);
}

bool UCsScriptLibrary_AI_Character::Blackboard_SetValueAsClass(const FString& Context, const ACharacter* Character, const FName& KeyName, UClass* ClassValue)
{
	using namespace NCsScriptLibraryAICharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetValueAsClass : Context;

	return BlackboardLibrary::SetSafeValue(Ctxt, Character, KeyName, ClassValue);
}

bool UCsScriptLibrary_AI_Character::Blackboard_SetValueAsVector(const FString& Context, const ACharacter* Character, const FName& KeyName, const FVector& VectorValue)
{
	using namespace NCsScriptLibraryAICharacter::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Blackboard_SetValueAsVector : Context;

	return BlackboardLibrary::SetSafeValue(Ctxt, Character, KeyName, VectorValue);
}

#undef BlackboardLibrary

#pragma endregion Blackboard