// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
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
			static AAIController* GetSafeController(const FString& Context, const ACharacter* Character, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

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
			static UBlackboardComponent* GetSafeBlackboard(const FString& Context, const ACharacter* Character, void(*Log)(const FString&) = &NCsAI::FLog::Warning);
		};

		namespace NBlackboard
		{
			/**
			* Library of functions related to Blackboard
			*/
			struct CSAI_API FLibrary final
			{
			public:

				FORCEINLINE static UBlackboardComponent* GetComponentChecked(const FString& Context, const ACharacter* Character)
				{
					typedef NCsAI::NCharacter::FLibrary CharacterLibrary;

					return CharacterLibrary::GetBlackboardChecked(Context, Character);
				}

				FORCEINLINE static UBlackboardComponent* GetSafeComponent(const FString& Context, const ACharacter* Character, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
				{
					typedef NCsAI::NCharacter::FLibrary CharacterLibrary;

					return CharacterLibrary::GetSafeBlackboard(Context, Character, Log);
				}

			// Set
			#pragma region

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
				* Safely set the Character's Blackboard Object Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Character
				* @param KeyName
				* @parma ObjectValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

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
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, UClass* ClassValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

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
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const uint8& EnumValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

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
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const int32& IntValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

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
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const float& FloatValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

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
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const bool& BoolValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

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
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FString& StringValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

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
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FName& NameValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

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
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FVector3d& VectorValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

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
				static bool SetSafeValue(const FString& Context, const ACharacter* Character, const FName& KeyName, const FRotator3d& RotatorValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Set
			};
		}
	}
}