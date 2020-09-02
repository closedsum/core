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