// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Script/CsScriptLibrary_WeaponClass.h"

// Library
#include "Library/CsLibrary_Enum.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_WeaponClass)

// Cached
#pragma region

namespace NCsScriptLibraryWeaponClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsWeaponClass = TEXT("FECsWeaponClass");
			const FString Create = TEXT("Create");
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

EnumType UCsScriptLibrary_WeaponClass::Create(const FString& Name, const FString& DisplayName)
{
	using namespace NCsScriptLibraryWeaponClass::NCached;

	const FString& Context = Str::Create;

	return CsEnumLibrary::CreateSafe<EnumMapType, EnumType>(Context, Name, DisplayName);
}

EnumType UCsScriptLibrary_WeaponClass::Get(const FString& Name)
{
	using namespace NCsScriptLibraryWeaponClass::NCached;

	const FString& Context = Str::Get;

	return CsEnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_WeaponClass::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryWeaponClass::NCached;

	const FString& Context = Str::GetByIndex;

	return CsEnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
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
	CsEnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
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