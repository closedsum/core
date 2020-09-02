// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsTypes_Data_Damage.h"

#include "Managers/Damage/Data/CsData_DamagePointEmu.h"

// FCsScriptData_DamagePoint
#pragma region

void FCsScriptData_DamagePoint::SetData(FCsData_DamagePointEmu* Data)
{
	Data->SetValue(&Damage);
	Data->SetType(&Type);
}

#pragma endregion FCsScriptData_DamagePoint