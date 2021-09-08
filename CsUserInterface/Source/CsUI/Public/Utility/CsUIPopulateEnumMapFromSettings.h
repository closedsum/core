// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

struct FCsUIDataRootSet;

/**
* Utility class to help populate a EnumStructMap. Called internally by the 
* namespace associated with the appropriate EnumStruct.
*/
struct CSUI_API FCsUIPopulateEnumMapFromSettings final
{
public:

	static const FCsUIDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot);
};