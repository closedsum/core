// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/Script/CsScriptLibrary_InputActionMap.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cached
#pragma region

namespace NCsScriptLibraryInputActionMap
{ 
	namespace NCached
	{
		namespace Str
		{
			const FString FECsInputActionMap = TEXT("FECsInputActionMap");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_InputActionMap::UCsScriptLibrary_InputActionMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define EnumMapType EMCsInputActionMap
#define EnumType FECsInputActionMap

EnumType UCsScriptLibrary_InputActionMap::Get(const FString& Name)
{
	using namespace NCsScriptLibraryInputActionMap::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_InputActionMap::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryInputActionMap::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_InputActionMap::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_InputActionMap::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_InputActionMap::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_InputActionMap::GetNONE()
{
	return EnumMapType::Get().GetNONE();
}

bool UCsScriptLibrary_InputActionMap::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType