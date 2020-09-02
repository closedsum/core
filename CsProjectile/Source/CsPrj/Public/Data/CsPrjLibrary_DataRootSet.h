// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsPrjDataRootSet.h"

#pragma once

class UObject;

/**
*/
class CSPRJ_API FCsPrjLibrary_DataRootSet
{
public:

	static const FCsPrjDataRootSet& GetChecked(const FString& Context, UObject* ContextRoot);
};