// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Controller/CsLibrary_AI_Controller.h"

// Library
#include "Blackboard/CsLibrary_Blackboard.h"
#include "Library/CsLibrary_Valid.h"
// AI
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

namespace NCsAI
{
	namespace NController
	{
		UBlackboardComponent* FLibrary::GetBlackboardChecked(const FString& Context, const AAIController* Controller)
		{
			CS_IS_PENDING_KILL_CHECKED(Controller);

			UBrainComponent* BrainComponent = Controller->GetBrainComponent();

			CS_IS_PENDING_KILL_CHECKED(BrainComponent);

			UBlackboardComponent* Blackboard = BrainComponent->GetBlackboardComponent();

			CS_IS_PENDING_KILL_CHECKED(Blackboard);
			return Blackboard;
		}

		UBlackboardComponent* FLibrary::GetSafeBlackboard(const FString& Context, const AAIController* Controller, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
		{
			CS_IS_PENDING_KILL_RET_NULL(Controller);

			UBrainComponent* BrainComponent = Controller->GetBrainComponent();

			CS_IS_PENDING_KILL_RET_NULL(BrainComponent);

			UBlackboardComponent* Blackboard = BrainComponent->GetBlackboardComponent();

			CS_IS_PENDING_KILL_RET_NULL(Blackboard);
			return Blackboard;
		}

		namespace NBlackboard
		{
			#define ControllerLibrary NCsAI::NController::FLibrary
			#define BlackboardLibrary NCsBlackboard::FLibrary

			// Set
			#pragma region

				// Object
			#pragma region

			void FLibrary::SetObjectChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetObjectChecked(Context, Blackboard, KeyName, ObjectValue);
			}

			void FLibrary::SetObjectChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetObjectChecked(Context, Blackboard, KeySelector, ObjectValue);
			}

			bool FLibrary::SetSafeObject(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::SetSafeObject(Context, Blackboard, KeyName, ObjectValue, Log);
				return false;
			}

			bool FLibrary::SetSafeObject(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::SetSafeObject(Context, Blackboard, KeySelector, ObjectValue, Log);
				return false;
			}

			void FLibrary::SetObjectChecked2(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetObjectChecked2(Context, Blackboard, KeyName, ObjectValue);
			}

			void FLibrary::SetObjectChecked2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetObjectChecked2(Context, Blackboard, KeySelector, ObjectValue);
			}

			bool FLibrary::SetSafeObject2(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::SetSafeObject2(Context, Blackboard, KeyName, ObjectValue, Log);
				return false;
			}

