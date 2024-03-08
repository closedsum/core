// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/Script/CsScriptLibrary_BeamClass.h"
#include "CsBeam.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cached
#pragma region

namespace NCsScriptLibraryBeamClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsBeamClass = TEXT("FECsBeamClass");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_BeamClass::UCsScriptLibrary_BeamClass(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

#define EnumMapType EMCsBeamClass
#define EnumType FECsBeamClass

EnumType UCsScriptLibrary_BeamClass::Get(const FString& Name)
{
	using namespace NCsScriptLibraryBeamClass::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_BeamClass::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryBeamClass::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_BeamClass::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_BeamClass::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_BeamClass::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_BeamClass::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_BeamClass::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum