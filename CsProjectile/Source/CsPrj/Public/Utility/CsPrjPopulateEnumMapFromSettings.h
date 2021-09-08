// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

struct FCsPrjDataRootSet;

/**
* Utility class to help populate a EnumStructMap. Called internally by the 
* namespace associated with the appropriate EnumStruct.
*/
struct CSPRJ_API FCsPrjPopulateEnumMapFromSettings final
{
public:

	static const FCsPrjDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot);
};