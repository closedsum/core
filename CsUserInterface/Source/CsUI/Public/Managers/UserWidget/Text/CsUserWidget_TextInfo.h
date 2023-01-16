// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Font.h"
#include "Material/CsTypes_Material.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Managers/UserWidget/Text/CsTypes_UserWidget_Text.h"
#include "Types/CsTypes_UserWidget_Anim.h"
// Log
#include "Utility/CsUILog.h"

#include "CsUserWidget_TextInfo.generated.h"

// NCsUserWidget::NText::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NText, FInfo)

/**
* Container holding general information for a UserWidget Text object.
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

	/** The scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float RenderScale;

	/** Way to interpret Position information for being converted to screen space. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	ECsUserWidgetPosition PositionType;

	/** Way to interpret Offset information for being converted to screen space. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	ECsUserWidgetPosition OffsetType;

	/** The offset to apply to the position of the UserWidget. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	FVector Offset;

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
		RenderScale(1.0f),
		PositionType(ECsUserWidgetPosition::Screen),
		OffsetType(ECsUserWidgetPosition::Screen),
		Offset(FVector::ZeroVector),
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
		* Container holding general information for a UserWidget Text pooled object.
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
			/** The scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)). */
			CS_DECLARE_MEMBER_WITH_PROXY(RenderScale, float)
			/** Way to interpret Position information for beionverted to screen space. */
			CS_DECLARE_MEMBER_WITH_PROXY(PositionType, NCsUserWidget::EPosition)
			/** Way to interpret Offset information for being converted to screen space. */
			CS_DECLARE_MEMBER_WITH_PROXY(OffsetType, NCsUserWidget::EPosition)
			/** The offset to apply to the position of the UserWidget. */
			CS_DECLARE_MEMBER_WITH_PROXY(Offset, FVector)
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
				CS_CTOR_INIT_MEMBER_WITH_PROXY(RenderScale, 1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(PositionType, NCsUserWidget::EPosition::Screen),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(OffsetType, NCsUserWidget::EPosition::Screen),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Offset, FVector::ZeroVector),
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
				CS_CTOR_SET_MEMBER_PROXY(RenderScale);
				CS_CTOR_SET_MEMBER_PROXY(PositionType);
				CS_CTOR_SET_MEMBER_PROXY(OffsetType);
				CS_CTOR_SET_MEMBER_PROXY(Offset);
				CS_CTOR_SET_MEMBER_PROXY(ZOrder);
				CS_CTOR_SET_MEMBER_PROXY(Color);
				CS_CTOR_SET_MEMBER_PROXY(bAnimParams);
				CS_CTOR_SET_MEMBER_PROXY(AnimParams);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Text, FString)
			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Font, UFont)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bMaterial, bool)
			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Material, UMaterialInterface)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(RenderScale, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PositionType, NCsUserWidget::EPosition)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(OffsetType, NCsUserWidget::EPosition)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FVector)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ZOrder, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Color, FLinearColor)
			FORCEINLINE const OutlineSettingsType& GetOutlineSettings() const { return OutlineSettings; }
			FORCEINLINE OutlineSettingsType* GetOutlineSettingsPtr() { return &OutlineSettings; }
			FORCEINLINE const ShadowSettingsType& GetShadowSettings() const { return ShadowSettings; }
			FORCEINLINE ShadowSettingsType* GetShadowSettingsPtr() { return &ShadowSettings; }
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bAnimParams, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AnimParams, AnimParamsType)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

		#undef DeallocateMethodType
		#undef OutlineSettingsType
		#undef ShadowSettingsType
		#undef AnimParamsType
		};
	}
}