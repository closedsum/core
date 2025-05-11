// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
// Log
#include "Utility/CsAILog.h"

class ACharacter;
class UObject;
class UClass;
class AAIController;
class UBlackboardComponent;

namespace NCsAI
{
	namespace NCharacter
	{
		/**
		* Library of functions related to Character
		*/
		struct CSAI_API FLibrary final
		{
		private:

			CS_DECLARE_STATIC_LOG_LEVEL

		// Controller
		#pragma region
		public:

			/**
			* Get the AI Controller associated with Character
			* 
			* @param Context	The calling context.
			* @param Character
			* return			AI Controller
			*/
			static AAIController* GetControllerChecked(const FString& Context, const ACharacter* Character);

			/**
			* Safely get the AI Controller associated with Character
			*
			* @param Context	The calling context.
			* @param Character
			* return			AI Controller
			*/
			static AAIController* GetSafeController(const FString& Context, const ACharacter* Character, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		#pragma endregion Controller

		public:

			/**
			* Get the Blackboard associated with Character.
			* 
			* @param Context	The calling context.
			* @param Character
			* return			Blackboard
			*/
			static UBlackboardComponent* GetBlackboardChecked(const FString& Context, const ACharacter* Character);

			/**
			* Safely get the Blackboard associated with Character.
			*
			* @param Context	The calling context.
			* @param Character
			* @param Log		(optional)
			* return			Blackboard
			*/
			static UBlackboardComponent* GetSafeBlackboard(const FString& Context, const ACharacter* Character, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		};
	}
}

using CsAICharacterLibrary = NCsAI::NCharacter::FLibrary;

namespace NCsAI
{
	namespace NCharacter
	{
		namespace NBlackboard
		{
			/**
			* Library of functions related to Blackboard
			*/
			struct CSAI_API FLibrary final
			{
			private:

				CS_DECLARE_STATIC_LOG_LEVEL

			public:

				FORCEINLINE static UBlackboardComponent* GetComponentChecked(const FString& Context, const ACharacter* Character)
				{
					typedef NCsAI::NCharacter::FLibrary CharacterLibrary;

					return CharacterLibrary::GetBlackboardChecked(Context, Character);
				}

				FORCEINLINE static UBlackboardComponent* GetSafeComponent(const FString& Context, const ACharacter* Character, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					typedef NCsAI::NCharacter::FLibrary CharacterLibrary;

					return CharacterLibrary::GetSafeBlackboard(Context, Character, Log);
				}

			// Set
			#pragma region
				
				// Object
			#pragma region
			public:

				/**
				* Set the Character's Blackboard Object Key value associated with KeyName.
				* 
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* @parma ObjectValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue);
	
				/**
				* Set the Character's Blackboard Object Key value associated with KeySelector.
				*
				* @param Context	The calling context.
				* @param Character
				* @param KeySelector
				* @parma ObjectValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue);

				/**
				* Safely set the Character's Blackboard Object Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma ObjectValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Safely set the Character's Blackboard Object Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeySelector
				* @parma ObjectValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion Object

				// Class
			#pragma region 
			public:

				/**
				* Set the Character's Blackboard Class Key value associated with KeyName.
				* 
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* @parma ClassValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, UClass* ClassValue);

				/**
				* Safely set the Character's Blackboard Class Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma ClassValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, UClass* ClassValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion Class

				// Enum
			#pragma region
			public:

				/**
				* Set the Character's Blackboard Enum (uint8) Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* @parma EnumValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const uint8& EnumValue);

				/**
				* Safely set the Character's Blackboard Enum (uint8) Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma EnumValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const uint8& EnumValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion Enum

				// Int
			#pragma region
			public:

				/**
				* Set the Character's Blackboard Int (int32) Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* @parma IntValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const int32& IntValue);

				/**
				* Safely set the Character's Blackboard Int (int32) Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma IntValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const int32& IntValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion Int

				// Float
			#pragma region
			public:

				/**
				* Set the Character's Blackboard Float Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* @parma FloatValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const float& FloatValue);

				/**
				* Safely set the Character's Blackboard Float Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma FloatValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const float& FloatValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion Float

				// Bool
			#pragma region
			public:

				/**
				* Set the Character's Blackboard Bool Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* @parma BoolValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const bool& BoolValue);

				/**
				* Safely set the Character's Blackboard Bool Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma BoolValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const bool& BoolValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion Bool

				// String
			#pragma region
			public:

				/**
				* Set the Character's Blackboard String Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* @parma StringValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FString& StringValue);

				/**
				* Safely set the Character's Blackboard String Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma StringValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FString& StringValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion String

				// Name
			#pragma region
			public:

				/**
				* Set the Character's Blackboard Name Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* @parma NameValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FName& NameValue);

				/**
				* Safely set the Character's Blackboard Name Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma NameValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FName& NameValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion Name

				// Vector (Vector3d)
			#pragma region
			public:

				/**
				* Set the Character's Blackboard Vector (Vector3d) Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* @parma VectorValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FVector3d& VectorValue);

				/**
				* Safely set the Character's Blackboard Vector (Vector3d) Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma VectorValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FVector3d& VectorValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion Vector (Vector3d)

				// Rotator (Rotator3d)
			#pragma region
			public:

				/**
				* Set the Character's Blackboard Rotator (Rotator3d) Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* @parma RotatorValue
				*/
				static void SetValueChecked(const FString& Context, const ACharacter* Character, const FName& KeyName, const FRotator3d& RotatorValue);

				/**
				* Safely set the Character's Blackboard Rotator (Rotator3d) Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma RotatorValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FRotator3d& RotatorValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion Rotator (Rotator3d)

			#pragma endregion Set

			// Get
			#pragma region
			public:

				// Object
			#pragma region
			public:

				/**
				* Get the Character's Blackboard Object Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Character
				* @param KeyName
				* return			Object.
				*/
				static UObject* GetObjectChecked(const FString& Context, const ACharacter* Character, const FName& KeyName);

				/**
				* Get the Character's Blackboard Object Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeySelector
				* return				Object.
				*/
				static UObject* GetObjectChecked(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector);

				/**
				* Safely get the Character's Blackboard Object Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @param Log			(optional)
				* return				Object.
				*/
				static UObject* GetSafeObject(const FString& Context, const ACharacter* Character, const FName& KeyName, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Safely get the Character's Blackboard Object Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeySelector
				* @param Log			(optional)
				* return				Object.
				*/
				static UObject* GetSafeObject(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion Object

			#pragma endregion Get
			};
		}
	}
}

using CsAICharacterBlackboardLibrary = NCsAI::NCharacter::NBlackboard::FLibrary;