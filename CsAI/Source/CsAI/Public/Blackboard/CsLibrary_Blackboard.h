// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsAILog.h"

class UBlackboardComponent;
class UBlackboardData;
class UBlackboardKeyType;

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

	// Key
	#pragma region
	public:

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

		// Object
		#pragma region
		public:

		/**
		* Get whether the Data with Key with KeyName is of type Object or not.
		* 
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Object or not.
		*/
		static bool IsKey_ObjectChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Object or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Object or not.
		*/
		FORCEINLINE static bool IsKey_ObjectChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKey_ObjectChecked(Context, GetDataChecked(Context, Component), KeyName);
		}

		/**
		* Safely get whether the Data with Key with KeyName is of type Object or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Object or not.
		*/
		static bool SafeIsKey_Object(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely get whether the Data with Key with KeyName is of type Object or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Object or not.
		*/
		FORCEINLINE static bool SafeIsKey_Object(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) = &NCsAI::FLog::Warning)
		{
			return SafeIsKey_Object(Context, GetSafeData(Context, Component, Log), KeyName, Log);
		}

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
		static bool IsKey_ClassChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Class or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Class or not.
		*/
		FORCEINLINE static bool IsKey_ClassChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKey_ClassChecked(Context, GetDataChecked(Context, Component), KeyName);
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
		* Get whether the Data with Key with KeyName is of type Enum or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Enum or not.
		*/
		static bool IsKey_EnumChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Enum or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Enum or not.
		*/
		FORCEINLINE static bool IsKey_EnumChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKey_EnumChecked(Context, GetDataChecked(Context, Component), KeyName);
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
		static bool IsKey_IntChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Int or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Int or not.
		*/
		FORCEINLINE static bool IsKey_IntChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKey_IntChecked(Context, GetDataChecked(Context, Component), KeyName);
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
		* Get whether the Data with Key with KeyName is of type Float or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Float or not.
		*/
		static bool IsKey_FloatChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Float or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Float or not.
		*/
		FORCEINLINE static bool IsKey_FloatChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKey_FloatChecked(Context, GetDataChecked(Context, Component), KeyName);
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
		static bool IsKey_BoolChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Bool or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Bool or not.
		*/
		FORCEINLINE static bool IsKey_BoolChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKey_BoolChecked(Context, GetDataChecked(Context, Component), KeyName);
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
		static bool IsKey_StringChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type String or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type String or not.
		*/
		FORCEINLINE static bool IsKey_StringChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKey_StringChecked(Context, GetDataChecked(Context, Component), KeyName);
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
		static bool IsKey_NameChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Name or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Name or not.
		*/
		FORCEINLINE static bool IsKey_NameChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKey_NameChecked(Context, GetDataChecked(Context, Component), KeyName);
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
		* Get whether the Data with Key with KeyName is of type Vector or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Vector or not.
		*/
		static bool IsKey_VectorChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Vector or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Vector or not.
		*/
		FORCEINLINE static bool IsKey_VectorChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKey_VectorChecked(Context, GetDataChecked(Context, Component), KeyName);
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
		static bool IsKey_RotatorChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName);

		/**
		* Get whether the Component with Key with KeyName is of type Rotator or not.
		*
		* @param Context	The calling context.
		* @param Data
		* @param KeyName
		* return			Whether the Data has the Key with name KeyName is of type Rotator or not.
		*/
		FORCEINLINE static bool IsKey_RotatorChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
		{
			return IsKey_RotatorChecked(Context, GetDataChecked(Context, Component), KeyName);
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
	};
}