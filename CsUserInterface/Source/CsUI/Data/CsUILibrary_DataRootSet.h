// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsUIDataRootSet.h"

#pragma once

class UObject;

/**
*/
class CSUI_API FCsUILibrary_DataRootSet
{
public:

	static const FCsUIDataRootSet& GetChecked(const FString& Context, UObject* ContextRoot);
};