// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

struct FCsWpDataRootSet;

/**
* Utility class to help populate a EnumStructMap. Called internally by the 
* namespace associated with the appropriate EnumStruct.
*/
struct CSWP_API FCsWpPopulateEnumMapFromSettings final
{
public:

	static const FCsWpDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot);
};