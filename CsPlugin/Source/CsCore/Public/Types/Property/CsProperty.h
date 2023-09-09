// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

struct ICsProperty
{
	virtual ~ICsProperty(){}

	virtual void UpdateIsDirty() = 0;
	virtual void Clear() = 0;
	virtual void ResetValue() = 0;
	virtual void Reset() = 0;
	virtual bool HasChanged() = 0;
	virtual void Resolve() = 0;
};