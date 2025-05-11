// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
// Log
#include "Utility/CsAILog.h"

class UObject;
class AAIController;
class UBlackboardComponent;
class APawn;

namespace NCsAI
{
	namespace NController
	{
		/**
		* Library of functions related to AIController
		*/
		struct CSAI_API FLibrary final
		{
		private:

			CS_DECLARE_STATIC_LOG_LEVEL
			
		// Get
		#pragma region
		public:

			static AAIController* GetSafe(const FString& Context, APawn* Pawn, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		#pragma endregion Get

		// Blackboard
		#pragma region
		public:

			/**
			* Get the Blackboard associated with Controller.
			* 
			* @param Context	The calling context.
			* @param Controller
			* return			Blackboard
			*/
			static UBlackboardComponent* GetBlackboardChecked(const FString& Context, const AAIController* Controller);

			/**
			* Safely get the Blackboard associated with Controller.
			*
			* @param Context	The calling context.
			* @param Controller
			* @param Log		(optional)
			* return			Blackboard
			*/
			static UBlackboardComponent* GetSafeBlackboard(const FString& Context, const AAIController* Controller, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		#pragma endregion Blackboard

		// Move To
		#pragma region
		public:

			/**
			* Safely Move a Pawn to an Actor by Tag.
			* 
			* @param Context 	The calling context.
			* @param Pawn 		The Pawn to move.
			* @param Tag 		The Tag of the Actor to move to.
			* @param Log		(optional)
			* return			Whether this executed successfully or not.
			*/
			static bool SafeSimpleMoveTo_ActorByTag(const FString& Context, APawn* Pawn, const FName& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		#pragma endregion Move To
		};
	}
}

using CsAIControllerLibrary = NCsAI::NController::FLibrary;

namespace NCsAI
{
	namespace NController
	{
		namespace NBlackboard
		{
			/**
			* Library of functions related to Blackboard
			*/
			struct CSAI_API FLibrary final
			{
			// Set
			#pragma region
				
				// Object
			#pragma region
			public:

				/**
				* Set the Controller's Blackboard Object Key value associated with KeyName.
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma ObjectValue
				*/
				static void SetObjectChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue);
	
				/**
				* Set the Controller's Blackboard Object Key value associated with KeySelector.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeySelector
				* @parma ObjectValue
				*/
				static void SetObjectChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue);

				/**
				* Safely set the Controller's Blackboard Object Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma ObjectValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeObject(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Safely set the Controller's Blackboard Object Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* @parma ObjectValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeObject(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Set the Controller's Blackboard Object Key value associated with KeyName.
				*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma ObjectValue
				*/
				static void SetObjectChecked2(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue);
	
				/**
				* Set the Controller's Blackboard Object Key value associated with KeySelector.
				*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeySelector
				* @parma ObjectValue
				*/
				static void SetObjectChecked2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue);

				/**
				* Safely set the Controller's Blackboard Object Key value associated with KeyName.
				*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
				* 
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma ObjectValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeObject2(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Safely set the Controller's Blackboard Object Key value associated with KeySelector.
				*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
				* 
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* @parma ObjectValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeObject2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Object

				// Pawn
			#pragma region
			public:

				/**
				* Set the Controller's Blackboard Object Key value as a Pawn associated with KeyName.
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma PawnValue
				*/
				static void SetPawnChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue);
	
				/**
				* Set the Controller's Blackboard Object Key value as a Pawn associated with KeySelector.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeySelector
				* @parma PawnValue
				*/
				static void SetPawnChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue);

				/**
				* Safely set the Controller's Blackboard Object Key value as a Pawn associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma PawnValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafePawn(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Safely set the Controller's Blackboard Object Key value as a Pawn associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* @parma PawnValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafePawn(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Set the Controller's Blackboard Object Key value as a Pawn associated with KeyName.
				*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma PawnValue
				*/
				static void SetPawnChecked2(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue);
	
				/**
				* Set the Controller's Blackboard Object Key value as a Pawn associated with KeySelector.
				*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeySelector
				* @parma PawnValue
				*/
				static void SetPawnChecked2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue);

