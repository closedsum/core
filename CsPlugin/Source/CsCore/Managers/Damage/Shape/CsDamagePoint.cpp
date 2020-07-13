// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Shape/CsDamagePoint.h"

const FName FCsDamagePoint::Name = FName("FCsDamagePoint");

FCsDamagePoint::FCsDamagePoint() :
	InterfaceMap(),
	Damage(0.0f)
{
	InterfaceMap.SetRootName(FCsDamagePoint::Name);

	InterfaceMap.Add<ICsDamageShape>(static_cast<ICsDamageShape*>(this));
}