// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Menu/Script/CsScriptLibrary_Menu.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Enum.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Menu)

// Cached
#pragma region

namespace NCsScriptLibraryMenu
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsMenu = TEXT("FECsMenu");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Menu, Create);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Menu, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Menu, GetByIndex);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Menu::UCsScriptLibrary_Menu(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryMenu::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsScriptLibraryMenu::NCached; \
	const FString& Context = Str::__FunctionName

// Enum
#pragma region

#define EnumMapType EMCsMenu
#define EnumType FECsMenu

EnumType UCsScriptLibrary_Menu::Create(const FString& Name, const FString& DisplayName)
{
	SET_CONTEXT(Create);

	return CsEnumLibrary::CreateSafe<EnumMapType, EnumType>(Context, Name, DisplayName);
}

EnumType UCsScriptLibrary_Menu::Get(const FString& Name)
{
	SET_CONTEXT(Get);

	return CsEnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_Menu::GetByIndex(const int32& Index)
{
	SET_CONTEXT(GetByIndex);

	return CsEnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_Menu::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_Menu::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_Menu::GetAll(TArray<EnumType>& OutTypes)
{
	CsEnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_Menu::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_Menu::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

bool UCsScriptLibrary_Menu::NotEqual(const EnumType& A, const EnumType& B)
{
	return A != B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum

#undef USING_NS_CACHED
#undef SET_CONTEXT