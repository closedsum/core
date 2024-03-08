// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Blackboard/CsLibrary_Blackboard.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// AI
#include "BehaviorTree/BehaviorTreeComponent.h"
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
// Pawn
#include "GameFramework/Pawn.h"

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

	const UBlackboardComponent* FLibrary::GetComponentChecked(const FString& Context, const UBehaviorTreeComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component);

		const UBlackboardComponent* Blackboard = Component->GetBlackboardComponent();

		CS_IS_PENDING_KILL_CHECKED(Blackboard);
		return Blackboard;
	}

	UBlackboardComponent* FLibrary::GetComponentChecked(const FString& Context, UBehaviorTreeComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component);

		UBlackboardComponent* Blackboard = Component->GetBlackboardComponent();

		CS_IS_PENDING_KILL_CHECKED(Blackboard);
		return Blackboard;
	}

	const UBlackboardComponent* FLibrary::GetSafeComponent(const FString& Context, const UBehaviorTreeComponent* Component, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL_RET_NULL(Component);

		const UBlackboardComponent* Blackboard = Component->GetBlackboardComponent();

		CS_IS_PENDING_KILL_RET_NULL(Blackboard);
		return Blackboard;
	}

	UBlackboardComponent* FLibrary::GetSafeComponent(const FString& Context, UBehaviorTreeComponent* Component, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL_RET_NULL(Component);

		UBlackboardComponent* Blackboard = Component->GetBlackboardComponent();

		CS_IS_PENDING_KILL_RET_NULL(Blackboard);
		return Blackboard;
	}

	// Key
	#pragma region

	bool FLibrary::IsValidChecked(const FString& Context, const FBlackboardKeySelector& KeySelector)
	{
		checkf(KeySelector.IsSet(), TEXT("%s: KeySelector is NOT Set."), *Context);
		CS_IS_NAME_NONE_CHECKED(KeySelector.SelectedKeyName);
		checkf(KeySelector.SelectedKeyType.Get(), TEXT("%s: KeySelector has NO type."), *Context);
		return true;
	}

	bool FLibrary::IsValid(const FString& Context, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!KeySelector.IsSet())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeySelector is NOT Set."), *Context));
			return false;
		}

		CS_IS_NAME_NONE(KeySelector.SelectedKeyName);

		if (!KeySelector.SelectedKeyType.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeySelector has NO type."), *Context));
			return false;
		}
		return true;
	}

	bool FLibrary::AreEqualChecked(const FString& Context, const TSubclassOf<UBlackboardKeyType>& A, const TSubclassOf<UBlackboardKeyType>& B)
	{
		checkf(A.Get(), TEXT("%s: A is NULL."), *Context);
		checkf(B.Get(), TEXT("%s: B is NULL."), *Context);
		checkf(A.Get() == B.Get(), TEXT("%s: A != B."), *Context);
		return true;
	}

	bool FLibrary::SafeAreEqual(const FString& Context, const TSubclassOf<UBlackboardKeyType>& A, const TSubclassOf<UBlackboardKeyType>& B, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!A.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: A is NULL."), *Context));
			return false;
		}

		if (!B.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: B is NULL."), *Context));
			return false;
		}

		if (A.Get() != B.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: A != B."), *Context));
			return false;
		}
		return true;
	}

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

	uint16 FLibrary::GetKeyIDChecked(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		CS_IS_PENDING_KILL_CHECKED(Data)
		CS_IS_NAME_NONE_CHECKED(KeyName)

		FBlackboard::FKey ID = Data->GetKeyID(KeyName);

		checkf(ID != FBlackboard::InvalidKey, TEXT("%s: %s does NOT have Key: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()));
		return ID;
	}

	uint16 FLibrary::GetSafeKeyID(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
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

	TSubclassOf<UBlackboardKeyType> FLibrary::GetKeyTypeChecked(const FString& Context, const UBlackboardData* Data, const uint16& KeyID)
	{
		CS_IS_PENDING_KILL_CHECKED(Data)
	
		checkf(KeyID != (uint16)FBlackboard::InvalidKey, TEXT("%s: KeyID is NOT Valid."), *Context);

		TSubclassOf<UBlackboardKeyType> KeyType = Data->GetKeyType(KeyID);
		
		checkf(KeyType.Get(), TEXT("%s: %s with Key with KeyID: %d does NOT have a valid type."), *Context, *(Data->GetName()), KeyID);
		return KeyType;
	}

	TSubclassOf<UBlackboardKeyType> FLibrary::GetSafeKeyType(const FString& Context, const UBlackboardData* Data, const uint16& KeyID, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL_RET_NULL(Data)

		if (KeyID == (uint16)FBlackboard::InvalidKey)
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
			return TSubclassOf<UBlackboardKeyType>();
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

#if !UE_BUILD_SHIPPING

	bool FLibrary::IsKeyChecked_Object(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);
		
		checkf(KeyType.Get() == UBlackboardKeyType_Object::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Object but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::IsKeyChecked_Object(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector)
	{
		check(HasKeyChecked(Context, Data, KeySelector));
		checkf(KeySelector.SelectedKeyType.Get() == UBlackboardKeyType_Object::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Object but of type: %s."), *Context, *(Data->GetName()), *(KeySelector.SelectedKeyName.ToString()), *KeyTypeToString(KeySelector.SelectedKeyType));
		return true;
	}

	bool FLibrary::IsKeyChecked_Object(const FString& Context, const FBlackboardKeySelector& KeySelector)
	{
		check(IsValidChecked(Context, KeySelector));
		checkf(KeySelector.SelectedKeyType.Get() == UBlackboardKeyType_Object::StaticClass(), TEXT("%s: KeySelector: %s is NOT of type: Object but of type: %s."), *Context, *(KeySelector.SelectedKeyName.ToString()), *KeyTypeToString(KeySelector.SelectedKeyType));
		return true;
	}

#endif // #if !UE_BUILD_SHIPPING

	bool FLibrary::SafeIsKey_Object(const FString& Context, const UBlackboardData* Data, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetSafeKeyType(Context, Data, KeyName, Log);

		if (KeyType.Get() != UBlackboardKeyType_Object::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Object but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	bool FLibrary::SafeIsKey_Object(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeHasKey(Context, Data, KeySelector, Log))
			return false;

		if (KeySelector.SelectedKeyType.Get() != UBlackboardKeyType_Object::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Object but of type: %s."), *Context, *(Data->GetName()), *(KeySelector.SelectedKeyName.ToString()), *KeyTypeToString(KeySelector.SelectedKeyType)));
			return false;
		}
		return true;
	}

	bool FLibrary::SafeIsKey_Object(const FString& Context, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!IsValid(Context, KeySelector, Log))
			return false;

		if (KeySelector.SelectedKeyType.Get() != UBlackboardKeyType_Object::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeySelector: %s is NOT of type: Object but of type: %s."), *Context, *(KeySelector.SelectedKeyName.ToString()), *KeyTypeToString(KeySelector.SelectedKeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Object

		// Class
	#pragma region

	bool FLibrary::IsKeyChecked_Class(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
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

	bool FLibrary::SafeIsKeyType_Enum(const FString& Context, const TSubclassOf<UBlackboardKeyType>& KeyType, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!KeyType.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType is NULL."), *Context));
			return false;
		}

		if (KeyType != UBlackboardKeyType_Enum::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType NOT of type: Enum but of type: %s."), *Context, *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	bool FLibrary::IsKeyChecked_Enum(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Enum::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Enum but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::IsKeyChecked_Enum(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector)
	{
		check(HasKeyChecked(Context, Data, KeySelector));
		checkf(KeySelector.SelectedKeyType.Get() == UBlackboardKeyType_Enum::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Enum but of type: %s."), *Context, *(Data->GetName()), *(KeySelector.SelectedKeyName.ToString()), *KeyTypeToString(KeySelector.SelectedKeyType));
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

	bool FLibrary::SafeIsKey_Enum(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeHasKey(Context, Data, KeySelector, Log))
			return false;

		if (KeySelector.SelectedKeyType.Get() != UBlackboardKeyType_Enum::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Enum but of type: %s."), *Context, *(Data->GetName()), *(KeySelector.SelectedKeyName.ToString()), *KeyTypeToString(KeySelector.SelectedKeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Enum

		// Int
	#pragma region

	bool FLibrary::SafeIsKeyType_Int(const FString& Context, const TSubclassOf<UBlackboardKeyType>& KeyType, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!KeyType.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType is NULL."), *Context));
			return false;
		}

		if (KeyType != UBlackboardKeyType_Int::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType NOT of type: Int but of type: %s."), *Context, *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	bool FLibrary::IsKeyChecked_Int(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Int::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Int but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::IsKeyChecked_Int(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector)
	{
		check(HasKeyChecked(Context, Data, KeySelector));
		checkf(KeySelector.SelectedKeyType.Get() == UBlackboardKeyType_Int::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Int but of type: %s."), *Context, *(Data->GetName()), *(KeySelector.SelectedKeyName.ToString()), *KeyTypeToString(KeySelector.SelectedKeyType));
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

	bool FLibrary::SafeIsKey_Int(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeHasKey(Context, Data, KeySelector, Log))
			return false;

		if (KeySelector.SelectedKeyType.Get() != UBlackboardKeyType_Int::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Int but of type: %s."), *Context, *(Data->GetName()), *(KeySelector.SelectedKeyName.ToString()), *KeyTypeToString(KeySelector.SelectedKeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Int

		// Float
	#pragma region

	bool FLibrary::SafeIsKeyType_Float(const FString& Context, const TSubclassOf<UBlackboardKeyType>& KeyType, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!KeyType.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType is NULL."), *Context));
			return false;
		}

		if (KeyType != UBlackboardKeyType_Float::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyType NOT of type: Float but of type: %s."), *Context, *KeyTypeToString(KeyType)));
			return false;
		}
		return true;
	}

	bool FLibrary::IsKeyChecked_Float(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
	{
		TSubclassOf<UBlackboardKeyType> KeyType = GetKeyTypeChecked(Context, Data, KeyName);

		checkf(KeyType == UBlackboardKeyType_Float::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Float but of type: %s."), *Context, *(Data->GetName()), *(KeyName.ToString()), *KeyTypeToString(KeyType));
		return true;
	}

	bool FLibrary::IsKeyChecked_Float(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector)
	{
		check(HasKeyChecked(Context, Data, KeySelector));
		checkf(KeySelector.SelectedKeyType.Get() == UBlackboardKeyType_Float::StaticClass(), TEXT("%s: %s with Key: %s is NOT of type: Float but of type: %s."), *Context, *(Data->GetName()), *(KeySelector.SelectedKeyName.ToString()), *KeyTypeToString(KeySelector.SelectedKeyType));
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

	bool FLibrary::SafeIsKey_Float(const FString& Context, const UBlackboardData* Data, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeHasKey(Context, Data, KeySelector, Log))
			return false;

		if (KeySelector.SelectedKeyType.Get() != UBlackboardKeyType_Float::StaticClass())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s with Key: %s is NOT of type: Float but of type: %s."), *Context, *(Data->GetName()), *(KeySelector.SelectedKeyName.ToString()), *KeyTypeToString(KeySelector.SelectedKeyType)));
			return false;
		}
		return true;
	}

	#pragma endregion Float

		// Bool
	#pragma region

	bool FLibrary::IsKeyChecked_Bool(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
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

	bool FLibrary::IsKeyChecked_String(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
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

	bool FLibrary::IsKeyChecked_Name(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
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

	bool FLibrary::IsKeyChecked_Vector(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
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

	bool FLibrary::IsKeyChecked_Rotator(const FString& Context, const UBlackboardData* Data, const FName& KeyName)
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

	// Set
	#pragma region

		// Object
	#pragma region
	
	void FLibrary::SetObjectChecked(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, UObject* ObjectValue)
	{
		check(IsKeyChecked_Object(Context, Component, KeyName));

		Component->SetValueAsObject(KeyName, ObjectValue);
	}
	
	void FLibrary::SetObjectChecked(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
	{
		check(IsKeyChecked_Object(Context, Component, KeySelector));

		Component->SetValueAsObject(KeySelector.SelectedKeyName, ObjectValue);
	}

	bool FLibrary::SetSafeObject(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Object(Context, Component, KeyName))
			return false;

		Component->SetValueAsObject(KeyName, ObjectValue);
		return true;
	}

	bool FLibrary::SetSafeObject(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Object(Context, Component, KeySelector))
			return false;

		Component->SetValueAsObject(KeySelector.SelectedKeyName, ObjectValue);
		return true;
	}

	void FLibrary::SetObjectChecked2(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, UObject* ObjectValue)
	{
		check(IsKeyChecked_Object(Context, Component, KeyName));
		CS_IS_PENDING_KILL_CHECKED(ObjectValue)

		Component->SetValueAsObject(KeyName, ObjectValue);
	}
	
	void FLibrary::SetObjectChecked2(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue)
	{
		check(IsKeyChecked_Object(Context, Component, KeySelector));
		CS_IS_PENDING_KILL_CHECKED(ObjectValue)

		Component->SetValueAsObject(KeySelector.SelectedKeyName, ObjectValue);
	}

	bool FLibrary::SetSafeObject2(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Object(Context, Component, KeyName))
			return false;

		CS_IS_PENDING_KILL(ObjectValue)

		Component->SetValueAsObject(KeyName, ObjectValue);
		return true;
	}

	bool FLibrary::SetSafeObject2(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Object(Context, Component, KeySelector))
			return false;

		CS_IS_PENDING_KILL(ObjectValue)

		Component->SetValueAsObject(KeySelector.SelectedKeyName, ObjectValue);
		return true;
	}

	#pragma endregion Object

		// Pawn
	#pragma region
	
	void FLibrary::SetPawnChecked(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, APawn* PawnValue)
	{
		check(IsKeyChecked_Object(Context, Component, KeyName));

		Component->SetValueAsObject(KeyName, PawnValue);
	}
	
	void FLibrary::SetPawnChecked(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
	{
		check(IsKeyChecked_Object(Context, Component, KeySelector));

		Component->SetValueAsObject(KeySelector.SelectedKeyName, PawnValue);
	}

	bool FLibrary::SetSafePawn(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, APawn* PawnValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Object(Context, Component, KeyName))
			return false;

		Component->SetValueAsObject(KeyName, PawnValue);
		return true;
	}

	bool FLibrary::SetSafePawn(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, APawn* PawnValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Object(Context, Component, KeySelector))
			return false;

		Component->SetValueAsObject(KeySelector.SelectedKeyName, PawnValue);
		return true;
	}

	void FLibrary::SetPawnChecked2(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, APawn* PawnValue)
	{
		check(IsKeyChecked_Object(Context, Component, KeyName));
		CS_IS_PENDING_KILL_CHECKED(PawnValue)

		Component->SetValueAsObject(KeyName, PawnValue);
	}
	
	void FLibrary::SetPawnChecked2(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, APawn* PawnValue)
	{
		check(IsKeyChecked_Object(Context, Component, KeySelector));
		CS_IS_PENDING_KILL_CHECKED(PawnValue)

		Component->SetValueAsObject(KeySelector.SelectedKeyName, PawnValue);
	}

	bool FLibrary::SetSafePawn2(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, APawn* PawnValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Object(Context, Component, KeyName))
			return false;

		CS_IS_PENDING_KILL(PawnValue)

		Component->SetValueAsObject(KeyName, PawnValue);
		return true;
	}

	bool FLibrary::SetSafePawn2(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, APawn* PawnValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Object(Context, Component, KeySelector))
			return false;

		CS_IS_PENDING_KILL(PawnValue)

		Component->SetValueAsObject(KeySelector.SelectedKeyName, PawnValue);
		return true;
	}

	#pragma endregion Pawn

		// Enum
	#pragma region
	
	void FLibrary::SetEnumChecked(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const uint8& EnumValue)
	{
		check(IsKeyChecked_Enum(Context, Component, KeyName));

		Component->SetValueAsEnum(KeyName, EnumValue);
	}
	
	void FLibrary::SetEnumChecked(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue)
	{
		check(IsKeyChecked_Enum(Context, Component, KeySelector));

		Component->SetValueAsEnum(KeySelector.SelectedKeyName, EnumValue);
	}

	bool FLibrary::SetSafeEnum(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const uint8& EnumValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Enum(Context, Component, KeyName))
			return false;

		Component->SetValueAsEnum(KeyName, EnumValue);
		return true;
	}

	bool FLibrary::SetSafeEnum(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Enum(Context, Component, KeySelector))
			return false;

		Component->SetValueAsEnum(KeySelector.SelectedKeyName, EnumValue);
		return true;
	}

	#pragma endregion Enum

		// Int
	#pragma region
	
	void FLibrary::SetIntChecked(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const int32& IntValue)
	{
		check(IsKeyChecked_Int(Context, Component, KeyName));

		Component->SetValueAsInt(KeyName, IntValue);
	}
	
	void FLibrary::SetIntChecked(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, const int32& IntValue)
	{
		check(IsKeyChecked_Int(Context, Component, KeySelector));

		Component->SetValueAsInt(KeySelector.SelectedKeyName, IntValue);
	}

	bool FLibrary::SetSafeInt(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const int32& IntValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Int(Context, Component, KeyName))
			return false;

		Component->SetValueAsInt(KeyName, IntValue);
		return true;
	}

	bool FLibrary::SetSafeInt(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, const int32& IntValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Int(Context, Component, KeySelector))
			return false;

		Component->SetValueAsInt(KeySelector.SelectedKeyName, IntValue);
		return true;
	}

	void FLibrary::IncrementIntChecked(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const int32& Amount /*=1*/)
	{
		check(IsKeyChecked_Int(Context, Component, KeyName));
		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Amount, 1)

		int32 Value = Component->GetValueAsInt(KeyName);

		Component->SetValueAsInt(KeyName, Value + Amount);
	}

	bool FLibrary::SafeIncrementInt(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const int32& Amount /*=1*/, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Int(Context, Component, KeyName))
			return false;

		CS_IS_INT_GREATER_THAN_OR_EQUAL(Amount, 1)

		int32 Value = Component->GetValueAsInt(KeyName);

		Component->SetValueAsInt(KeyName, Value + Amount);
		return true;
	}

	#pragma endregion Int

		// Float
	#pragma region
	
	void FLibrary::SetFloatChecked(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const float& FloatValue)
	{
		check(IsKeyChecked_Float(Context, Component, KeyName));

		Component->SetValueAsFloat(KeyName, FloatValue);
	}
	
	void FLibrary::SetFloatChecked(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, const float& FloatValue)
	{
		check(IsKeyChecked_Float(Context, Component, KeySelector));

		Component->SetValueAsFloat(KeySelector.SelectedKeyName, FloatValue);
	}

	bool FLibrary::SetSafeFloat(const FString& Context, UBlackboardComponent* Component, const FName& KeyName, const float& FloatValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Float(Context, Component, KeyName))
			return false;

		Component->SetValueAsFloat(KeyName, FloatValue);
		return true;
	}

	bool FLibrary::SetSafeFloat(const FString& Context, UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, const float& FloatValue, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Float(Context, Component, KeySelector))
			return false;

		Component->SetValueAsFloat(KeySelector.SelectedKeyName, FloatValue);
		return true;
	}

	#pragma endregion Float

	#pragma endregion Set

	// Get
	#pragma region

		// Object
	#pragma region

	UObject* FLibrary::GetObjectChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
	{
		check(IsKeyChecked_Object(Context, Component, KeyName));
		return Component->GetValueAsObject(KeyName);
	}

	UObject* FLibrary::GetObjectChecked(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector)
	{
		check(IsKeyChecked_Object(Context, Component, KeySelector));
		return Component->GetValueAsObject(KeySelector.SelectedKeyName);
	}

	UObject* FLibrary::GetSafeObject(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		OutSuccess = false;

		if (!SafeIsKey_Object(Context, Component, KeyName, Log))
			return nullptr;

		UObject* O = Component->GetValueAsObject(KeyName);
		OutSuccess = O != nullptr;

		return O;
	}

	UObject* FLibrary::GetSafeObject(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		OutSuccess = false;

		if (!SafeIsKey_Object(Context, Component, KeySelector, Log))
			return nullptr;

		UObject* O = Component->GetValueAsObject(KeySelector.SelectedKeyName);
		OutSuccess = O != nullptr;

		return O;
	}

	#pragma endregion Object

		// Pawn
	#pragma region

	APawn* FLibrary::GetPawnChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
	{
		check(IsKeyChecked_Object(Context, Component, KeyName));

		UObject* O = Component->GetValueAsObject(KeyName);

		return CS_CAST_CHECKED(O, UObject, APawn);
	}

	APawn* FLibrary::GetPawnChecked(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector)
	{
		check(IsKeyChecked_Object(Context, Component, KeySelector));

		UObject* O = Component->GetValueAsObject(KeySelector.SelectedKeyName);

		return CS_CAST_CHECKED(O, UObject, APawn);
	}

	APawn* FLibrary::GetSafePawn(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		OutSuccess = false;

		if (!SafeIsKey_Object(Context, Component, KeyName, Log))
			return nullptr;

		UObject* O = Component->GetValueAsObject(KeyName);
		APawn* P   = CS_CAST(O, UObject, APawn);
		OutSuccess = P != nullptr;

		return P;
	}

	APawn* FLibrary::GetSafePawn(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		OutSuccess = false;

		if (!SafeIsKey_Object(Context, Component, KeySelector, Log))
			return nullptr;

		UObject* O = Component->GetValueAsObject(KeySelector.SelectedKeyName);
		APawn* P   = CS_CAST(O, UObject, APawn);
		OutSuccess = P != nullptr;

		return P;
	}

	#pragma endregion Pawn

		// Enum
	#pragma region

	uint8 FLibrary::GetEnumChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
	{
		check(IsKeyChecked_Enum(Context, Component, KeyName));
		return Component->GetValueAsEnum(KeyName);
	}

	uint8 FLibrary::GetEnumChecked(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector)
	{
		check(IsKeyChecked_Enum(Context, Component, KeySelector));
		return Component->GetValueAsEnum(KeySelector.SelectedKeyName);
	}

	uint8 FLibrary::GetSafeEnum(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		OutSuccess = false;

		if (!SafeIsKey_Enum(Context, Component, KeyName, Log))
			return 0;

		OutSuccess = true;
		return Component->GetValueAsEnum(KeyName);
	}

	uint8 FLibrary::GetSafeEnum(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		OutSuccess = false;

		if (!SafeIsKey_Enum(Context, Component, KeySelector, Log))
			return 0;

		OutSuccess = true;
		return Component->GetValueAsEnum(KeySelector.SelectedKeyName);
	}

	#pragma endregion Enum

		// Int
	#pragma region

	int32 FLibrary::GetIntChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
	{
		check(IsKeyChecked_Int(Context, Component, KeyName));
		return Component->GetValueAsInt(KeyName);
	}

	int32 FLibrary::GetIntChecked(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector)
	{
		check(IsKeyChecked_Int(Context, Component, KeySelector));
		return Component->GetValueAsInt(KeySelector.SelectedKeyName);
	}

	int32 FLibrary::GetSafeInt(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		OutSuccess = false;

		if (!SafeIsKey_Int(Context, Component, KeyName, Log))
			return 0;

		OutSuccess = true;
		return Component->GetValueAsInt(KeyName);
	}

	int32 FLibrary::GetSafeInt(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		OutSuccess = false;

		if (!SafeIsKey_Int(Context, Component, KeySelector, Log))
			return 0;

		OutSuccess = true;
		return Component->GetValueAsInt(KeySelector.SelectedKeyName);
	}

	#pragma endregion Int

		// Float
	#pragma region

	float FLibrary::GetFloatChecked(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName)
	{
		check(IsKeyChecked_Float(Context, Component, KeyName));
		return Component->GetValueAsFloat(KeyName);
	}

	float FLibrary::GetFloatChecked(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector)
	{
		check(IsKeyChecked_Float(Context, Component, KeySelector));
		return Component->GetValueAsFloat(KeySelector.SelectedKeyName);
	}

	float FLibrary::GetSafeFloat(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		OutSuccess = false;

		if (!SafeIsKey_Float(Context, Component, KeyName, Log))
			return 0;

		OutSuccess = true;
		return Component->GetValueAsFloat(KeyName);
	}

	float FLibrary::GetSafeFloat(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		OutSuccess = false;

		if (!SafeIsKey_Float(Context, Component, KeySelector, Log))
			return 0;

		OutSuccess = true;
		return Component->GetValueAsFloat(KeySelector.SelectedKeyName);
	}

	float FLibrary::GetSafeFloat(const FString& Context, const UBlackboardComponent* Component, const FName& KeyName, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Float(Context, Component, KeyName, Log))
			return 0;
		return Component->GetValueAsFloat(KeyName);
	}

	float FLibrary::GetSafeFloat(const FString& Context, const UBlackboardComponent* Component, const FBlackboardKeySelector& KeySelector, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		if (!SafeIsKey_Float(Context, Component, KeySelector, Log))
			return 0;
		return Component->GetValueAsFloat(KeySelector.SelectedKeyName);
	}

	#pragma endregion Float

	#pragma endregion Get
}