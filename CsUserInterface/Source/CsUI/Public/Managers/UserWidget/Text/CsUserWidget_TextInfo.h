// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Font.h"
#include "Material/CsTypes_Material.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Managers/UserWidget/Text/CsTypes_UserWidget_Text.h"
#include "Types/CsTypes_UserWidget_Anim.h"
// Text
#include "Framework/Text/TextLayout.h"
// Log
#include "Utility/CsUILog.h"

#include "CsUserWidget_TextInfo.generated.h"

// NCsUserWidget::NText::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NText, FInfo)

/**
* Describes any information for a UserWidget Text object.
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidget_TextInfo
{
	GENERATED_USTRUCT_BODY()

public:

	/** The text to display. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget|Text")
	FString Text;

	/** The font object (valid when used from UMG and Slate widget style asset). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget|Text")
	FCsFont Font;

	/** Whether to use specific material for rendering Font or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget|Text", meta = (ScriptName = "m_bMaterial", InlineEditConditionToggle))
	bool bMaterial;

	/** The material use when rendering Font. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget|Text", meta = (ScriptName = "m_Material", EditCondition = "bMaterial"))
	FCsMaterialInterface Material;

	/** The font size is a measure in point values.  The conversion of points to Slate Units is done at 96 dpi.  So if
		you're using a tool like Photoshop to prototype layouts and UI mock ups, be sure to change the default dpi
		measurements from 72 dpi to 96 dpi. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text", meta = (ClampMin = "1", UIMin = "1", ClampMax = "1000", UIMax = "1000"))
	int32 Size;

	/** The scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float RenderScale;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	TEnumAsByte<ETextJustify::Type> Justification;

	/** The order priority this widget is rendered in.  Higher values are rendered last (and so they will appear to be on top). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	int32 ZOrder;

	/** The color of the text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	FLinearColor Color;

	/** Any information describing the Outline Settings for the text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	FCsUserWidget_Text_OutlineSettings OutlineSettings;

	/** Any information describing the Shadow Settings for the text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	FCsUserWidget_Text_ShadowSettings ShadowSettings;

	/** Whether to use AnimParams or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text", meta = (ScriptName = "m_bAnimParams", InlineEditConditionToggle))
	bool bAnimParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text", meta = (ScriptName = "m_AnimParams", EditCondition = "bAnimParams"))
	FCsUserWidget_Anim_PlayParams AnimParams;

public:

	FCsUserWidget_TextInfo() :
		Text(),
		Font(),
		bMaterial(false),
		Material(),
		Size(1),
		RenderScale(1.0f),
		Justification(ETextJustify::Type::Center),
		ZOrder(0),
		Color(FLinearColor::White),
		OutlineSettings(),
		ShadowSettings(),
		bAnimParams(false),
		AnimParams()
	{
	}

#define InfoType NCsUserWidget::NText::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

class UObject;

namespace NCsUserWidget
{
	namespace NText
	{
		/**
		* Describes any information for a UserWidget Text object.
		*/
		struct CSUI_API FInfo final
		{
		#define DeallocateMethodType NCsUserWidget::EDeallocateMethod
		#define OutlineSettingsType NCsUserWidget::NText::FOutline
		#define ShadowSettingsType NCsUserWidget::NText::FShadow
		#define AnimParamsType NCsUserWidget::NAnim::NPlay::FParams

		private:

			/** The text to display. */
			CS_DECLARE_MEMBER_WITH_PROXY(Text, FString)
			/** The font object (valid when used from UMG and Slate widget style asset). */
			CS_DECLARE_MEMBER_WITH_PROXY(Font, UFont*)
			/** Whether to use specific material for rendering Font or not. */
			CS_DECLARE_MEMBER_WITH_PROXY(bMaterial, bool)
			/** The material use when rendering Font. */
			CS_DECLARE_MEMBER_WITH_PROXY(Material, UMaterialInterface*)
			/** The font size is a measure in point values.  The conversion of points to Slate Units is done at 96 dpi.  So if
				you're using a tool like Photoshop to prototype layouts and UI mock ups, be sure to change the default dpi
				measurements from 72 dpi to 96 dpi. */
			CS_DECLARE_MEMBER_WITH_PROXY(Size, int32)
			/** The scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)). */
			CS_DECLARE_MEMBER_WITH_PROXY(RenderScale, float)
			CS_DECLARE_MEMBER_WITH_PROXY(Justification, ETextJustify::Type)
			/** The order priority this widget is rendered in.  Higher values are rendered last (and so they will appear to be on top). */
			CS_DECLARE_MEMBER_WITH_PROXY(ZOrder, int32)
			/** Get the color of the text. */
			CS_DECLARE_MEMBER_WITH_PROXY(Color, FLinearColor)
			/** Get any information describing the Outline Settings for the text. */
			OutlineSettingsType OutlineSettings;
			/** Get any information describing the Shadow Settings for the text. */
			ShadowSettingsType ShadowSettings;
			/** Whether to use AnimParams or not. */
			CS_DECLARE_MEMBER_WITH_PROXY(bAnimParams, bool)
			CS_DECLARE_MEMBER_WITH_PROXY(AnimParams, AnimParamsType)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Text),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Font, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bMaterial, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Material, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Size, 1),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(RenderScale, 1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Justification, ETextJustify::Type::Center),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(ZOrder, 0),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Color, FLinearColor::White),
				OutlineSettings(),
				ShadowSettings(),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bAnimParams, false),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(AnimParams)
			{
				CS_CTOR_SET_MEMBER_PROXY(Text);
				CS_CTOR_SET_MEMBER_PROXY(Font);
				CS_CTOR_SET_MEMBER_PROXY(bMaterial);
				CS_CTOR_SET_MEMBER_PROXY(Material);
				CS_CTOR_SET_MEMBER_PROXY(Size);
				CS_CTOR_SET_MEMBER_PROXY(RenderScale);
				CS_CTOR_SET_MEMBER_PROXY(Justification);
				CS_CTOR_SET_MEMBER_PROXY(ZOrder);
				CS_CTOR_SET_MEMBER_PROXY(Color);
				CS_CTOR_SET_MEMBER_PROXY(bAnimParams);
				CS_CTOR_SET_MEMBER_PROXY(AnimParams);
			}

			FORCEINLINE FInfo(FInfo& B)
			{
				Copy(B);
			}

			FORCEINLINE FInfo(const FInfo& B)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Text, FString)
			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Font, UFont)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bMaterial, bool)
			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Material, UMaterialInterface)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Size, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(RenderScale, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Justification, ETextJustify::Type)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ZOrder, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Color, FLinearColor)
			FORCEINLINE const OutlineSettingsType& GetOutlineSettings() const { return OutlineSettings; }
			FORCEINLINE OutlineSettingsType* GetOutlineSettingsPtr() { return &OutlineSettings; }
			FORCEINLINE const ShadowSettingsType& GetShadowSettings() const { return ShadowSettings; }
			FORCEINLINE ShadowSettingsType* GetShadowSettingsPtr() { return &ShadowSettings; }
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bAnimParams, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AnimParams, AnimParamsType)

			FORCEINLINE void Copy(const FInfo& B)
			{
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Text);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Font);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bMaterial);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Material);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Size);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, RenderScale);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Justification);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, ZOrder);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Color);
				CS_COPY_CUSTOM_PROXY_TO_PROXY_PTR_AS_VALUE(B, OutlineSettings);
				CS_COPY_CUSTOM_PROXY_TO_PROXY_PTR_AS_VALUE(B, ShadowSettings);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bAnimParams);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, AnimParams);
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

		#undef DeallocateMethodType
		#undef OutlineSettingsType
		#undef ShadowSettingsType
		#undef AnimParamsType
		};
	}
}