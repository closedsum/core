// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsSettings_Data.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Data)

// FCsSettings_Data_EnumStruct
#pragma region

/*static*/ const FCsSettings_Data_EnumStruct& FCsSettings_Data_EnumStruct::Get()
{
	return FCsSettings_Data::Get().EnumStructSettings;
}

#pragma endregion FCsSettings_Data_EnumStruct

// FCsSettings_Data
#pragma region

/*static*/ const FCsSettings_Data& FCsSettings_Data::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>()->Data;
}

#pragma endregion FCsSettings_Data