			bool FLibrary::SetSafeObject2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::SetSafeObject2(Context, Blackboard, KeySelector, ObjectValue, Log);
				return false;
			}


			#pragma endregion Object

				// Pawn
			#pragma region

			void FLibrary::SetPawnChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetPawnChecked(Context, Blackboard, KeyName, PawnValue);
			}

			void FLibrary::SetPawnChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetPawnChecked(Context, Blackboard, KeySelector, PawnValue);
			}

			bool FLibrary::SetSafePawn(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
				{
					if (!BlackboardLibrary::SetSafePawn(Context, Blackboard, KeyName, PawnValue, Log))
						return false;
				}
				return false;
			}

			bool FLibrary::SetSafePawn(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
				{
					if (!BlackboardLibrary::SetSafePawn(Context, Blackboard, KeySelector, PawnValue, Log))
						return false;
				}
				return false;
			}

			void FLibrary::SetPawnChecked2(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetPawnChecked2(Context, Blackboard, KeyName, PawnValue);
			}

			void FLibrary::SetPawnChecked2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetPawnChecked2(Context, Blackboard, KeySelector, PawnValue);
			}

			bool FLibrary::SetSafePawn2(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
				{
					if (!BlackboardLibrary::SetSafePawn2(Context, Blackboard, KeyName, PawnValue, Log))
						return false;
				}
				return false;
			}

			bool FLibrary::SetSafePawn2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
				{
					if (!BlackboardLibrary::SetSafePawn2(Context, Blackboard, KeySelector, PawnValue, Log))
						return false;
				}
				return false;
			}

			#pragma endregion Pawn

				// Class
			#pragma region 

			void FLibrary::SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, UClass* ClassValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				check(BlackboardLibrary::IsKeyChecked_Class(Context, Blackboard, KeyName));

				Blackboard->SetValueAsClass(KeyName, ClassValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, UClass* ClassValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
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

			void FLibrary::SetEnumChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const uint8& EnumValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetEnumChecked(Context, Blackboard, KeyName, EnumValue);
			}

			void FLibrary::SetEnumChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetEnumChecked(Context, Blackboard, KeySelector, EnumValue);
			}

			bool FLibrary::SetSafeEnum(const FString& Context, const AAIController* Controller, const FName& KeyName, const uint8& EnumValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::SetSafeEnum(Context, Blackboard, KeyName, EnumValue, Log);
				return false;
			}

			bool FLibrary::SetSafeEnum(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::SetSafeEnum(Context, Blackboard, KeySelector, EnumValue, Log);
				return false;
			}

			#pragma endregion Enum

				// Int
			#pragma region

			void FLibrary::SetIntChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const int32& IntValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				check(BlackboardLibrary::IsKeyChecked_Int(Context, Blackboard, KeyName));

				Blackboard->SetValueAsInt(KeyName, IntValue);
			}

			void FLibrary::SetIntChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const int32& IntValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::SetIntChecked(Context, Blackboard, KeySelector, IntValue);
			}

			bool FLibrary::SetSafeInt(const FString& Context, const AAIController* Controller, const FName& KeyName, const int32& IntValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
				{
					if (!BlackboardLibrary::SafeIsKey_Int(Context, Blackboard, KeyName, Log))
						return false;
					Blackboard->SetValueAsInt(KeyName, IntValue);
					return true;
				}
				return false;
			}

			bool FLibrary::SetSafeInt(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const int32& IntValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::SetSafeInt(Context, Blackboard, KeySelector, IntValue, Log);
				return false;
			}

			void FLibrary::IncrementIntChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const int32& Amount /*=1*/)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				BlackboardLibrary::IncrementIntChecked(Context, Blackboard, KeyName, Amount);
			}

			bool FLibrary::SafeIncrementInt(const FString& Context, const AAIController* Controller, const FName& KeyName, const int32& Amount /*=1*/, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::SafeIncrementInt(Context, Blackboard, KeyName, Amount, Log);
				return false;
			}

			#pragma endregion Int

				// Float
			#pragma region

			void FLibrary::SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const float& FloatValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				check(BlackboardLibrary::IsKeyChecked_Float(Context, Blackboard, KeyName));

				Blackboard->SetValueAsFloat(KeyName, FloatValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const float& FloatValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
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

			void FLibrary::SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const bool& BoolValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				check(BlackboardLibrary::IsKeyChecked_Bool(Context, Blackboard, KeyName));

				Blackboard->SetValueAsBool(KeyName, BoolValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const bool& BoolValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
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

			void FLibrary::SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const FString& StringValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				check(BlackboardLibrary::IsKeyChecked_String(Context, Blackboard, KeyName));

				Blackboard->SetValueAsString(KeyName, StringValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const FString& StringValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
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

			void FLibrary::SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const FName& NameValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				check(BlackboardLibrary::IsKeyChecked_Name(Context, Blackboard, KeyName));

				Blackboard->SetValueAsName(KeyName, NameValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const FName& NameValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
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

			void FLibrary::SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const FVector3d& VectorValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				check(BlackboardLibrary::IsKeyChecked_Vector(Context, Blackboard, KeyName));

				Blackboard->SetValueAsVector(KeyName, VectorValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const FVector3d& VectorValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
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

			void FLibrary::SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const FRotator3d& RotatorValue)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				check(BlackboardLibrary::IsKeyChecked_Rotator(Context, Blackboard, KeyName));

				Blackboard->SetValueAsRotator(KeyName, RotatorValue);
			}

			bool FLibrary::SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const FRotator3d& RotatorValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
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

			UObject* FLibrary::GetObjectChecked(const FString& Context, const AAIController* Controller, const FName& KeyName)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				return BlackboardLibrary::GetObjectChecked(Context, Blackboard, KeyName);
			}

			UObject* FLibrary::GetObjectChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				return BlackboardLibrary::GetObjectChecked(Context, Blackboard, KeySelector);
			}

			UObject* FLibrary::GetSafeObject(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				OutSuccess = false;

				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::GetSafeObject(Context, Blackboard, KeyName, OutSuccess, Log);
				return nullptr;
			}

			UObject* FLibrary::GetSafeObject(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				OutSuccess = false;

				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::GetSafeObject(Context, Blackboard, KeySelector, OutSuccess, Log);
				return nullptr;
			}

			#pragma endregion Object

				// Pawn
			#pragma region

			APawn* FLibrary::GetPawnChecked(const FString& Context, const AAIController* Controller, const FName& KeyName)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				return BlackboardLibrary::GetPawnChecked(Context, Blackboard, KeyName);
			}

			APawn* FLibrary::GetPawnChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				return BlackboardLibrary::GetPawnChecked(Context, Blackboard, KeySelector);
			}

			APawn* FLibrary::GetSafePawn(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				OutSuccess = false;

				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::GetSafePawn(Context, Blackboard, KeyName, OutSuccess, Log);
				return nullptr;
			}

			APawn* FLibrary::GetSafePawn(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				OutSuccess = false;

				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::GetSafePawn(Context, Blackboard, KeySelector, OutSuccess, Log);
				return nullptr;
			}

			#pragma endregion Pawn

				// Enum
			#pragma region

			uint8 FLibrary::GetEnumChecked(const FString& Context, const AAIController* Controller, const FName& KeyName)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				return BlackboardLibrary::GetEnumChecked(Context, Blackboard, KeyName);
			}

			uint8 FLibrary::GetEnumChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				return BlackboardLibrary::GetEnumChecked(Context, Blackboard, KeySelector);
			}

			uint8 FLibrary::GetSafeEnum(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::GetSafeEnum(Context, Blackboard, KeyName, OutSuccess, Log);	
				return 0;
			}

			uint8 FLibrary::GetSafeEnum(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::GetSafeEnum(Context, Blackboard, KeySelector, OutSuccess, Log);
				return 0;
			}

			#pragma endregion Enum

				// Int
			#pragma region

			int32 FLibrary::GetIntChecked(const FString& Context, const AAIController* Controller, const FName& KeyName)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				return BlackboardLibrary::GetIntChecked(Context, Blackboard, KeyName);
			}

			int32 FLibrary::GetIntChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector)
			{
				UBlackboardComponent* Blackboard = ControllerLibrary::GetBlackboardChecked(Context, Controller);

				return BlackboardLibrary::GetIntChecked(Context, Blackboard, KeySelector);
			}

			int32 FLibrary::GetSafeInt(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::GetSafeInt(Context, Blackboard, KeyName, OutSuccess, Log);	
				return 0;
			}

			int32 FLibrary::GetSafeInt(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
			{
				if (UBlackboardComponent* Blackboard = ControllerLibrary::GetSafeBlackboard(Context, Controller, Log))
					return BlackboardLibrary::GetSafeInt(Context, Blackboard, KeySelector, OutSuccess, Log);
				return 0;
			}

			#pragma endregion Int

			#pragma endregion Get

			#undef ControllerLibrary
			#undef BlackboardLibrary
		}
	}
}