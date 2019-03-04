// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "DetailCustomizations/EnumStruct/ECsEnumStructCustomization.h"

/**
* Customizes a FECsItemType property to use a dropdown
*/
class CSEDITOR_API FECsItemTypeCustomization : public FECsEnumStructCustomization
{
private:
	typedef FECsEnumStructCustomization Super;

public:

	FECsItemTypeCustomization();

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle) override;
	virtual void SetEnumWithDisplayName(const FString& DisplayName) override;
};