// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsAllocationOrder.h"

FCsAllocationOrder::FCsAllocationOrder() :
	Links(),
	Head(nullptr),
	Tail(nullptr),
	Size(0)
{
}

FCsAllocationOrder::~FCsAllocationOrder()
{
	Shutdown();
}