// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "EdGraphUtilities.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_K2.h"

class SGraphPin;
class UEdGraphPin;
class UEdGraphSchema_K2;

class CSPRJEDITOR_API FCsProjectilePanelGraphPinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* InPin) const override;

	template<typename T>
	bool DoesPinUseScriptStruct(UEdGraphPin* InPin, const UEdGraphSchema_K2* K2Schema) const
	{
		return InPin->PinType.PinCategory == K2Schema->PC_Struct && InPin->PinType.PinSubCategoryObject == T::StaticStruct();
	}
};