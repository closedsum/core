// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GraphEditor/EnumStruct/SCsGraphPin_EnumStruct.h"

class SCsGraphPin_ECsMenuEvent : public SCsGraphPin_EnumStruct
{
public:
	SLATE_BEGIN_ARGS(SCsGraphPin_ECsMenuEvent) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:

	virtual void CustomPopulateEnumMap() override;

	virtual FString OnGetText() const override;

	virtual void GenerateComboBoxIndexes(TArray< TSharedPtr<int32> >& OutComboBoxIndexes) override;
	virtual void ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo) override;

	virtual FText OnGetFriendlyName(int32 EnumIndex) override;
	virtual FText OnGetTooltip(int32 EnumIndex) override;
};