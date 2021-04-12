// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Script/CsTypes_ScriptLibrary_FX.h"
#include "CsCore.h"

// Types
#include "Managers/FX/CsTypes_Library_FX.h"

#define ParamsType NCsFX::NSpawn::NParams::FParams
void FCsScriptLibrary_FX_Spawn_Params::CopyParams(ParamsType* Params) const
{
#undef ParamsType

	Params->FX = FX;
	Params->FX.UpdateInternalPtrs();
	Params->Actor = Actor;
	Params->FrequencyParams = FrequencyParams;
	Params->Group = Group;
}

bool FCsScriptLibrary_FX_Spawn_Params::IsValid(const FString& Context) const
{
	// Check FX is Valid
	if (!FX.IsValid(Context))
		return false;
	// Check FrequencyParams is Valid
	if (!FrequencyParams.IsValid(Context))
		return false;
	// Check Group is Valid
	if (!EMCsUpdateGroup::Get().IsValidEnum(Group))
		return false;
	return true;
}

void FCsScriptLibrary_FX_Spawn_Params::Update()
{
	FrequencyParams.Update();
}