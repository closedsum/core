// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "CsCore.h"

const FName FCsDamageValuePointImpl::Name = FName("FCsDamageValuePointImpl");

FCsDamageValuePointImpl::FCsDamageValuePointImpl() :
	// ICsGetInterfaceMap
	InterfaceMap(),
	// ICsDamageValuePoint
	Value(0.0f)
{
	// ICsGetInterfaceMap
	InterfaceMap.SetRootName(FCsDamageValuePointImpl::Name);

	InterfaceMap.Add<ICsDamageValue>(static_cast<ICsDamageValue*>(this));
	InterfaceMap.Add<ICsDamageValuePoint>(static_cast<ICsDamageValuePoint*>(this));
}

void FCsDamageValuePointImpl::Reset()
{
	Value = 0.0f;
}