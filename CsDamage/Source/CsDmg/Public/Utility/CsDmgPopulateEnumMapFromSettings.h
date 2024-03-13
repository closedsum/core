// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/UnrealString.h"

class UObject;

struct FCsDmgDataRootSet;

/**
* Utility class to help populate a EnumStructMap. Called internally by the 
* namespace associated with the appropriate EnumStruct.
*/
struct CSDMG_API FCsDmgPopulateEnumMapFromSettings final
{
public:

	static const FCsDmgDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot);
};