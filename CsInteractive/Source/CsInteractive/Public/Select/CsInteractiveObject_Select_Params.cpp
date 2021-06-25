// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Select/CsInteractiveObject_Select_Params.h"

// FCsInteractiveObject_Select_Params
#pragma region

#define ParamsType NCsInteractive::NObject::NSelect::NParams::FImpl
void FCsInteractiveObject_Select_Params::CopyToParams(ParamsType* Params) const
{
#undef ParamsType

	Params->Instigator = Instigator;
	Params->Object = Object;
	Params->HitResult = HitResult;
}

bool FCsInteractiveObject_Select_Params::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsInteractiveObject_Select_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsInteractive::FLog::Warning*/) const
{
	return true;
}

#pragma endregion FCsInteractiveObject_Select_Params

// FCsInteractiveObject_Deselect_Params
#pragma region

#define ParamsType NCsInteractive::NObject::NDeselect::NParams::FImpl
void FCsInteractiveObject_Deselect_Params::CopyToParams(ParamsType* Params) const
{
#undef ParamsType

	Params->Instigator = Instigator;
	Params->Object = Object;
	Params->HitResult = HitResult;
}

bool FCsInteractiveObject_Deselect_Params::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsInteractiveObject_Deselect_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsInteractive::FLog::Warning*/) const
{
	return true;
}

#pragma endregion FCsInteractiveObject_Deselect_Params