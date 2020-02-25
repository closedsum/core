// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Enum.h"
#include "CsCore.h"

// Cache
#pragma region

namespace NCsLibraryEnumCached
{
	namespace Str
	{
		// Process
		const FString FECsProcess = TEXT("FECsProcess");
		const FString ECsProcess_Get = TEXT("ECsProcess_Get");
		const FString ECsProcess_GetByIndex = TEXT("ECsProcess_GetByIndex");
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

UCsLibrary_Enum::UCsLibrary_Enum(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Process
#pragma region

FECsProcess UCsLibrary_Enum::ECsProcess_Get(const FString& Name)
{
	return GetEnum<EMCsProcess, FECsProcess>(NCsLibraryEnumCached::Str::ECsProcess_Get, NCsLibraryEnumCached::Str::FECsProcess, Name);
}

FECsProcess UCsLibrary_Enum::ECsProcess_GetByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsProcess, FECsProcess>(NCsLibraryEnumCached::Str::ECsProcess_GetByIndex, NCsLibraryEnumCached::Str::FECsProcess, Index);
}

FString UCsLibrary_Enum::ECsProcess_ToString(const FECsProcess& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::ECsProcess_GetCount()
{
	return EMCsProcess::Get().Num();
}

void UCsLibrary_Enum::ECsProcess_GetAll(TArray<FECsProcess>& OutTypes)
{
	GetAllEnum<EMCsProcess, FECsProcess>(OutTypes);
}

#pragma endregion Process

// AI
#pragma region

	// Type
#pragma region

FECsAIType UCsLibrary_Enum::GetECsAIType(const FString& Name)
{
	return GetEnum<EMCsAIType, FECsAIType>(NCsLibraryEnumCached::Str::GetECsAIType, NCsLibraryEnumCached::Str::FECsAIType, Name);
}

FECsAIType UCsLibrary_Enum::GetECsAITypeByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsAIType, FECsAIType>(NCsLibraryEnumCached::Str::GetECsAITypeByIndex, NCsLibraryEnumCached::Str::FECsAIType, Index);
}

FString UCsLibrary_Enum::ECsAITypeToString(const FECsAIType& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsAITypeCount()
{
	return EMCsAIType::Get().Num();
}

void UCsLibrary_Enum::GetAllECsAIType(TArray<FECsAIType>& OutTypes)
{
	GetAllEnum<EMCsAIType, FECsAIType>(OutTypes);
}

#pragma endregion Type

	// State
#pragma region

FECsAIState UCsLibrary_Enum::GetECsAIState(const FString& Name)
{
	return GetEnum<EMCsAIState, FECsAIState>(NCsLibraryEnumCached::Str::GetECsAIState, NCsLibraryEnumCached::Str::FECsAIState, Name);
}

FECsAIState UCsLibrary_Enum::GetECsAIStateByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsAIState, FECsAIState>(NCsLibraryEnumCached::Str::GetECsAIStateByIndex, NCsLibraryEnumCached::Str::FECsAIState, Index);
}

FString UCsLibrary_Enum::ECsAIStateToString(const FECsAIState& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsAIStateCount()
{
	return EMCsAIState::Get().Num();
}

void UCsLibrary_Enum::GetAllECsAIState(TArray<FECsAIState>& OutTypes)
{
	GetAllEnum<EMCsAIState, FECsAIState>(OutTypes);
}

#pragma endregion State

	// Setup
#pragma region

FECsAISetup UCsLibrary_Enum::GetECsAISetup(const FString& Name)
{
	return GetEnum<EMCsAISetup, FECsAISetup>(NCsLibraryEnumCached::Str::GetECsAISetup, NCsLibraryEnumCached::Str::FECsAISetup, Name);
}

FECsAISetup UCsLibrary_Enum::GetECsAISetupByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsAISetup, FECsAISetup>(NCsLibraryEnumCached::Str::GetECsAISetupByIndex, NCsLibraryEnumCached::Str::FECsAISetup, Index);
}

FString UCsLibrary_Enum::ECsAISetupToString(const FECsAISetup& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsAISetupCount()
{
	return EMCsAISetup::Get().Num();
}

void UCsLibrary_Enum::GetAllECsAISetup(TArray<FECsAISetup>& OutTypes)
{
	GetAllEnum<EMCsAISetup, FECsAISetup>(OutTypes);
}

#pragma endregion Setup

#pragma endregion AI