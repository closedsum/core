// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
			const FString ECsUpdateGroup_Get = TEXT("ECsUpdateGroup_Get");
			const FString ECsUpdateGroup_GetByIndex = TEXT("ECsUpdateGroup_GetByIndex");
		}
	}
}

#pragma endregion Cache

UCsScriptLibrary_UpdateGroup::UCsScriptLibrary_UpdateGroup(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


FECsUpdateGroup UCsScriptLibrary_UpdateGroup::ECsUpdateGroup_Get(const FString& Name)
{
	using namespace NCsScriptLibraryUpdateGroup::NCached;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::Get<EMCsUpdateGroup, FECsUpdateGroup>(Str::ECsUpdateGroup_Get, Str::FECsUpdateGroup, Name);
}

FECsUpdateGroup UCsScriptLibrary_UpdateGroup::ECsUpdateGroup_GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryUpdateGroup::NCached;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetByIndex<EMCsUpdateGroup, FECsUpdateGroup>(Str::ECsUpdateGroup_GetByIndex, Str::FECsUpdateGroup, Index);
}

FString UCsScriptLibrary_UpdateGroup::ECsUpdateGroup_ToString(const FECsUpdateGroup& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_UpdateGroup::ECsUpdateGroup_GetCount()
{
	return EMCsUpdateGroup::Get().Num();
}

void UCsScriptLibrary_UpdateGroup::ECsUpdateGroup_GetAll(TArray<FECsUpdateGroup>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EMCsUpdateGroup, FECsUpdateGroup>(OutTypes);
}