				/**
				* Safely set the Controller's Blackboard Object Key value as a Pawn associated with KeyName.
				*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
				* 
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma PawnValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafePawn2(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Safely set the Controller's Blackboard Object Key value as a Pawn associated with KeySelector.
				*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
				* 
				* 
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* @parma PawnValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafePawn2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Pawn

				// Class
			#pragma region 
			public:

				/**
				* Set the Controller's Blackboard Class Key value associated with KeyName.
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma ClassValue
				*/
				static void SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, UClass* ClassValue);

				/**
				* Safely set the Controller's Blackboard Class Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma ClassValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, UClass* ClassValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Class

				// Enum
			#pragma region
			public:
			
				/**
				* Set the Controller's Blackboard Enum (uint8) Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma EnumValue
				*/
				static void SetEnumChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const uint8& EnumValue);

				/**
				* Set the Controller's Blackboard Enum Key value associated with KeySelector.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeySelector
				* @parma EnumValue
				*/
				static void SetEnumChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue);

				/**
				* Safely set the Controller's Blackboard Enum (uint8) Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma EnumValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeEnum(const FString& Context, const AAIController* Controller, const FName& KeyName, const uint8& EnumValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Safely set the Controller's Blackboard Enum Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* @parma EnumValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeEnum(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Enum

				// Int
			#pragma region
			public:

				/**
				* Set the Controller's Blackboard Int (int32) Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma IntValue
				*/
				static void SetIntChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const int32& IntValue);

				/**
				* Set the Controller's Blackboard Int (int32) Key value associated with KeySelector.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeySelector
				* @parma IntValue
				*/
				static void SetIntChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const int32& IntValue);

				/**
				* Safely set the Controller's Blackboard Int (int32) Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma IntValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeInt(const FString& Context, const AAIController* Controller, const FName& KeyName, const int32& IntValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Safely set the Controller's Blackboard Int (int32) Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* @parma IntValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeInt(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const int32& IntValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Increment the Controller's Blackboard Int (int32) Key value associated with KeySelector.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeySelector
				* @parma Amount
				*/
				static void IncrementIntChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const int32& Amount = 1);

				/**
				* Safely increment the Controller's Blackboard Int (int32) Key value associated with KeySelector.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeySelector
				* @parma Amount
				*/
				static bool SafeIncrementInt(const FString& Context, const AAIController* Controller, const FName& KeyName, const int32& Amount = 1, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Int

				// Float
			#pragma region

				/**
				* Set the Controller's Blackboard Float Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma FloatValue
				*/
				static void SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const float& FloatValue);

				/**
				* Safely set the Controller's Blackboard Float Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma FloatValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const float& FloatValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Float

				// Bool
			#pragma region
			public:

				/**
				* Set the Controller's Blackboard Bool Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma BoolValue
				*/
				static void SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const bool& BoolValue);

				/**
				* Safely set the Controller's Blackboard Bool Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma BoolValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const bool& BoolValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Bool

				// String
			#pragma region
			public:

				/**
				* Set the Controller's Blackboard String Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma StringValue
				*/
				static void SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const FString& StringValue);

				/**
				* Safely set the Controller's Blackboard String Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma StringValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const FString& StringValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion String

				// Name
			#pragma region

				/**
				* Set the Controller's Blackboard Name Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma NameValue
				*/
				static void SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const FName& NameValue);

				/**
				* Safely set the Controller's Blackboard Name Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma NameValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const FName& NameValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Name

				// Vector (Vector3d)
			#pragma region
			public:

				/**
				* Set the Controller's Blackboard Vector (Vector3d) Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma VectorValue
				*/
				static void SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const FVector3d& VectorValue);

				/**
				* Safely set the Controller's Blackboard Vector (Vector3d) Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma VectorValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const FVector3d& VectorValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Vector (Vector3d)

				// Rotator (Rotator3d)
			#pragma region
			public:

				/**
				* Set the Controller's Blackboard Rotator (Rotator3d) Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @parma RotatorValue
				*/
				static void SetValueChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const FRotator3d& RotatorValue);

				/**
				* Safely set the Controller's Blackboard Rotator (Rotator3d) Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @parma RotatorValue
				* @param Log			(optional)
				* return				Whether the value was set or not.
				*/
				static bool SetSafeValue(const FString& Context, const AAIController* Controller, const FName& KeyName, const FRotator3d& RotatorValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Rotator (Rotator3d)

			#pragma endregion Set

			// Get
			#pragma region
			public:

				// Object
			#pragma region
			public:

				/**
				* Get the Controller's Blackboard Object Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* return			Object.
				*/
				static UObject* GetObjectChecked(const FString& Context, const AAIController* Controller, const FName& KeyName);

				/**
				* Get the Controller's Blackboard Object Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* return				Object.
				*/
				static UObject* GetObjectChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector);

				/**
				* Safely get the Controller's Blackboard Object Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @param OutSuccess		(out)
				* @param Log			(optional)
				* return				Object.
				*/
				static UObject* GetSafeObject(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Safely get the Controller's Blackboard Object Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* @param OutSuccess		(out)
				* @param Log			(optional)
				* return				Object.
				*/
				static UObject* GetSafeObject(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Object

				// Pawn
			#pragma region
			public:

				/*
				* Get the Controller's Blackboard Object Key value as a Pawn associated with KeyName.
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName	
				* return			Pawn.
				*/
				static APawn* GetPawnChecked(const FString& Context, const AAIController* Controller, const FName& KeyName);

				/*
				* Get the Controller's Blackboard Object Key value as Pawn associated with KeySelector.
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName	
				* return			Pawn.
				*/
				static APawn* GetPawnChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector);

				/*
				* Safely get the Controller's Blackboard Object Key value as a Pawn associated with KeyName.
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName	
				* @param OutSuccess (out)
				* @param Log		(optional)
				* return			Pawn.
				*/
				static APawn* GetSafePawn(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/*
				* Safely get the Controller's Blackboard Object Key value as Pawn associated with KeySelector.
				* 
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* @param OutSuccess (out)
				* @param Log		(optional)
				* return			Pawn.
				*/
				static APawn* GetSafePawn(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Pawn

				// Enum
			#pragma region
			public:

				/**
				* Get the Controller's Blackboard Enum Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* return			Enum (as Byte).
				*/
				static uint8 GetEnumChecked(const FString& Context, const AAIController* Controller, const FName& KeyName);

				/**
				* Get the Controller's Blackboard Enum Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* return				Enum (as Byte).
				*/
				static uint8 GetEnumChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector);

				/**
				* Safely get the Controller's Blackboard Enum Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @param OutSuccess		(out)
				* @param Log			(optional)
				* return				Enum (as Byte).
				*/
				static uint8 GetSafeEnum(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Safely get the Controller's Blackboard Enum Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* @param OutSuccess		(out)
				* @param Log			(optional)
				* return				Enum (as Byte).
				*/
				static uint8 GetSafeEnum(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Enum

				// Int
			#pragma region
			public:

				/**
				* Get the Controller's Blackboard Int (int32) Key value associated with KeyName.
				*
				* @param Context	The calling context.
				* @param Controller
				* @param KeyName
				* return			Int (int32).
				*/
				static int32 GetIntChecked(const FString& Context, const AAIController* Controller, const FName& KeyName);

				/**
				* Get the Controller's Blackboard Int (int32) Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* return				Int (int32).
				*/
				static int32 GetIntChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector);

				/**
				* Safely get the Controller's Blackboard Int (int32) Key value associated with KeyName.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeyName
				* @param OutSuccess		(out)
				* @param Log			(optional)
				* return				Int (int32).
				*/
				static int32 GetSafeInt(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

				/**
				* Safely get the Controller's Blackboard Int (int32) Key value associated with KeySelector.
				*
				* @param Context		The calling context.
				* @param Controller
				* @param KeySelector
				* @param OutSuccess		(out)
				* @param Log			(optional)
				* return				Int (int32).
				*/
				static int32 GetSafeInt(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

			#pragma endregion Int

			#pragma endregion Get
			};
		}
	}
}

using CsAIBlackboardLibrary = NCsAI::NController::NBlackboard::FLibrary;