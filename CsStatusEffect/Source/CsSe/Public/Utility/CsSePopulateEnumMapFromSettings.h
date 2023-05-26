// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

struct FCsSeDataRootSet;

/**
* Utility class to help populate a EnumStructMap. Called internally by the 
* namespace associated with the appropriate EnumStruct.
*/
struct CSSE_API FCsSePopulateEnumMapFromSettings final
{
public:

	static const FCsSeDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot);
	static const FCsSeDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot, UObject*& DataRootSetImpl);
};