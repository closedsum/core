// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Image/CsUserWidget_ImageImpl.h"
#include "CsUI.h"

// Component
#include "Components/Image.h"

UCsUserWidget_ImageImpl::UCsUserWidget_ImageImpl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	MyImage(nullptr)
{
}

#define InfoType NCsUserWidget::NImage::FInfo
void UCsUserWidget_ImageImpl::SetInfo(const InfoType& Info)
{
#undef InfoType

	MyImage->SetBrushFromTexture(Info.GetImage());
}