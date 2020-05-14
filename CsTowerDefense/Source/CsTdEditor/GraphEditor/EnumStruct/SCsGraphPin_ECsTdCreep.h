// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GraphEditor/EnumStruct/SCsGraphPin_EnumStruct.h"

class SCsGraphPin_ECsTdCreep : public SCsGraphPin_EnumStruct
{
public:
	SLATE_BEGIN_ARGS(SCsGraphPin_ECsTdCreep) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:

	virtual FString OnGetText() const override;

	virtual void GenerateComboBoxIndexes(TArray< TSharedPtr<int32> >& OutComboBoxIndexes) override;
	virtual void ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo) override;

	virtual FText OnGetFriendlyName(int32 EnumIndex) override;
	virtual FText OnGetTooltip(int32 EnumIndex) override;
};