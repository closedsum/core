// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Script/CsScriptLibrary_InputActionMap.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Log
#include "Utility/CsLog.h"

// Cached
#pragma region

namespace NCsScriptLibraryInputActionMap
{ 
	namespace NCached
	{
		namespace Str
		{
			const FString FECsInputActionMap = TEXT("FECsInputActionMap");
			const FString Create = TEXT("Create");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_InputActionMap::UCsScriptLibrary_InputActionMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define EnumMapType EMCsInputActionMap
#define EnumType FECsInputActionMap

EnumType UCsScriptLibrary_InputActionMap::Create(const FString& Name, const FString& DisplayName)
{
	using namespace NCsScriptLibraryInputActionMap::NCached;

	const FString& Context = Str::Create;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::CreateSafe<EnumMapType, EnumType>(Context, Name, DisplayName);
}

EnumType UCsScriptLibrary_InputActionMap::Get(const FString& Name)
{
	using namespace NCsScriptLibraryInputActionMap::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_InputActionMap::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryInputActionMap::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_InputActionMap::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_InputActionMap::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_InputActionMap::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_InputActionMap::GetNONE()
{
	return EnumMapType::Get().GetNONE();
}

bool UCsScriptLibrary_InputActionMap::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

bool UCsScriptLibrary_InputActionMap::IsValid(const EnumType& Enum)
{
	return EnumMapType::Get().IsValidEnum(Enum);
}

bool UCsScriptLibrary_InputActionMap::IsValidByName(const FString& Name)
{
	return EnumMapType::Get().IsValidEnum(Name);
}

#undef EnumMapType
#undef EnumType