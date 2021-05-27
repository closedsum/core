// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Script/CsScriptLibrary_WeaponClass.h"
#include "CsWp.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cached
#pragma region

namespace NCsScriptLibraryWeaponClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsWeaponClass = TEXT("FECsWeaponClass");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_WeaponClass::UCsScriptLibrary_WeaponClass(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

#define EnumMapType EMCsWeaponClass
#define EnumType FECsWeaponClass

EnumType UCsScriptLibrary_WeaponClass::Get(const FString& Name)
{
	using namespace NCsScriptLibraryWeaponClass::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_WeaponClass::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryWeaponClass::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_WeaponClass::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_WeaponClass::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_WeaponClass::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_WeaponClass::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_WeaponClass::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum