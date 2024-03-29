// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GraphEditor/EnumStruct/SCsGraphPin_EnumStruct.h"

class CSWPEDITOR_API SCsGraphPin_ECsWeaponSlot : public SCsGraphPin_EnumStruct
{
public:
	SLATE_BEGIN_ARGS(SCsGraphPin_ECsWeaponSlot) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:

	virtual FString OnGetText() const override;

	virtual void GenerateComboBoxIndexes(TArray< TSharedPtr<int32> >& OutComboBoxIndexes) override;
	virtual void ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo) override;

	virtual FText OnGetFriendlyName(int32 EnumIndex) override;
	virtual FText OnGetTooltip(int32 EnumIndex) override;
};