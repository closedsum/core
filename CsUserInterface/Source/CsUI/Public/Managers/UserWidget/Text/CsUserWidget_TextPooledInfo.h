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

	/** The offset to apply to the position of the UserWidget. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	FVector2D Offset;

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

public:

	FCsUserWidget_TextPooledInfo() :
		Type(),
		DeallocateMethod(ECsUserWidgetDeallocateMethod::Complete),
		RenderScale(1.0f),
		LifeTime(0.0f),
		Offset(FVector2D::ZeroVector),
		ZOrder(0),
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

class UObject;
struct FCsUserWidgetPooled;

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

			/** The offset to apply to the position of the UserWidget. */
			CS_DECLARE_MEMBER_WITH_PROXY(Offset, FVector2D)

			/** The order priority this widget is rendered in.  Higher values are rendered last (and so they will appear to be on top). */
			CS_DECLARE_MEMBER_WITH_PROXY(ZOrder, int32)

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
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Offset, FVector2D::ZeroVector),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(ZOrder, 0),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Color, FLinearColor::White),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(OutlineSettings),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(ShadowSettings)
			{
				CS_CTOR_SET_MEMBER_PROXY(Type);
				CS_CTOR_SET_MEMBER_PROXY(DeallocateMethod);
				CS_CTOR_SET_MEMBER_PROXY(RenderScale);
				CS_CTOR_SET_MEMBER_PROXY(LifeTime);
				CS_CTOR_SET_MEMBER_PROXY(Offset);
				CS_CTOR_SET_MEMBER_PROXY(ZOrder);
				CS_CTOR_SET_MEMBER_PROXY(Color);
				CS_CTOR_SET_MEMBER_PROXY(OutlineSettings);
				CS_CTOR_SET_MEMBER_PROXY(ShadowSettings);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsUserWidgetPooled)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(RenderScale, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LifeTime, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FVector2D)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ZOrder, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Color, FLinearColor)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(OutlineSettings, OutlineSettingsType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ShadowSettings, ShadowSettingsType)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

			/**
			* Spawn a UserWidget Text object with the appropriate text information from that Data. 
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Instigator
			* @param Owner
			* @param Value
			* @param Location		Location in World Space
			* return
			*/
			const FCsUserWidgetPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, UObject* Instigator, UObject* Owner, const float& Value, const FVector& Location) const;

		#undef DeallocateMethodType
		#undef OutlineSettingsType
		#undef ShadowSettingsType
		};
	}
}