// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/Script/CsScriptLibrary_UpdateGroup.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cache
#pragma region

namespace NCsScriptLibraryUpdateGroup
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsUpdateGroup = TEXT("FECsUpdateGroup");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cache

UCsScriptLibrary_UpdateGroup::UCsScriptLibrary_UpdateGroup(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


FECsUpdateGroup UCsScriptLibrary_UpdateGroup::Get(const FString& Name)
{
	using namespace NCsScriptLibraryUpdateGroup::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EMCsUpdateGroup, FECsUpdateGroup>(Context, Str::FECsUpdateGroup, Name);
}

FECsUpdateGroup UCsScriptLibrary_UpdateGroup::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryUpdateGroup::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EMCsUpdateGroup, FECsUpdateGroup>(Context, Str::FECsUpdateGroup, Index);
}

FString UCsScriptLibrary_UpdateGroup::ToString(const FECsUpdateGroup& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_UpdateGroup::GetCount()
{
	return EMCsUpdateGroup::Get().Num();
}

void UCsScriptLibrary_UpdateGroup::GetAll(TArray<FECsUpdateGroup>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EMCsUpdateGroup, FECsUpdateGroup>(OutTypes);
}

FECsUpdateGroup UCsScriptLibrary_UpdateGroup::GetMax()
{
	return EMCsUpdateGroup::Get().GetMAX();
}

bool UCsScriptLibrary_UpdateGroup::EqualEqual(const FECsUpdateGroup& A, const FECsUpdateGroup& B)
{
	return A == B;
}