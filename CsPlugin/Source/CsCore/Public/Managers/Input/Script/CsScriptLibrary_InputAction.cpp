// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Script/CsScriptLibrary_InputAction.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"
#include "Managers/Input/CsLibrary_Input.h"

// Cached
#pragma region

namespace NCsScriptLibraryInputAction
{ 
	namespace NCached
	{
		namespace Str
		{
			const FString FECsInputAction = TEXT("FECsInputAction");
			const FString Create = TEXT("Create");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InputAction, GetByKey);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_InputAction::UCsScriptLibrary_InputAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define EnumMapType EMCsInputAction
#define EnumType FECsInputAction

EnumType UCsScriptLibrary_InputAction::Create(const FString& Name, const FString& DisplayName)
{
	using namespace NCsScriptLibraryInputAction::NCached;

	const FString& Context = Str::Create;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::CreateSafe<EnumMapType, EnumType>(Context, Name, DisplayName);
}

EnumType UCsScriptLibrary_InputAction::Get(const FString& Name)
{
	using namespace NCsScriptLibraryInputAction::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_InputAction::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryInputAction::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_InputAction::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_InputAction::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_InputAction::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_InputAction::GetMAX()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_InputAction::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

bool UCsScriptLibrary_InputAction::IsValid(const EnumType& Enum)
{
	return EnumMapType::Get().IsValidEnum(Enum);
}

bool UCsScriptLibrary_InputAction::IsValidByName(const FString& Name)
{
	return EnumMapType::Get().IsValidEnum(Name);
}

EnumType UCsScriptLibrary_InputAction::GetByKey(const FKey& Key)
{
	using namespace NCsScriptLibraryInputAction::NCached;

	const FString& Context = Str::GetByKey;

	typedef NCsInput::NAction::FLibrary InputActionLibrary;

	return InputActionLibrary::GetSafe(Context, Key);
}

#undef EnumMapType
#undef EnumType