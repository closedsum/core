// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Containers/CsInterfaceMap.h"

FCsInterfaceMap::FCsInterfaceMap() :
	Root(nullptr),
	RootName(NAME_None),
	Interfaces(),
	bUniqueBasedSlices(false),
	InterfacesByUniqueBasedSliceRootName()
{
}

FCsInterfaceMap::~FCsInterfaceMap()
{
}