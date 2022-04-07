// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Managers/UserWidget/Text/CsTypes_UserWidget_Text.h"
// Log
#include "Utility/CsUILog.h"

#include "CsUserWidget_TextPooledInfo.generated.h"

// NCsUserWidget::NText::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NText, FInfo)

// NCsUserWidget::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NPayload, IPayload)

/**
* Container holding general information for a UserWidget Text pooled object.
*  UserWidget is an object that implements the interface: ICsUserWidgetPooled.
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidget_TextPooledInfo
{
	GENERATED_USTRUCT_BODY()

public:

	/** The UserWidgetPooled Type. This is used to group UserWidget Text objects into different categories 
	    and can be used by a Manager pooling UserWidget Text objects to Spawn the correct
		UUserWidget. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	FECsUserWidgetPooled Type;

	/** Condition to determine when to deallocate the UserWidget. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	ECsUserWidgetDeallocateMethod DeallocateMethod;

	/** The scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float RenderScale;

	/** Valid if the DeallocateMethod == ECsUserWidgetDeallocateMethod::LifeTime.
		 LifeTime == 0.0f means the UserWidget object will stay active forever.
		 LifeTime > 0.0f means the UserWidget will be deallocated after LifeTime amount of time after
	      the UserWidget object has been allocated. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	/** Get the color of the text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	FLinearColor Color;

	/** Get any information describing the Outline Settings for the text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	FCsUserWidget_Text_OutlineSettings OutlineSettings;

	/** Get any information describing the Shadow Settings for the text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	FCsUserWidget_Text_ShadowSettings ShadowSettings;

public:

	FCsUserWidget_TextPooledInfo() :
		Type(),
		DeallocateMethod(ECsUserWidgetDeallocateMethod::Complete),
		RenderScale(1.0f),
		LifeTime(0.0f),
		Color(FLinearColor::White),
		OutlineSettings(),
		ShadowSettings()
	{
	}

#define InfoType NCsUserWidget::NText::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

#define PayloadType NCsUserWidget::NPayload::IPayload
	void SetPayloadChecked(const FString& Context, PayloadType* Payload) const;
	bool SetSafePayload(const FString& Context, PayloadType* Payload, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
#undef PayloadType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

namespace NCsUserWidget
{
	namespace NText
	{
		/**
		* Container holding general information for a UserWidget Text pooled object.
		*  UserWidget is an object that implements the interface: ICsUserWidgetPooled.
		*/
		struct CSUI_API FInfo final
		{
		#define DeallocateMethodType NCsUserWidget::EDeallocateMethod
		#define OutlineSettingsType NCsUserWidget::NText::FOutline
		#define ShadowSettingsType NCsUserWidget::NText::FShadow

		private:

			/** The UserWidgetPooled Type. This is used to group UserWidget Text objects into different categories
				and can be used by a Manager pooling UserWidget Text objects to Spawn the correct
				UUserWidget. */
			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsUserWidgetPooled)

			/** Condition to determine when to deallocate the UserWidget. */
			CS_DECLARE_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType)

			/** The scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)). */
			CS_DECLARE_MEMBER_WITH_PROXY(RenderScale, float)

			/** Valid if the DeallocateMethod == DeallocateMethodType::LifeTime.
				 LifeTime == 0.0f means the UserWidget object will stay active forever.
				 LifeTime > 0.0f means the UserWidget will be deallocated after LifeTime amount of time after
				  the UserWidget object has been allocated. */
			CS_DECLARE_MEMBER_WITH_PROXY(LifeTime, float)

			/** Get the color of the text. */
			CS_DECLARE_MEMBER_WITH_PROXY(Color, FLinearColor)

			/** Get any information describing the Outline Settings for the text. */
			CS_DECLARE_MEMBER_WITH_PROXY(OutlineSettings, OutlineSettingsType)

			/** Get any information describing the Shadow Settings for the text. */
			CS_DECLARE_MEMBER_WITH_PROXY(ShadowSettings, ShadowSettingsType)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType::LifeTime),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(RenderScale, 1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(LifeTime, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Color, FLinearColor::White),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(OutlineSettings),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(ShadowSettings)
			{
				CS_CTOR_SET_MEMBER_PROXY(Type);
				CS_CTOR_SET_MEMBER_PROXY(DeallocateMethod);
				CS_CTOR_SET_MEMBER_PROXY(RenderScale);
				CS_CTOR_SET_MEMBER_PROXY(LifeTime);
				CS_CTOR_SET_MEMBER_PROXY(Color);
				CS_CTOR_SET_MEMBER_PROXY(OutlineSettings);
				CS_CTOR_SET_MEMBER_PROXY(ShadowSettings);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsUserWidgetPooled)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(RenderScale, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LifeTime, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Color, FLinearColor)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(OutlineSettings, OutlineSettingsType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ShadowSettings, ShadowSettingsType)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

		#undef DeallocateMethodType
		#undef OutlineSettingsType
		#undef ShadowSettingsType
		};
	}
}