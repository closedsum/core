// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/Library/CsLibrary_AI_Enum.h"
#include "CsCoreDEPRECATED.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cache
#pragma region

namespace NCsLibraryAIEnumCached
{
	namespace Str
	{
		// AI

			// Type
		const FString FECsAIType = TEXT("FECsAIType");
		const FString GetECsAIType = TEXT("GetECsAIType");
		const FString GetECsAITypeByIndex = TEXT("GetECsAITypeByIndex");
			// State
		const FString FECsAIState = TEXT("FECsAIState");
		const FString GetECsAIState = TEXT("GetECsAIState");
		const FString GetECsAIStateByIndex = TEXT("GetECsAIStateByIndex");
			// Setup
		const FString FECsAISetup = TEXT("FECsAISetup");
		const FString GetECsAISetup = TEXT("GetECsAISetup");
		const FString GetECsAISetupByIndex = TEXT("GetECsAISetupByIndex");
	}
}

#pragma endregion Cache

UCsLibrary_AI_Enum::UCsLibrary_AI_Enum(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// AI
#pragma region

	// Type
#pragma region

FECsAIType UCsLibrary_AI_Enum::GetECsAIType(const FString& Name)
{
	return UCsLibrary_Enum::GetEnum<EMCsAIType, FECsAIType>(NCsLibraryAIEnumCached::Str::GetECsAIType, NCsLibraryAIEnumCached::Str::FECsAIType, Name);
}

FECsAIType UCsLibrary_AI_Enum::GetECsAITypeByIndex(const int32& Index)
{
	return UCsLibrary_Enum::GetEnumByIndex<EMCsAIType, FECsAIType>(NCsLibraryAIEnumCached::Str::GetECsAITypeByIndex, NCsLibraryAIEnumCached::Str::FECsAIType, Index);
}

FString UCsLibrary_AI_Enum::ECsAITypeToString(const FECsAIType& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_AI_Enum::GetECsAITypeCount()
{
	return EMCsAIType::Get().Num();
}

void UCsLibrary_AI_Enum::GetAllECsAIType(TArray<FECsAIType>& OutTypes)
{
	UCsLibrary_Enum::GetAllEnum<EMCsAIType, FECsAIType>(OutTypes);
}

#pragma endregion Type

	// State
#pragma region

FECsAIState UCsLibrary_AI_Enum::GetECsAIState(const FString& Name)
{
	return UCsLibrary_Enum::GetEnum<EMCsAIState, FECsAIState>(NCsLibraryAIEnumCached::Str::GetECsAIState, NCsLibraryAIEnumCached::Str::FECsAIState, Name);
}

FECsAIState UCsLibrary_AI_Enum::GetECsAIStateByIndex(const int32& Index)
{
	return UCsLibrary_Enum::GetEnumByIndex<EMCsAIState, FECsAIState>(NCsLibraryAIEnumCached::Str::GetECsAIStateByIndex, NCsLibraryAIEnumCached::Str::FECsAIState, Index);
}

FString UCsLibrary_AI_Enum::ECsAIStateToString(const FECsAIState& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_AI_Enum::GetECsAIStateCount()
{
	return EMCsAIState::Get().Num();
}

void UCsLibrary_AI_Enum::GetAllECsAIState(TArray<FECsAIState>& OutTypes)
{
	UCsLibrary_Enum::GetAllEnum<EMCsAIState, FECsAIState>(OutTypes);
}

#pragma endregion State

	// Setup
#pragma region

FECsAISetup UCsLibrary_AI_Enum::GetECsAISetup(const FString& Name)
{
	return UCsLibrary_Enum::GetEnum<EMCsAISetup, FECsAISetup>(NCsLibraryAIEnumCached::Str::GetECsAISetup, NCsLibraryAIEnumCached::Str::FECsAISetup, Name);
}

FECsAISetup UCsLibrary_AI_Enum::GetECsAISetupByIndex(const int32& Index)
{
	return UCsLibrary_Enum::GetEnumByIndex<EMCsAISetup, FECsAISetup>(NCsLibraryAIEnumCached::Str::GetECsAISetupByIndex, NCsLibraryAIEnumCached::Str::FECsAISetup, Index);
}

FString UCsLibrary_AI_Enum::ECsAISetupToString(const FECsAISetup& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_AI_Enum::GetECsAISetupCount()
{
	return EMCsAISetup::Get().Num();
}

void UCsLibrary_AI_Enum::GetAllECsAISetup(TArray<FECsAISetup>& OutTypes)
{
	UCsLibrary_Enum::GetAllEnum<EMCsAISetup, FECsAISetup>(OutTypes);
}

#pragma endregion Setup

#pragma endregion AI