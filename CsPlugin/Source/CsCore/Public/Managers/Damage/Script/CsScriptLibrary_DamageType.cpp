// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Script/CsScriptLibrary_DamageType.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cached
#pragma region

namespace NCsScriptLibraryDamageType
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsDamageType = TEXT("FECsDamageType");
			const FString Create = TEXT("Create");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_DamageType::UCsScriptLibrary_DamageType(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

#define EnumMapType EMCsDamageType
#define EnumType FECsDamageType

EnumType UCsScriptLibrary_DamageType::Create(const FString& Name, const FString& DisplayName)
{
	using namespace NCsScriptLibraryDamageType::NCached;

	const FString& Context = Str::Create;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::CreateSafe<EnumMapType, EnumType>(Context, Name, DisplayName);
}

EnumType UCsScriptLibrary_DamageType::Get(const FString& Name)
{
	using namespace NCsScriptLibraryDamageType::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_DamageType::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryDamageType::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_DamageType::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_DamageType::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_DamageType::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_DamageType::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_DamageType::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

bool UCsScriptLibrary_DamageType::NotEqual(const EnumType& A, const EnumType& B)
{
	return A != B;
}

bool UCsScriptLibrary_DamageType::IsValid(const EnumType& Enum)
{
	return EnumMapType::Get().IsValidEnum(Enum);
}

bool UCsScriptLibrary_DamageType::IsValidByName(const FString& Name)
{
	return EnumMapType::Get().IsValidEnum(Name);
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum