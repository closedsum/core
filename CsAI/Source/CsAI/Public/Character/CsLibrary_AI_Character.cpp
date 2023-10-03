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
			#define BlackboardLibrary NCsBlackboard::FLibrary

			// Set
			#pragma region

				// Object
			#pragma region

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Object(Context, Blackboard, KeyName));

				Blackboard->SetValueAsObject(KeyName, ObjectValue);
			}

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Object(Context, Blackboard, KeySelector));

				Blackboard->SetValueAsObject(KeySelector.SelectedKeyName, ObjectValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Object(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsObject(KeyName, ObjectValue);
					return true;
				}
				return false;
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Object(Context, Blackboard, KeySelector, Log))
						return false;
					Blackboard->SetValueAsObject(KeySelector.SelectedKeyName, ObjectValue);
					return true;
				}
				return false;
			}

			#pragma endregion Object

				// Class
			#pragma region 

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, UClass* ClassValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Class(Context, Blackboard, KeyName));

				Blackboard->SetValueAsClass(KeyName, ClassValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, UClass* ClassValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Class(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsClass(KeyName, ClassValue);
					return true;
				}
				return false;
			}

			#pragma endregion Class

				// Enum
			#pragma region

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const uint8& EnumValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Enum(Context, Blackboard, KeyName));

				Blackboard->SetValueAsEnum(KeyName, EnumValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const uint8& EnumValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Enum(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsEnum(KeyName, EnumValue);
					return true;
				}
				return false;
			}

			#pragma endregion Enum

				// Int
			#pragma region

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const int32& IntValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Int(Context, Blackboard, KeyName));

				Blackboard->SetValueAsInt(KeyName, IntValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const int32& IntValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Int(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsInt(KeyName, IntValue);
					return true;
				}
				return false;
			}

			#pragma endregion Int

				// Float
			#pragma region

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const float& FloatValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Float(Context, Blackboard, KeyName));

				Blackboard->SetValueAsFloat(KeyName, FloatValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const float& FloatValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Float(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsFloat(KeyName, FloatValue);
					return true;
				}
				return false;
			}

			#pragma endregion Float

				// Bool
			#pragma region

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const bool& BoolValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Bool(Context, Blackboard, KeyName));

				Blackboard->SetValueAsBool(KeyName, BoolValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const bool& BoolValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Bool(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsBool(KeyName, BoolValue);
					return true;
				}
				return false;
			}

			#pragma endregion Bool

				// String
			#pragma region

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FString& StringValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_String(Context, Blackboard, KeyName));

				Blackboard->SetValueAsString(KeyName, StringValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FString& StringValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_String(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsString(KeyName, StringValue);
					return true;
				}
				return false;
			}

			#pragma endregion String

				// Name
			#pragma region

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FName& NameValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Name(Context, Blackboard, KeyName));

				Blackboard->SetValueAsName(KeyName, NameValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FName& NameValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Name(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsName(KeyName, NameValue);
					return true;
				}
				return false;
			}

			#pragma endregion Name

				// Vector (Vector3d)
			#pragma region

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FVector3d& VectorValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Vector(Context, Blackboard, KeyName));

				Blackboard->SetValueAsVector(KeyName, VectorValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FVector3d& VectorValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Vector(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsVector(KeyName, VectorValue);
					return true;
				}
				return false;
			}

			#pragma endregion Vector (Vector3d)

				// Rotator (Rotator3d)
			#pragma region

			void FLibrary::SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FRotator3d& RotatorValue)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Rotator(Context, Blackboard, KeyName));

				Blackboard->SetValueAsRotator(KeyName, RotatorValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FRotator3d& RotatorValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Rotator(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsRotator(KeyName, RotatorValue);
					return true;
				}
				return false;
			}

			#pragma endregion Rotator (Rotator3d)

			#pragma endregion Set

			// Get
			#pragma region

				// Object
			#pragma region

			UObject* FLibrary::GetObjectChecked(const FString& Context, const ACharacter* Character, const FName& KeyName)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Object(Context, Blackboard, KeyName));

				return Blackboard->GetValueAsObject(KeyName);
			}

			UObject* FLibrary::GetObjectChecked(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector)
			{
				UBlackboardComponent* Blackboard = GetComponentChecked(Context, Character);

				check(BlackboardLibrary::IsKeyChecked_Object(Context, Blackboard, KeySelector));

				return Blackboard->GetValueAsObject(KeySelector.SelectedKeyName);
			}

			UObject* FLibrary::GetSafeObject(const FString& Context, const ACharacter* Character, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Object(Context, Blackboard, KeyName, Log))
						return nullptr;		
					return Blackboard->GetValueAsObject(KeyName);;
				}
				return nullptr;
			}

			UObject* FLibrary::GetSafeObject(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = GetSafeComponent(Context, Character, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Object(Context, Blackboard, KeySelector, Log))
						return nullptr;
					return Blackboard->GetValueAsObject(KeySelector.SelectedKeyName);
				}
				return nullptr;
			}

			#pragma endregion Object

			#pragma endregion Get

			#undef BlackboardLibrary
		}
	}
}