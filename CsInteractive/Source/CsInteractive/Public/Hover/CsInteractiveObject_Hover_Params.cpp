// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Hover/CsInteractiveObject_Hover_Params.h"

// FCsInteractiveObject_Hover_Params
#pragma region

#define ParamsType NCsInteractive::NObject::NHover::NParams::FImpl
void FCsInteractiveObject_Hover_Params::CopyToParams(ParamsType* Params) const
{
#undef ParamsType

	Params->Instigator = Instigator;
	Params->Object = Object;
	Params->HitResult = HitResult;
}

bool FCsInteractiveObject_Hover_Params::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsInteractiveObject_Hover_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsInteractive::FLog::Warning*/) const
{
	return true;
}

#pragma endregion FCsInteractiveObject_Hover_Params

// FCsInteractiveObject_UnHover_Params
#pragma region

#define ParamsType NCsInteractive::NObject::NUnHover::NParams::FImpl
void FCsInteractiveObject_UnHover_Params::CopyToParams(ParamsType* Params) const
{
#undef ParamsType

	Params->Instigator = Instigator;
	Params->Object = Object;
	Params->HitResult = HitResult;
}

bool FCsInteractiveObject_UnHover_Params::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsInteractiveObject_UnHover_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsInteractive::FLog::Warning*/) const
{
	return true;
}

#pragma endregion FCsInteractiveObject_UnHover_Params