// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsTypes_Data_Damage.h"

#include "Managers/Damage/Data/CsData_DamagePointEmu.h"

// FCsData_DamagePoint
#pragma region

void FCsData_DamagePoint::SetData(PointDataEmuType* Data)
{
	Data->SetValue(&Damage);
	Data->SetType(&Type);
}

#pragma endregion FCsData_DamagePoint