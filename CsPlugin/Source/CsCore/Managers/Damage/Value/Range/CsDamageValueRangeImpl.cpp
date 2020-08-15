// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
#include "CsCore.h"

const FName FCsDamageValueRangeImpl::Name = FName("FCsDamageValueRangeImpl");

FCsDamageValueRangeImpl::FCsDamageValueRangeImpl() :
	InterfaceMap(),
	// ICsDamageValueRange
	MinValue(0.0f),
	MaxValue(0.0f)
{
	InterfaceMap.SetRootName(FCsDamageValueRangeImpl::Name);

	InterfaceMap.Add<ICsDamageValue>(static_cast<ICsDamageValue*>(this));
	InterfaceMap.Add<ICsDamageValueRange>(static_cast<ICsDamageValueRange*>(this));
}

void FCsDamageValueRangeImpl::Reset()
{
	MinValue = 0.0f;
	MaxValue = 0.0f;
}