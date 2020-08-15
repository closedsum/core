// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsDamageRangeImpl.h"
#include "CsCore.h"

const FName FCsDamageRangeImpl::Name = FName("FCsDamageRangeImpl");

FCsDamageRangeImpl::FCsDamageRangeImpl() :
	InterfaceMap(),
	// ICsDamageValueRange
	MinRange(0.0f),
	MaxRange(0.0f)
{
	InterfaceMap.SetRootName(FCsDamageRangeImpl::Name);

	InterfaceMap.Add<ICsDamageRange>(static_cast<ICsDamageRange*>(this));
}

void FCsDamageRangeImpl::Reset()
{
	MinRange = 0.0f;
	MaxRange = 0.0f;
}