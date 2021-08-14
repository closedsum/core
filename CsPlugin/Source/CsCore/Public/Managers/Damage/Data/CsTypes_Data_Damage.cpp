// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsTypes_Data_Damage.h"

#include "Managers/Damage/Data/Point/CsData_DamagePointProxy.h"

// FCsData_DamagePoint
#pragma region

void FCsData_DamagePoint::SetData(PointDataProxyType* Data)
{
	Data->SetValue(&Damage);
	Data->SetType(&Type);
}

#pragma endregion FCsData_DamagePoint