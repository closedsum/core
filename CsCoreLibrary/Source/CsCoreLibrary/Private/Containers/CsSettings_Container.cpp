// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
// Types
#include "Containers/CsSettings_Container.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsCoreLibrarySettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Container)

// FCsSettings_Container_UniformGrid_Debug
#pragma region

const FCsSettings_Container_UniformGrid_Debug& FCsSettings_Container_UniformGrid_Debug::Get()
{
	return FCsSettings_Container_UniformGrid::Get().Debug;
}

#pragma endregion FCsSettings_Container_UniformGrid_Debug

// FCsSettings_Container_UniformGrid
#pragma region

const FCsSettings_Container_UniformGrid& FCsSettings_Container_UniformGrid::Get()
{
	return FCsSettings_Container::Get().UniformGrid;
}

#pragma endregion FCsSettings_Container_UniformGrid

// FCsSettings_Container
#pragma region

const FCsSettings_Container& FCsSettings_Container::Get()
{
	return GetMutableDefault<UCsCoreLibrarySettings>()->Container;
}

#pragma endregion FCsSettings_Container