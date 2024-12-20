// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Script/CsScriptLibrary_Projectile.h"

// Library
#include "Library/CsLibrary_Enum.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Projectile)

// Cached
#pragma region

namespace NCsScriptLibraryProjectile
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsProjectile = TEXT("FECsProjectile");
			const FString Create = TEXT("Create");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Projectile::UCsScriptLibrary_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

#define EnumMapType EMCsProjectile
#define EnumType FECsProjectile

EnumType UCsScriptLibrary_Projectile::Create(const FString& Name, const FString& DisplayName)
{
	using namespace NCsScriptLibraryProjectile::NCached;

	const FString& Context = Str::Create;

	return CsEnumLibrary::CreateSafe<EnumMapType, EnumType>(Context, Name, DisplayName);
}

EnumType UCsScriptLibrary_Projectile::Get(const FString& Name)
{
	using namespace NCsScriptLibraryProjectile::NCached;

	const FString& Context = Str::Get;

	return CsEnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_Projectile::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryProjectile::NCached;

	const FString& Context = Str::GetByIndex;

	return CsEnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_Projectile::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_Projectile::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_Projectile::GetAll(TArray<EnumType>& OutTypes)
{
	CsEnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_Projectile::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_Projectile::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum