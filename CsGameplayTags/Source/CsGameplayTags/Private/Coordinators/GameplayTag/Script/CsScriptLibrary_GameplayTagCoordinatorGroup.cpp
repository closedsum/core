// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameplayTag/Script/CsScriptLibrary_GameplayTagCoordinatorGroup.h"

// Library
#include "Library/CsLibrary_Enum.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_GameplayTagCoordinatorGroup)

// Cache
#pragma region

namespace NCsScriptLibraryGameplayTagCoordinatorGroup
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsGameplayTagCoordinatorGroup = TEXT("FECsGameplayTagCoordinatorGroup");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cache

UCsScriptLibrary_GameplayTagCoordinatorGroup::UCsScriptLibrary_GameplayTagCoordinatorGroup(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryGameplayTagCoordinatorGroup::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsScriptLibraryGameplayTagCoordinatorGroup::NCached; \
	const FString& Context = Str::__FunctionName
#define THISCLASS UCsScriptLibrary_GameplayTagCoordinatorGroup
#define EnumLibrary NCsEnum::FLibrary
#define EnumMapType EMCsGameplayTagCoordinatorGroup
#define EnumType FECsGameplayTagCoordinatorGroup

EnumType THISCLASS::Get(const FString& Name)
{
	SET_CONTEXT(Get);

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType THISCLASS::GetByIndex(const int32& Index)
{
	SET_CONTEXT(GetByIndex);

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString THISCLASS::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 THISCLASS::GetCount()
{
	return EnumMapType::Get().Num();
}

void THISCLASS::GetAll(TArray<EnumType>& OutTypes)
{
	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType THISCLASS::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool THISCLASS::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef THISCLASS
#undef EnumLibrary
#undef EnumMapType
#undef EnumType