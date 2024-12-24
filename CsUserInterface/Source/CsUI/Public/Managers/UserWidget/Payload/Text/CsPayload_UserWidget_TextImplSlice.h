// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Managers/UserWidget/Payload/Text/CsPayload_UserWidget_Text.h"
#include "Reset/CsReset.h"

class UObject;
struct FCsInterfaceMap;

namespace NCsUserWidget
{
	namespace NPayload
	{
		namespace NText
		{
			namespace NImpl
			{
				namespace NSlice
				{
					using PayloadType = NCsUserWidget::NPayload::NText::IText;

					struct CSUI_API FSlice final : public PayloadType,
												   public ICsReset
					{
					public:

						static const FName Name;

					private:
			
						using OutlineSettingsType = NCsUserWidget::NText::FOutline;
						using ShadowSettingsType = NCsUserWidget::NText::FShadow;

					// ICsGetInterfaceMap

						FCsInterfaceMap* InterfaceMap;

					public:

					// PayloadType (NCsUserWidget::NPayload::NText::IText)

						FText Text;

						/** Get the color of the text. */
						FLinearColor Color;

						/** Get any information describing the Outline Settings for the text. */
						OutlineSettingsType OutlineSettings;

						/** Get any information describing the Shadow Settings for the text. */
						ShadowSettingsType ShadowSettings;

					public:

						FSlice();

					public:

						void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

					// ICsGetInterfaceMap
					#pragma region
					public:

						FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

					#pragma endregion ICsGetInterfaceMap

					// PayloadType (NCsUserWidget::NPayload::NText::IText)
					#pragma region
					public:

						FORCEINLINE const FText& GetText() const { return Text; }
						FORCEINLINE const FLinearColor& GetColor() const { return Color; }
						FORCEINLINE const OutlineSettingsType& GetOutlineSettings() const { return OutlineSettings; }
						FORCEINLINE const ShadowSettingsType& GetShadowSettings() const { return ShadowSettings; }

					#pragma endregion PayloadType (NCsUserWidget::NPayload::NText::IText)

					// ICsReset
					#pragma region
					public:

						void Reset();

					#pragma endregion ICsReset

					public:

						FORCEINLINE OutlineSettingsType* GetOutlineSettingsPtr() { return &OutlineSettings; }
						FORCEINLINE ShadowSettingsType* GetShadowSettingsPtr() { return &ShadowSettings; }

						FORCEINLINE static void Deconstruct(void* Ptr)
						{
							delete static_cast<NCsUserWidget::NPayload::NText::NImpl::NSlice::FSlice*>(Ptr);
						}
					};
				}
			}
		}
	}
}