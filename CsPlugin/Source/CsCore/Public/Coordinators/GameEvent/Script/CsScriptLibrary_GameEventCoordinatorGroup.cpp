// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameEvent/Script/CsScriptLibrary_GameEventCoordinatorGroup.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cache
#pragma region

namespace NCsScriptLibraryGameEventCoordinatorGroup
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsGameEventCoordinatorGroup = TEXT("FECsGameEventCoordinatorGroup");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cache

UCsScriptLibrary_GameEventCoordinatorGroup::UCsScriptLibrary_GameEventCoordinatorGroup(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define EnumMapType EMCsGameEventCoordinatorGroup
#define EnumType FECsGameEventCoordinatorGroup

EnumType UCsScriptLibrary_GameEventCoordinatorGroup::Get(const FString& Name)
{
	using namespace NCsScriptLibraryGameEventCoordinatorGroup::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_GameEventCoordinatorGroup::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryGameEventCoordinatorGroup::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_GameEventCoordinatorGroup::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_GameEventCoordinatorGroup::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_GameEventCoordinatorGroup::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, FECsGameEventCoordinatorGroup>(OutTypes);
}

EnumType UCsScriptLibrary_GameEventCoordinatorGroup::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_GameEventCoordinatorGroup::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType