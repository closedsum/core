// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

struct FCsBeamDataRootSet;

/**
* Utility class to help populate a EnumStructMap. Called internally by the 
* namespace associated with the appropriate EnumStruct.
*/
struct CSBEAM_API FCsBeamPopulateEnumMapFromSettings final
{
public:

	static const FCsBeamDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot);
};