// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Text/CsUserWidget_TextImpl.h"

// UI
#include "Engine/Font.h"
// Component
#include "Components/TextBlock.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsUserWidget_TextImpl)

UCsUserWidget_TextImpl::UCsUserWidget_TextImpl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	MyText(nullptr)
{
}

using InfoType = NCsUserWidget::NText::FInfo;

void UCsUserWidget_TextImpl::SetInfo(const InfoType& Info)
{
	MyText->SetText(FText::FromString(Info.GetText()));
	
	FSlateFontInfo FontInfo;
	FontInfo.FontObject = Info.GetFont();
	FontInfo.Size		= Info.GetSize();

	if (Info.GetbMaterial())
	{
		FontInfo.FontMaterial = Info.GetMaterial();
	}

	SetRenderScale(Info.GetRenderScale() * FVector2D(1.0f));
	MyText->SetColorAndOpacity(FSlateColor(Info.GetColor()));

	// Outline
	typedef NCsUserWidget::NText::FOutline OutlineSettingsType;

	const OutlineSettingsType& OutlineSettings = Info.GetOutlineSettings();

	FontInfo.OutlineSettings.OutlineSize				= OutlineSettings.GetSize();
	FontInfo.OutlineSettings.bApplyOutlineToDropShadows = OutlineSettings.GetbApplyOutlineToDropShadow();
	FontInfo.OutlineSettings.OutlineColor				= OutlineSettings.GetColor();

	MyText->SetFont(FontInfo);

	// Shadow
	typedef NCsUserWidget::NText::FShadow ShadowSettingsType;

	const ShadowSettingsType& ShadowSettings = Info.GetShadowSettings();

	MyText->SetShadowOffset(ShadowSettings.GetOffset());
	MyText->SetShadowColorAndOpacity(ShadowSettings.GetColor());
	MyText->SetJustification(Info.GetJustification());
}