// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
//Types
#include "BehaviorTree/BehaviorTreeTypes.h"
// Log
#include "Utility/CsAILog.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UBlackboardData;
class UBlackboardKeyType;
class APawn;

namespace NCsBlackboard
{
	/**
	* Library of functions related to a Blackboard and Blackboard Component
	*/
	struct CSAI_API FLibrary final
	{
	public:

		/**
		* Get the Blackboard Data associated with Component
		* 
		* @param Context	The calling context.
		* @param Component
		* return			Data
		*/
		static const UBlackboardData* GetDataChecked(const FString& Context, const UBlackboardComponent* Component);

		/**
		* Safely get the Blackboard Data associated with Component
		*
		* @param Context	The calling context.
		* @param Component
		* @param Log		(optional)
		* return			Data
		*/
		static const UBlackboardData* GetSafeData(const FString& Context, const UBlackboardComponent* Component, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Get the Blackboard Component associated with Component
		* 
		* @param Context	The calling context.
		* @param Component
		* return			Component
		*/
		static const UBlackboardComponent* GetComponentChecked(const FString& Context, const UBehaviorTreeComponent* Component);
		static UBlackboardComponent* GetComponentChecked(const FString& Context, UBehaviorTreeComponent* Component);

		/**
		* Safely get the Blackboard Component associated with Component
		*
		* @param Context	The calling context.
		* @param Component
		* @param Log		(optional)
		* return			Component
		*/
		static const UBlackboardComponent* GetSafeComponent(const FString& Context, const UBehaviorTreeComponent* Component, void(*Log)(const FString&) = &NCsAI::FLog::Warning);
		static UBlackboardComponent* GetSafeComponent(const FString& Context, UBehaviorTreeComponent* Component, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

	// Key
	#pragma region
	public:

		static bool IsValidChecked(const FString& Context, const FBlackboardKeySelector& KeySelector);

		static bool IsValid(const FString& Context, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		static bool AreEqualChecked(const FString& Context, const TSubclassOf<UBlackboardKeyType>& A, const TSubclassOf<UBlackboardKeyType>& B);

		static bool SafeAreEqual(const FString& Context, const TSubclassOf<UBlackboardKeyType>& A, const TSubclassOf<UBlackboardKeyType>& B, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Get whether the Data has the Key with name KeyName or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName or not.
		*/
		static bool HasKeyChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component has the Key with name KeyName or not.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* return			Whether the Component has the Key with name KeyName or not.
		*/
		FORCEINLINE static bool HasKeyChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return HasKeyChecked(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Get whether the Data has Key associated with KeySelector.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeySelector
		* return			Whether the Data has Key associated with KeySelector or not.
		*/
		FORCEINLINE static bool HasKeyChecked(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector)
		{
			check(IsValidChecked(Context, KeySelector));
			return AreEqualChecked(Context, KeySelector.SelectedKeyType, GetKeyTypeChecked(Context, Data, KeySelector.SelectedKeyName));
		}

		/**
		* Get whether the Component has Key associated with KeySelector.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* return			Whether the Component has Key associated with KeySelector or not.
		*/
		FORCEINLINE static bool HasKeyChecked(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector)
		{
			return HasKeyChecked(Context, GetDataChecked(Context, Component), KeySelector);
		}

		/**
		* Safely Get whether the Data has the Key with name KeyName or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* @param Log		(optional)
		* return			Whether the Data has the Key with name KeyName or not.
		*/
		static bool SafeHasKey(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely Get whether the Component has the Key with name KeyName or not.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* @param Log		(optional)
		* return			Whether the Component has the Key wiht name KeyName or not.
		*/
		FORCEINLINE static bool SafeHasKey(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeHasKey(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		/**
		* Safely Get whether the Data has the Key associated with KeySelector or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* @param Log		(optional)
		* return			Whether the Data has the Key associated with KeySelector or not.
		*/
		FORCEINLINE static bool SafeHasKey(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			if (!IsValid(Context, KeySelector, Log))
				return false;
			return SafeAreEqual(Context, KeySelector.SelectedKeyType, GetSafeKeyType(Context, Data, KeySelector.SelectedKeyName, Log), Log);
		}

		/**
		* Safely Get whether the Component has the Key associated with KeySelector or not.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* @param Log		(optional)
		* return			Whether the Component has the Key associated with KeySelector or not.
		*/
		FORCEINLINE static bool SafeHasKey(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeHasKey(Context, GetSafeData(Context, Component, Log), KeySelector, Log);
		}

		/**
		* Get ID associated with the Key with KeyName.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Get ID associated with the Key with KeyName.
		*/
		static uint8 GetKeyIDChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Safely get ID associated with the Key with KeyName.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* @param Log		(optional)
		* return			Get ID associated with the Key with KeyName.
		*/
		static uint8 GetSafeKeyID(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		static const FString& KeyTypeToString(const TSubclassOf<UBlackboardKeyType>& KeyType);

		static TSubclassOf<UBlackboardKeyType> GetKeyTypeChecked(const FString& Context, const UBlackboardData* Data, const uint8& KeyID);

		FORCEINLINE static TSubclassOf<UBlackboardKeyType> GetKeyTypeChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
		{
			return GetKeyTypeChecked(Context, Data, GetKeyIDChecked(Context, Data, KeyName));
		}

		static TSubclassOf<UBlackboardKeyType> GetSafeKeyType(const FString& Context, const UBlackboardData* Data, const uint8& KeyID, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		FORCEINLINE static TSubclassOf<UBlackboardKeyType> GetSafeKeyType(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return GetSafeKeyType(Context, Data, GetSafeKeyID(Context, Data, KeyName));
		}

		static TSubclassOf<UBlackboardKeyType> GetSafeKeyType(const FString& Context, UClass* KeyType, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		// Object
		#pragma region
		public:

		/**
		* Safely check whether KeyType is of type Object.
		* 
		* @param Context	The calling context
		* @param KeyType
		* @param Log		(optional)
		* return			Whether KeyType is of type Object or not.
		*/
		static bool SafeIsKeyType_Object(const FString& Context, const TSubclassOf<UBlackboardKeyType>& KeyType, void(*Log)(const FString&) = &NCsAI::FLog::Warning);
		
		/**
		* Safely check whether KeyType is of type Object.
		*
		* @param Context	The calling context
		* @param KeyType
		* @param Log		(optional)
		* return			Whether KeyType is of type Object or not.
		*/
		FORCEINLINE static bool SafeIsKeyType_Object(const FString& Context, UClass* KeyType, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKeyType_Object(Context, GetSafeKeyType(Context, KeyType, Log), Log);
		}

		/**
		* Get whether the Data with Key with KeyName is of type Object or not.
		* 
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Object or not.
		*/
	#if !UE_BUILD_SHIPPING
		static bool IsKeyChecked_Object(const FString& Context, const UBlackboardData* Data, const FName& KeyName);
	#else
		FORCEINLINE static bool IsKeyChecked_Object(const FString& Context, const UBlackboardData* Data, const FName& KeyName) { return true; }
	#endif // #if !UE_BUILD_SHIPPING

		/**
		* Get whether the Component with Key with KeyName is of type Object or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Component has the Key with name KeyName is of type Object or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Object(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKeyChecked_Object(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Get whether the Data with Key associated with KeySelector is of type Object or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeySelector
		* return			Whether the Data has the Key associated with KeySelector is of type Object or not.
		*/
	#if !UE_BUILD_SHIPPING
		static bool IsKeyChecked_Object(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector);
	#else
		FORCEINLINE static bool IsKeyChecked_Object(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector) { return true; }
	#endif // #if !UE_BUILD_SHIPPING

		/**
		* Get whether the Data with Key associated with KeySelector is of type Object or not.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeySelector
		* return			Whether the Component has the Key associated with KeySelector is of type Object or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Object(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector)
		{
			return IsKeyChecked_Object(Context, GetDataChecked(Context, Component), KeySelector);
		}

		/**
		* Get whether the KeySelector is Valid and of type Object or not.
		*
		* @param Context	The calling context.
		* @param KeySelector
		* return			Whether the KeySelector is Valid and of type Object or not.
		*/
	#if !UE_BUILD_SHIPPING
		static bool IsKeyChecked_Object(const FString& Context, const FBlackboardKeySelector& KeySelector);
	#else
		FORCEINLINE static bool IsKeyChecked_Object(const FString& Context, const FBlackboardKeySelector& KeySelector) { return true; }
	#endif // #if !UE_BUILD_SHIPPING

		/**
		* Safely get whether the Data with Key with KeyName is of type Object or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* @param Log		(optional)
		* return			Whether the Data has the Key with name KeyName is of type Object or not.
		*/
		static bool SafeIsKey_Object(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type Object or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* @param Log		(optional)
		* return			Whether the Data has the Key with name KeyName is of type Object or not.
		*/
		FORCEINLINE static bool SafeIsKey_Object(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Object(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		/**
		* Safely get whether the Data with Key associated with KeySelector is of type Object or not.
		*
		* @param Context		The calling context.
		* @param Data
		* @param KeySelector
		* @param Log			(optional)
		* return				Whether the Data has the Key associated with KeySelector is of type Object or not.
		*/
		static bool SafeIsKey_Object(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key associated with KeySelector is of type Object or not.
		*
		* @param Context		The calling context.
		* @param Data
		* @param KeySelector
		* @param Log			(optional)
		* return				Whether the Data has the Key associated with KeySelector is of type Object or not.
		*/
		FORCEINLINE static bool SafeIsKey_Object(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Object(Context, GetSafeData(Context, Component, Log), KeySelector, Log);
		}

		/**
		* Safely get whether the KeySelector is Valid and of type Object or not.
		*
		* @param Context		The calling context.
		* @param KeySelector
		* @param Log			(optional)
		* return				Whether the KeySelector is Valid and of type Object or not.
		*/
		static bool SafeIsKey_Object(const FString& Context, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		#pragma endregion Object
		
		// Class
		#pragma region

		/**
		* Get whether the Data with Key with KeyName is of type Class or not.
		* 
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Class or not.
		*/
		static bool IsKeyChecked_Class(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Class or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Class or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Class(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKeyChecked_Class(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Safely get whether the Data with Key with KeyName is of type Class or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Class or not.
		*/
		static bool SafeIsKey_Class(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type Class or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Class or not.
		*/
		FORCEINLINE static bool SafeIsKey_Class(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Class(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		#pragma endregion Class
		
		// Enum
		#pragma region

		/**
		* Safely check whether KeyType is of type Enum or not.
		*
		* @param Context	The calling context
		* @param KeyType
		* return			Whether KeyType is of type Enum or not.
		*/
		static bool SafeIsKeyType_Enum(const FString& Context, const TSubclassOf<UBlackboardKeyType>& KeyType, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Get whether the Data with Key with KeyName is of type Enum or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Enum or not.
		*/
		static bool IsKeyChecked_Enum(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Enum or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Enum or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Enum(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKeyChecked_Enum(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Get whether the Data with Key associated with KeySelector is of type Enum or not.
		*
		* @param Context		The calling context.
		* @param Data
		* @param KeySelector
		* return				Whether the Data has the Key associated with KeySelector is of type Enum or not.
		*/
		static bool IsKeyChecked_Enum(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector);

		/**
		* Get whether the Data with Key associated with KeySelector is of type Enum or not.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* return				Whether the Component has the Key associated with KeySelector is of type Enum or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Enum(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector)
		{
			return IsKeyChecked_Enum(Context, GetDataChecked(Context, Component), KeySelector);
		}

		/**
		* Safely get whether the Data with Key with KeyName is of type Enum or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Enum or not.
		*/
		static bool SafeIsKey_Enum(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type Enum or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Enum or not.
		*/
		FORCEINLINE static bool SafeIsKey_Enum(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Enum(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		/**
		* Safely get whether the Data with Key associated with KeySelector is of type Enum or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeySelector
		* return			Whether the Data has the Key associated with KeySelector is of type Enum or not.
		*/
		static bool SafeIsKey_Enum(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key associated with KeySelector is of type Enum or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeySelector
		* return			Whether the Data has the Key associated with KeySelector is of type Enum or not.
		*/
		FORCEINLINE static bool SafeIsKey_Enum(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Enum(Context, GetSafeData(Context, Component, Log), KeySelector, Log);
		}

		#pragma endregion Enum

		// Int
		#pragma region

		/**
		* Get whether the Data with Key with KeyName is of type Int or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Int or not.
		*/
		static bool IsKeyChecked_Int(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Int or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Int or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Int(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKeyChecked_Int(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Safely get whether the Data with Key with KeyName is of type Int or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Int or not.
		*/
		static bool SafeIsKey_Int(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type Int or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Int or not.
		*/
		FORCEINLINE static bool SafeIsKey_Int(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Int(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		#pragma endregion Int

		// Float
		#pragma region

		/**
		* Safely check whether KeyType is of type Float or not.
		*
		* @param Context	The calling context
		* @param KeyType
		* return			Whether KeyType is of type Float or not.
		*/
		static bool SafeIsKeyType_Float(const FString& Context, const TSubclassOf<UBlackboardKeyType>& KeyType, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Get whether the Data with Key with KeyName is of type Float or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Float or not.
		*/
		static bool IsKeyChecked_Float(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Float or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Float or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Float(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKeyChecked_Float(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Get whether the Data with Key associated with KeySelector is of type Float or not.
		*
		* @param Context		The calling context.
		* @param Data
		* @param KeySelector
		* return				Whether the Data has the Key associated with KeySelector is of Float Enum or not.
		*/
		static bool IsKeyChecked_Float(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector);

		/**
		* Get whether the Data with Key associated with KeySelector is of type Float or not.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* return				Whether the Component has the Key associated with KeySelector is of type Float or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Float(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector)
		{
			return IsKeyChecked_Float(Context, GetDataChecked(Context, Component), KeySelector);
		}

		/**
		* Safely get whether the Data with Key with KeyName is of type Float or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Float or not.
		*/
		static bool SafeIsKey_Float(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type Float or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Float or not.
		*/
		FORCEINLINE static bool SafeIsKey_Float(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Float(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		/**
		* Safely get whether the Data with Key associated with KeySelector is of type Float or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeySelector
		* return			Whether the Data has the Key associated with KeySelector is of type Float or not.
		*/
		static bool SafeIsKey_Float(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key associated with KeySelector is of type Float or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeySelector
		* return			Whether the Data has the Key associated with KeySelector is of type Float or not.
		*/
		FORCEINLINE static bool SafeIsKey_Float(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Float(Context, GetSafeData(Context, Component, Log), KeySelector, Log);
		}

		#pragma endregion Float

		// Bool
		#pragma region

		/**
		* Get whether the Data with Key with KeyName is of type Bool or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Bool or not.
		*/
		static bool IsKeyChecked_Bool(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Bool or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Bool or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Bool(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKeyChecked_Bool(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Safely get whether the Data with Key with KeyName is of type Bool or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Bool or not.
		*/
		static bool SafeIsKey_Bool(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type Bool or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Bool or not.
		*/
		FORCEINLINE static bool SafeIsKey_Bool(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Bool(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		#pragma endregion Bool

		// String
		#pragma region

		/**
		* Get whether the Data with Key with KeyName is of type String or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type String or not.
		*/
		static bool IsKeyChecked_String(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type String or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type String or not.
		*/
		FORCEINLINE static bool IsKeyChecked_String(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKeyChecked_String(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Safely get whether the Data with Key with KeyName is of type String or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type String or not.
		*/
		static bool SafeIsKey_String(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type String or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type String or not.
		*/
		FORCEINLINE static bool SafeIsKey_String(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_String(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		#pragma endregion String

		// Name
		#pragma region

		/**
		* Get whether the Data with Key with KeyName is of type Name or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Name or not.
		*/
		static bool IsKeyChecked_Name(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Name or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Name or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Name(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKeyChecked_Name(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Safely get whether the Data with Key with KeyName is of type Name or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Name or not.
		*/
		static bool SafeIsKey_Name(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type Name or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Name or not.
		*/
		FORCEINLINE static bool SafeIsKey_Name(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Name(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		#pragma endregion Name

		// Vector
		#pragma region

		/**
		* Safely check whether KeyType is of type Vector.
		*
		* @param Context	The calling context
		* @param KeyType
		* return			Whether KeyType is of type Vector or not.
		*/
		static bool SafeIsKeyType_Vector(const FString& Context, const TSubclassOf<UBlackboardKeyType>& KeyType, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely check whether KeyType is of type Vector.
		*
		* @param Context	The calling context
		* @param KeyType
		* return			Whether KeyType is of type Vector or not.
		*/
		FORCEINLINE static bool SafeIsKeyType_Vector(const FString& Context, UClass* KeyType, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKeyType_Vector(Context, GetSafeKeyType(Context, KeyType, Log), Log);
		}

		/**
		* Get whether the Data with Key with KeyName is of type Vector or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Vector or not.
		*/
		static bool IsKeyChecked_Vector(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Vector or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Vector or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Vector(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKeyChecked_Vector(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Safely get whether the Data with Key with KeyName is of type Vector or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Vector or not.
		*/
		static bool SafeIsKey_Vector(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type Vector or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Vector or not.
		*/
		FORCEINLINE static bool SafeIsKey_Vector(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Vector(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		#pragma endregion Vector

		// Rotator
		#pragma region

		/**
		* Get whether the Data with Key with KeyName is of type Rotator or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Rotator or not.
		*/
		static bool IsKeyChecked_Rotator(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Rotator or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Rotator or not.
		*/
		FORCEINLINE static bool IsKeyChecked_Rotator(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKeyChecked_Rotator(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Safely get whether the Data with Key with KeyName is of type Rotator or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Rotator or not.
		*/
		static bool SafeIsKey_Rotator(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type Rotator or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Rotator or not.
		*/
		FORCEINLINE static bool SafeIsKey_Rotator(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Rotator(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

		#pragma endregion Rotator

	#pragma endregion Key

	// Set
	#pragma region

		// Object
	#pragma region
	public:

		/**
		* Set the Component's Blackboard Object Key value associated with KeyName.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* @parma ObjectValue
		*/
		static void SetObjectChecked(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, UObject* ObjectValue);
	
		/**
		* Set the Component's Blackboard Object Key value associated with KeySelector.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeySelector
		* @parma ObjectValue
		*/
		static void SetObjectChecked(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue);

		/**
		* Safely set the Component's Blackboard Object Key value associated with KeyName.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeyName
		* @param ObjectValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafeObject(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely set the Component's Blackboard Object Key value associated with KeySelector.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* @param ObjectValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafeObject(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Set the Component's Blackboard Object Key value associated with KeyName.
		*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* @parma ObjectValue
		*/
		static void SetObjectChecked2(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, UObject* ObjectValue);
	
		/**
		* Set the Component's Blackboard Object Key value associated with KeySelector.
		*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeySelector
		* @parma ObjectValue
		*/
		static void SetObjectChecked2(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue);

		/**
		* Safely set the Component's Blackboard Object Key value associated with KeyName.
		*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeyName
		* @param ObjectValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafeObject2(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely set the Component's Blackboard Object Key value associated with KeySelector.
		*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* @param ObjectValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafeObject2(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

	#pragma endregion Object

		// Pawn
	#pragma region
	public:

		/**
		* Set the Component's Blackboard Object Key value as a Pawn associated with KeyName.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* @parma PawnValue
		*/
		static void SetPawnChecked(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, APawn* PawnValue);
	
		/**
		* Set the Component's Blackboard Object Key value as a Pawn associated with KeySelector.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeySelector
		* @parma PawnValue
		*/
		static void SetPawnChecked(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, APawn* PawnValue);

		/**
		* Safely set the Component's Blackboard Object Key value as a Pawn associated with KeyName.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeyName
		* @parma PawnValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafePawn(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, APawn* PawnValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely set the Component's Blackboard Object Key value as a Pawn associated with KeySelector.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* @parma PawnValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafePawn(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, APawn* PawnValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Set the Component's Blackboard Object Key value as a Pawn associated with KeyName.
		*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* @parma PawnValue
		*/
		static void SetPawnChecked2(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, APawn* PawnValue);
	
		/**
		* Set the Component's Blackboard Object Key value as a Pawn associated with KeySelector.
		*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeySelector
		* @parma PawnValue
		*/
		static void SetPawnChecked2(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, APawn* PawnValue);

		/**
		* Safely set the Component's Blackboard Object Key value as a Pawn associated with KeyName.
		*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
		* 
		* @param Context		The calling context.
		* @param Component
		* @param KeyName
		* @parma PawnValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafePawn2(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, APawn* PawnValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely set the Component's Blackboard Object Key value as a Pawn associated with KeySelector.
		*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
		* 
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* @parma PawnValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafePawn2(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, APawn* PawnValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

	#pragma endregion Pawn

		// Enum
	#pragma region
	public:
			
		/**
		* Set the Component's Blackboard Enum (uint8) Key value associated with KeyName.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* @parma EnumValue
		*/
		static void SetEnumChecked(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const uint8& EnumValue);

		/**
		* Set the Component's Blackboard Enum Key value associated with KeySelector.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeySelector
		* @parma EnumValue
		*/
		static void SetEnumChecked(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue);

		/**
		* Safely set the Component's Blackboard Enum (uint8) Key value associated with KeyName.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeyName
		* @parma EnumValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafeEnum(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const uint8& EnumValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely set the Component's Blackboard Enum Key value associated with KeySelector.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* @parma EnumValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafeEnum(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

	#pragma endregion Enum

		// Float
	#pragma region
	public:
			
		/**
		* Set the Component's Blackboard Float Key value associated with KeyName.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* @parma FloatValue
		*/
		static void SetFloatChecked(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const float& FloatValue);

		/**
		* Set the Component's Blackboard Float Key value associated with KeySelector.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeySelector
		* @parma FloatValue
		*/
		static void SetFloatChecked(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, const float& FloatValue);

		FORCEINLINE static void SetFloatChecked(const FString& Context, UBehaviorTreeComponent* Component, const FBlackboardKeySelector& KeySelector, const float& FloatValue)
		{
			SetFloatChecked(Context, GetComponentChecked(Context, Component), KeySelector, FloatValue);
		}

		/**
		* Safely set the Component's Blackboard Float Key value associated with KeyName.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeyName
		* @parma FloatValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafeFloat(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const float& FloatValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely set the Component's Blackboard Float Key value associated with KeySelector.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* @parma FloatValue
		* @param Log			(optional)
		* return				Whether the value was set or not.
		*/
		static bool SetSafeFloat(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, const float& FloatValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		FORCEINLINE static bool SetSafeFloat(const FString& Context, UBehaviorTreeComponent* Component, const FBlackboardKeySelector& KeySelector, const float& FloatValue, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SetSafeFloat(Context, GetSafeComponent(Context, Component, Log), KeySelector, FloatValue, Log);
		}

	#pragma endregion Enum

	#pragma endregion Set

	// Get
	#pragma region

		// Object
	#pragma region
	public:

		/*
		* Get the Component's Blackboard Object Key value associated with KeyName.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName	
		* return			Pawn.
		*/
		static UObject* GetObjectChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName);

		/*
		* Get the Component's Blackboard Object Key value associated with KeySelector.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName	
		* return			Pawn.
		*/
		static UObject* GetObjectChecked(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector);

		/*
		* Safely get the Component's Blackboard Object Key value associated with KeyName.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName	
		* @param OutSuccess (out)
		* @param Log		(optional)
		* return			Pawn.
		*/
		static UObject* GetSafeObject(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/*
		* Safely get the Component's Blackboard Object Key value associated with KeySelector.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* @param OutSuccess (out)
		* @param Log		(optional)
		* return			Pawn.
		*/
		static UObject* GetSafeObject(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

	#pragma endregion Object

		// Pawn
	#pragma region
	public:

		/*
		* Get the Component's Blackboard Object Key value as a Pawn associated with KeyName.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName	
		* return			Pawn.
		*/
		static APawn* GetPawnChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName);

		/*
		* Get the Component's Blackboard Object Key value as Pawn associated with KeySelector.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName	
		* return			Pawn.
		*/
		static APawn* GetPawnChecked(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector);

		/*
		* Safely get the Component's Blackboard Object Key value as a Pawn associated with KeyName.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName	
		* @param OutSuccess (out)
		* @param Log		(optional)
		* return			Pawn.
		*/
		static APawn* GetSafePawn(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/*
		* Safely get the Component's Blackboard Object Key value as Pawn associated with KeySelector.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* @param OutSuccess (out)
		* @param Log		(optional)
		* return			Pawn.
		*/
		static APawn* GetSafePawn(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

	#pragma endregion Pawn

		// Enum
	#pragma region
	public:

		/**
		* Get the Component's Blackboard Enum Key value associated with KeyName.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* return			Enum (as Byte).
		*/
		static uint8 GetEnumChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName);

		/**
		* Get the Component's Blackboard Enum Key value associated with KeySelector.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* return				Enum (as Byte).
		*/
		static uint8 GetEnumChecked(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector);

		/**
		* Safely get the Component's Blackboard Enum Key value associated with KeyName.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeyName
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				Enum (as Byte).
		*/
		static uint8 GetSafeEnum(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get the Component's Blackboard Enum Key value associated with KeySelector.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				Enum (as Byte).
		*/
		static uint8 GetSafeEnum(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

	#pragma endregion Enum

		// Float
	#pragma region
	public:

		/**
		* Get the Component's Blackboard Float Key value associated with KeyName.
		*
		* @param Context	The calling context.
		* @param Component
		* @param KeyName
		* return			Float.
		*/
		static float GetFloatChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName);

		/**
		* Get the Component's Blackboard Float Key value associated with KeySelector.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* return				Float.
		*/
		static float GetFloatChecked(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector);

		FORCEINLINE static float GetFloatChecked(const FString& Context, const UBehaviorTreeComponent* Component, const FBlackboardKeySelector& KeySelector)
		{
			return GetFloatChecked(Context, GetComponentChecked(Context, Component), KeySelector);
		}

		/**
		* Safely get the Component's Blackboard Float Key value associated with KeyName.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeyName
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				Float.
		*/
		static float GetSafeFloat(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get the Component's Blackboard Float Key value associated with KeySelector.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				Float.
		*/
		static float GetSafeFloat(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get the Component's Blackboard Float Key value associated with KeyName.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeyName
		* @param Log			(optional)
		* return				Float.
		*/
		static float GetSafeFloat(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get the Component's Blackboard Float Key value associated with KeySelector.
		*
		* @param Context		The calling context.
		* @param Component
		* @param KeySelector
		* @param Log			(optional)
		* return				Float.
		*/
		static float GetSafeFloat(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		FORCEINLINE static float GetSafeFloat(const FString& Context, const UBehaviorTreeComponent* Component, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return GetSafeFloat(Context, GetSafeComponent(Context, Component, Log), KeySelector, Log);
		}

	#pragma endregion Float

	#pragma endregion Get
	};
}