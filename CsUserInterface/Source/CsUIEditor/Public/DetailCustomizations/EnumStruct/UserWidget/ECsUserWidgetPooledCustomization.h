// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "DetailCustomizations/EnumStruct/ECsEnumStructCustomization.h"

/**
* Customizes a FECsUserWidgetPooled property to use a dropdown
*/
class CSUIEDITOR_API FECsUserWidgetPooledCustomization : public FECsEnumStructCustomization
{
private:
	typedef FECsEnumStructCustomization Super;

public:

	FECsUserWidgetPooledCustomization();

protected:

	virtual void CustomPopulateEnumMap() override;

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle) override;
	virtual void SetEnumWithDisplayName(const FString& DisplayName) override;
	virtual void GetDisplayNamePropertyValue(FString& OutDisplayName) const override;
};