// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsInputAction.generated.h"

USTRUCT(BlueprintType)
struct CSINPUT_API FECsInputAction : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsInputAction)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsInputAction)

struct CSINPUT_API EMCsInputAction : public TCsEnumStructMap<FECsInputAction, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsInputAction, FECsInputAction, uint8)
};

namespace NCsInputAction
{
	typedef FECsInputAction Type;
	typedef EMCsInputAction EnumMapType;

	// Mouse
	extern CSINPUT_API const Type Default__MousePositionXY__;
	extern CSINPUT_API const Type Default__MouseLeftButton__;
	extern CSINPUT_API const Type Default__MouseRightButton__;
	// Touch
		// Action
	extern CSINPUT_API const Type Default__Touch_0__;
	extern CSINPUT_API const Type Default__Touch_1__;
	extern CSINPUT_API const Type Default__Touch_2__;
	extern CSINPUT_API const Type Default__Touch_3__;
	extern CSINPUT_API const Type Default__Touch_4__;
	extern CSINPUT_API const Type Default__Touch_5__;
	extern CSINPUT_API const Type Default__Touch_6__;
	extern CSINPUT_API const Type Default__Touch_7__;
	extern CSINPUT_API const Type Default__Touch_8__;
	extern CSINPUT_API const Type Default__Touch_9__;
		// Location
	extern CSINPUT_API const Type Default__TouchPositionXY_0__;
	extern CSINPUT_API const Type Default__TouchPositionXY_1__;
	extern CSINPUT_API const Type Default__TouchPositionXY_2__;
	extern CSINPUT_API const Type Default__TouchPositionXY_3__;
	extern CSINPUT_API const Type Default__TouchPositionXY_4__;
	extern CSINPUT_API const Type Default__TouchPositionXY_5__;
	extern CSINPUT_API const Type Default__TouchPositionXY_6__;
	extern CSINPUT_API const Type Default__TouchPositionXY_7__;
	extern CSINPUT_API const Type Default__TouchPositionXY_8__;
	extern CSINPUT_API const Type Default__TouchPositionXY_9__;

	CSINPUT_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

// FCsInputActionSet
#pragma region

USTRUCT(BlueprintType)
struct CSINPUT_API FCsInputActionSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsInput|Input|Action")
	TSet<FECsInputAction> Actions;

	FCsInputActionSet() :
		Actions()
	{
	}

	void ConditionalRebuild()
	{
		TArray<FECsInputAction> ToRemove;
		TArray<FECsInputAction> ToAdd;

		for (const FECsInputAction& Action : Actions)
		{
			const FECsInputAction& ByName = EMCsInputAction::Get().GetEnum(Action.GetFName());
			const FECsInputAction& ByValue = EMCsInputAction::Get().GetEnum(Action.GetValue());

			if (ByValue != Action)
			{
				ToRemove.Add(Action);
				ToAdd.Add(ByName);
			}
		}

		for (const FECsInputAction& Action : ToRemove)
		{
			Actions.Remove(Action);
		}

		for (const FECsInputAction& Action : ToAdd)
		{
			Actions.Add(Action);
		}
	}
};

#pragma endregion FCsInputActionSet