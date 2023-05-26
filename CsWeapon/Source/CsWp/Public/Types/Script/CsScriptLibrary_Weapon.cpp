// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Script/CsScriptLibrary_Weapon.h"
#include "CsWp.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cached
#pragma region

namespace NCsScriptLibraryWeapon
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsWeapon = TEXT("FECsWeapon");
			const FString Create = TEXT("Create");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Weapon::UCsScriptLibrary_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

#define EnumMapType EMCsWeapon
#define EnumType FECsWeapon

EnumType UCsScriptLibrary_Weapon::Create(const FString& Name, const FString& DisplayName)
{
	using namespace NCsScriptLibraryWeapon::NCached;

	const FString& Context = Str::Create;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::CreateSafe<EnumMapType, EnumType>(Context, Name, DisplayName);
}

EnumType UCsScriptLibrary_Weapon::Get(const FString& Name)
{
	using namespace NCsScriptLibraryWeapon::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_Weapon::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryWeapon::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_Weapon::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_Weapon::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_Weapon::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_Weapon::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_Weapon::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum