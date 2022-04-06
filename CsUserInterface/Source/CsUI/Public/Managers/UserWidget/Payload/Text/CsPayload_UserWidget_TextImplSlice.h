// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
		#define PayloadType NCsUserWidget::NPayload::NText::IText

			struct CSUI_API FImplSlice : public PayloadType,
										 public ICsReset
			{
			public:

				static const FName Name;

			#define OutlineSettingsType NCsUserWidget::NText::FOutline
			#define ShadowSettingsType NCsUserWidget::NText::FShadow

			private:

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

				FImplSlice();

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

				FORCEINLINE static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsUserWidget::NPayload::NText::FImplSlice*>(Ptr);
				}

			#undef OutlineSettingsType
			#undef ShadowSettingsType
			};

		#undef PayloadType
		}
	}
}