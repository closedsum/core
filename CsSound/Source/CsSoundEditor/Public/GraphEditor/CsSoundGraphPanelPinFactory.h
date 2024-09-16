// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "EdGraphUtilities.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_K2.h"

class CSSOUNDEDITOR_API FCsSoundPanelGraphPinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;

	template<typename T>
	bool DoesPinUseScriptStruct(class UEdGraphPin* InPin, const UEdGraphSchema_K2* K2Schema) const
	{
		return InPin->PinType.PinCategory == K2Schema->PC_Struct && InPin->PinType.PinSubCategoryObject == T::StaticStruct();
	}
};