// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/UserWidget/Cache/CsCache_UserWidget.h"
#include "Containers/CsLibrary_InterfaceMap.h"

/**
*/
struct CSUI_API FCsLibrary_Cache_UserWidget : public NCsInterfaceMap::TLibrary<NCsUserWidget::NCache::ICache>
{
};