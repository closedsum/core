// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Script/CsScriptLibrary_GameEvent.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cached
#pragma region

namespace NCsScriptLibraryGameEvent
{ 
	namespace NCached
	{
		namespace Str
		{
			const FString FECsGameEvent = TEXT("FECsGameEvent");
			const FString Create = TEXT("Create");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_GameEvent::UCsScriptLibrary_GameEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryGameEvent::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsScriptLibraryGameEvent::NCached; \
	const FString& Context = Str::__FunctionName
#define CLASS_TYPE UCsScriptLibrary_GameEvent
#define EnumLibrary NCsEnum::FLibrary
#define EnumMapType EMCsGameEvent
#define EnumType FECsGameEvent

void CLASS_TYPE::PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
{
	NCsGameEvent::PopulateEnumMapFromSettings(Context, ContextRoot);
}

EnumType CLASS_TYPE::Create(const FString& Name, const FString& DisplayName)
{
	SET_CONTEXT(Create);

	return EnumLibrary::CreateSafe<EnumMapType, EnumType>(Context, Name, DisplayName);
}

EnumType CLASS_TYPE::Get(const FString& Name)
{
	SET_CONTEXT(Get);

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType CLASS_TYPE::GetByIndex(const int32& Index)
{
	SET_CONTEXT(GetByIndex);

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString CLASS_TYPE::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 CLASS_TYPE::GetCount()
{
	return EnumMapType::Get().Num();
}

void CLASS_TYPE::GetAll(TArray<EnumType>& OutTypes)
{
	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType CLASS_TYPE::GetMAX()
{
	return EnumMapType::Get().GetMAX();
}

bool CLASS_TYPE::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

bool CLASS_TYPE::NotEqual(const EnumType& A, const EnumType& B)
{
	return A != B;
}

bool CLASS_TYPE::IsValid(const EnumType& Enum)
{
	return EnumMapType::Get().IsValidEnum(Enum);
}

bool CLASS_TYPE::IsValidByName(const FString& Name)
{
	return EnumMapType::Get().IsValidEnum(Name);
}

#undef USING_NS_CACHED
#undef SET_CONTEXT
#undef CLASS_TYPE
#undef EnumLibrary
#undef EnumMapType
#undef EnumType