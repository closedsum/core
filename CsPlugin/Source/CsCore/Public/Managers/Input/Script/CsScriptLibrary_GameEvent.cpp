// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

#define EnumMapType EMCsGameEvent
#define EnumType FECsGameEvent

EnumType UCsScriptLibrary_GameEvent::Create(const FString& Name, const FString& DisplayName)
{
	using namespace NCsScriptLibraryGameEvent::NCached;

	const FString& Context = Str::Create;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::CreateSafe<EnumMapType, EnumType>(Context, Name, DisplayName);
}

EnumType UCsScriptLibrary_GameEvent::Get(const FString& Name)
{
	using namespace NCsScriptLibraryGameEvent::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_GameEvent::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryGameEvent::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_GameEvent::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_GameEvent::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_GameEvent::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_GameEvent::GetMAX()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_GameEvent::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType