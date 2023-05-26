// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Script/CsScriptLibrary_Beam.h"
#include "CsBeam.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cached
#pragma region

namespace NCsScriptLibraryBeam
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsBeam = TEXT("FECsBeam");
			const FString Create = TEXT("Create");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Beam::UCsScriptLibrary_Beam(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

#define EnumMapType EMCsBeam
#define EnumType FECsBeam

EnumType UCsScriptLibrary_Beam::Create(const FString& Name, const FString& DisplayName)
{
	using namespace NCsScriptLibraryBeam::NCached;

	const FString& Context = Str::Create;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::CreateSafe<EnumMapType, EnumType>(Context, Name, DisplayName);
}

EnumType UCsScriptLibrary_Beam::Get(const FString& Name)
{
	using namespace NCsScriptLibraryBeam::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_Beam::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryBeam::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_Beam::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_Beam::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_Beam::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_Beam::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_Beam::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum