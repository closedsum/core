// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Data/CsData_UserWidget.h"
#include "CsUI.h"

const FName NCsUserWidget::NData::IData::Name = FName("NCsUserWidget::NData::IData");

const FName ICsData_UserWidget::Name = FName("ICsData_UserWidget");

UCsData_UserWidget::UCsData_UserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}