// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Character/CsLibrary_AI_Character.h"

// Library
#include "Blackboard/CsLibrary_Blackboard.h"
#include "Library/CsLibrary_Valid.h"
// Character
#include "GameFramework/Character.h"
// AI
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

namespace NCsAI
{
	namespace NCharacter
	{
		// Controller
		#pragma region

		AAIController* FLibrary::GetControllerChecked(const FString& Context, const ACharacter* Character)
		{
			CS_IS_PENDING_KILL_CHECKED(Character)

			AController* Controller = Character->GetController();

			CS_IS_PENDING_KILL_CHECKED(Controller);

			return CS_CAST_CHECKED(Controller, AController, AAIController);
		}

		AAIController* FLibrary::GetSafeController(const FString& Context, const ACharacter* Character, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
		{
			CS_IS_PENDING_KILL_RET_NULL(Character)

			AController* Controller = Character->GetController();

			CS_IS_PENDING_KILL_RET_NULL(Controller);

			return CS_CAST(Controller, AController, AAIController);
		}

		#pragma endregion Controller

		UBlackboardComponent* FLibrary::GetBlackboardChecked(const FString& Context, const ACharacter* Character)
		{
			AAIController* Controller		= GetControllerChecked(Context, Character);
			UBrainComponent* BrainComponent = Controller->GetBrainComponent();

			CS_IS_PENDING_KILL_CHECKED(BrainComponent);

			UBlackboardComponent* Blackboard = BrainComponent->GetBlackboardComponent();

			CS_IS_PENDING_KILL_CHECKED(Blackboard);
			return Blackboard;
		}

		UBlackboardComponent* FLibrary::GetSafeBlackboard(const FString& Context, const ACharacter* Character, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
		{
			AAIController* Controller = GetSafeController(Context, Character, Log);

			if (!Controller)
				return nullptr;

			UBrainComponent* BrainComponent = Controller->GetBrainComponent();

			CS_IS_PENDING_KILL_RET_NULL(BrainComponent);

			UBlackboardComponent* Blackboard = BrainComponent->GetBlackboardComponent();

			CS_IS_PENDING_KILL_RET_NULL(Blackboard);
			return Blackboard;
		}

		namespace NBlackboard
		{
			// Set
			#pragma region

			#define BlackbloardLibrary NCsBlackboard::FLibrary

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackbloardLibrary::IsKey_ObjectChecked(Context, Blackboard, KeyName));

				Blackboard->SetValueAsObject(KeyName, ObjectValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackbloardLibrary::SafeIsKey_Object(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsObject(KeyName, ObjectValue);
					return true;
				}
				return false;
			}

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, UClass* ClassValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackbloardLibrary::IsKey_ClassChecked(Context, Blackboard, KeyName));

				Blackboard->SetValueAsClass(KeyName, ClassValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, UClass* ClassValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackbloardLibrary::SafeIsKey_Class(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsClass(KeyName, ClassValue);
					return true;
				}
				return false;
			}

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const uint8& EnumValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackbloardLibrary::IsKey_EnumChecked(Context, Blackboard, KeyName));

				Blackboard->SetValueAsEnum(KeyName, EnumValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const uint8& EnumValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackbloardLibrary::SafeIsKey_Enum(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsEnum(KeyName, EnumValue);
					return true;
				}
				return false;
			}

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const int32& IntValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackbloardLibrary::IsKey_IntChecked(Context, Blackboard, KeyName));

				Blackboard->SetValueAsInt(KeyName, IntValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const int32& IntValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackbloardLibrary::SafeIsKey_Int(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsInt(KeyName, IntValue);
					return true;
				}
				return false;
			}

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const float& FloatValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackbloardLibrary::IsKey_FloatChecked(Context, Blackboard, KeyName));

				Blackboard->SetValueAsFloat(KeyName, FloatValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const float& FloatValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackbloardLibrary::SafeIsKey_Float(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsFloat(KeyName, FloatValue);
					return true;
				}
				return false;
			}

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const bool& BoolValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackbloardLibrary::IsKey_BoolChecked(Context, Blackboard, KeyName));

				Blackboard->SetValueAsBool(KeyName, BoolValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const bool& BoolValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackbloardLibrary::SafeIsKey_Bool(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsBool(KeyName, BoolValue);
					return true;
				}
				return false;
			}

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FString& StringValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackbloardLibrary::IsKey_StringChecked(Context, Blackboard, KeyName));

				Blackboard->SetValueAsString(KeyName, StringValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FString& StringValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackbloardLibrary::SafeIsKey_String(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsString(KeyName, StringValue);
					return true;
				}
				return false;
			}

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FName& NameValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackbloardLibrary::IsKey_NameChecked(Context, Blackboard, KeyName));

				Blackboard->SetValueAsName(KeyName, NameValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FName& NameValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackbloardLibrary::SafeIsKey_Name(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsName(KeyName, NameValue);
					return true;
				}
				return false;
			}

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FVector3d& VectorValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackbloardLibrary::IsKey_VectorChecked(Context, Blackboard, KeyName));

				Blackboard->SetValueAsVector(KeyName, VectorValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FVector3d& VectorValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackbloardLibrary::SafeIsKey_Vector(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsVector(KeyName, VectorValue);
					return true;
				}
				return false;
			}

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FRotator3d& RotatorValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackbloardLibrary::IsKey_RotatorChecked(Context, Blackboard, KeyName));

				Blackboard->SetValueAsRotator(KeyName, RotatorValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FRotator3d& RotatorValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackbloardLibrary::SafeIsKey_Rotator(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsRotator(KeyName, RotatorValue);
					return true;
				}
				return false;
			}

			#undef BlackboardLibrary

			#pragma endregion Set
		}
	}
}