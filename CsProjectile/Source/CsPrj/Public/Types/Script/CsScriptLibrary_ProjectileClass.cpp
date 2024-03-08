// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Script/CsScriptLibrary_ProjectileClass.h"
#include "CsPrj.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cached
#pragma region

namespace NCsScriptLibraryProjectileClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsProjectileClass = TEXT("FECsProjectileClass");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_ProjectileClass::UCsScriptLibrary_ProjectileClass(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

#define EnumMapType EMCsProjectileClass
#define EnumType FECsProjectileClass

EnumType UCsScriptLibrary_ProjectileClass::Get(const FString& Name)
{
	using namespace NCsScriptLibraryProjectileClass::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_ProjectileClass::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryProjectileClass::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_ProjectileClass::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_ProjectileClass::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_ProjectileClass::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_ProjectileClass::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_ProjectileClass::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum