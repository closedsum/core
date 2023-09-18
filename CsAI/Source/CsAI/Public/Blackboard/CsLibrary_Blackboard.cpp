// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Blackboard/CsLibrary_Blackboard.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// AI
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"

namespace NCsBlackboard
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				const FString Object = TEXT("Object");
				const FString Class = TEXT("Class");
				const FString Enum = TEXT("Enum");
				const FString Int = TEXT("Int");
				const FString Float = TEXT("Float");
				const FString Bool = TEXT("Bool");
				const FString String = TEXT("String");
				const FString Name = TEXT("Name");
				const FString Vector = TEXT("Vector");
				const FString Rotator = TEXT("Rotator");
			}
		}
	}

	const UBlackboardData* FLibrary::GetDataChecked(const FString& Context, const UBlackboardComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		const UBlackboardData* Data = Component->GetBlackboardAsset();

		CS_IS_PENDING_KILL_CHECKED(Data)
		return Data;
	}

	const UBlackboardData* FLibrary::GetSafeData(const FString& Context, const UBlackboardComponent* Component, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL_RET_NULL(Component)

		const UBlackboardData* Data = Component->GetBlackboardAsset();

		CS_IS_PENDING_KILL_RET_NULL(Data)
		return Data;
	}

	// Key
	#pragma region

	bool FLibrary::HasKeyChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		CS_IS_PENDING_KILL_CHECKED(Data)
		CS_IS_NAME_NONE_CHECKED(KeyName)

		checkf(Data->GetKeyID(KeyName) != FBlackboard::InvalidKey, TEXT("%s: %s does NOT have Key: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()));
		return true;
	}

	bool FLibrary::SafeHasKey(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL(Data)
		CS_IS_NAME_NONE(KeyName)

		if (Data->GetKeyID(KeyName) == FBlackboard::InvalidKey)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT have Key: %s."), *Context, *(Data->GetName()), *(KeyName.ToString())));
			return false;
		}
		return true;
	}

	uint8 FLibrary::GetKeyIDChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		CS_IS_PENDING_KILL_CHECKED(Data)
		CS_IS_NAME_NONE_CHECKED(KeyName)

		FBlackboard::FKey ID = Data->GetKeyID(KeyName);

		checkf(ID != FBlackboard::InvalidKey, TEXT("%s: %s does NOT have Key: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()));
		return ID;
	}

	uint8 FLibrary::GetSafeKeyID(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL_RET_VALUE(Data, FBlackboard::InvalidKey)
		CS_IS_NAME_NONE_RET_VALUE(KeyName, FBlackboard::InvalidKey)

		FBlackboard::FKey ID = Data->GetKeyID(KeyName);

		if (Data->GetKeyID(KeyName) == FBlackboard::InvalidKey)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT have Key: %s."), *Context, *(Data->GetName()), *(KeyName.ToString())));
			return FBlackboard::InvalidKey;
		}
		return ID;
	}

	const FString& FLibrary::KeyTypeToString(const TSubclassOf<UBlackboardKeyType>& KeyType)
	{
		using namespace NCsBlackboard::NLibrary::NCached;

		if (KeyType == UBlackboardKeyType_Object::StaticClass())
			return Str::Object;
		if (KeyType == UBlackboardKeyType_Class::StaticClass())
			return Str::Class;
		if (KeyType == UBlackboardKeyType_Enum::StaticClass())
			return Str::Enum;
		if (KeyType == UBlackboardKeyType_Int::StaticClass())
			return Str::Int;
		if (KeyType == UBlackboardKeyType_Float::StaticClass())
			return Str::Float;
		if (KeyType == UBlackboardKeyType_Bool::StaticClass())
			return Str::Bool;
		if (KeyType == UBlackboardKeyType_String::StaticClass())
			return Str::String;
		if (KeyType == UBlackboardKeyType_Name::StaticClass())
			return Str::Name;
		if (KeyType == UBlackboardKeyType_Vector::StaticClass())
			return Str::Vector;
		if (KeyType == UBlackboardKeyType_Rotator::StaticClass())
			return Str::Rotator;
		return Str::Object;
	}

	TSubclassOf<UBlackboardKeyType> FLibrary::GetKeyTypeChecked(const FString& Context, const UBlackboardData* Data, const uint8& KeyID)
	{
		CS_IS_PENDING_KILL_CHECKED(Data)
	
		checkf(KeyID != FBlackboard::InvalidKey, TEXT("%s: KeyID is NOT Valid."), *Context);

		TSubclassOf<UBlackboardKeyType> KeyType = Data->GetKeyType(KeyID);
		
		checkf(KeyType.Get(), TEXT("%s: %s with Key with KeyID: %d does NOT have a valid type."), *Context, *(Data->GetName()), KeyID);
		return KeyType;
	}

	TSubclassOf<UBlackboardKeyType> FLibrary::GetSafeKeyType(const FString& Context, const UBlackboardData* Data, const uint8& KeyID, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL_RET_NULL(Data)

		if (KeyID == FBlackboard::InvalidKey)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyID is NOT Valid."), *Context));
			return TSubclassOf<UBlackboardKeyType>();
		}

		TSubclassOf<UBlackboardKeyType> KeyType = Data->GetKeyType(KeyID);

		if (!KeyType.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key with KeyID: %d does NOT have a valid type."), *Context, *(Data->GetName()), KeyID));
			return TSubclassOf<UBlackboardKeyType>();
		}
		return KeyType;
	}

	TSubclassOf<UBlackboardKeyType> FLibrary::GetSafeKeyType(const FString& Context, UClass* KeyType, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!KeyType)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType is NULL."), *Context));
			return false;
		}
		return TSubclassOf<UBlackboardKeyType>(KeyType);
	}

		// Object
	#pragma region

	bool FLibrary::SafeIsKeyType_Object(const FString& Context, const TSubclassOf<UBlackboardKeyType>& KeyType, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!KeyType.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType is NULL."), *Context));
			return false;
		}

		if (KeyType != UBlackboardKeyType_Object::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType NOT of type: Object but of type: %s."), *Context, *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	bool FLibrary::IsKey_ObjectChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);
		
		checkf(KeyType == UBlackboardKeyType_Object::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Object but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::SafeIsKey_Object(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType != UBlackboardKeyType_Object::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Object but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Object

		// Class
	#pragma region

	bool FLibrary::IsKey_ClassChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Class::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Class but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::SafeIsKey_Class(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType != UBlackboardKeyType_Class::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Class but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Class

		// Enum
	#pragma region

	bool FLibrary::IsKey_EnumChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Enum::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Enum but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::SafeIsKey_Enum(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType != UBlackboardKeyType_Enum::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Enum but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Enum

		// Int
	#pragma region

	bool FLibrary::IsKey_IntChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Int::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Int but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::SafeIsKey_Int(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType != UBlackboardKeyType_Int::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Int but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Int

		// Float
	#pragma region

	bool FLibrary::IsKey_FloatChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Float::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Float but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::SafeIsKey_Float(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType != UBlackboardKeyType_Float::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Float but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Float

		// Bool
	#pragma region

	bool FLibrary::IsKey_BoolChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Bool::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Bool but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::SafeIsKey_Bool(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType != UBlackboardKeyType_Bool::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Bool but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Bool

		// String
	#pragma region

	bool FLibrary::IsKey_StringChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_String::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: String but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::SafeIsKey_String(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType != UBlackboardKeyType_String::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: String but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion String

		// Name
	#pragma region

	bool FLibrary::IsKey_NameChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Name::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Name but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::SafeIsKey_Name(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType != UBlackboardKeyType_Name::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Name but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Name

		// Vector
	#pragma region

	bool FLibrary::SafeIsKeyType_Vector(const FString& Context, const TSubclassOf<UBlackboardKeyType>& KeyType, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!KeyType.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType is NULL."), *Context));
			return false;
		}

		if (KeyType != UBlackboardKeyType_Vector::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType NOT of type: Object but of type: %s."), *Context, *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	bool FLibrary::IsKey_VectorChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Vector::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Vector but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::SafeIsKey_Vector(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType != UBlackboardKeyType_Vector::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Vector but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Vector

		// Rotator
	#pragma region

	bool FLibrary::IsKey_RotatorChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Rotator::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Rotator but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::SafeIsKey_Rotator(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType != UBlackboardKeyType_Rotator::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Rotator but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Rotator

	#pragma endregion Key
}