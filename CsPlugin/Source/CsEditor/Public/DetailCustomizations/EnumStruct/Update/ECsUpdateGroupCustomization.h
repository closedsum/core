// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "DetailCustomizations/EnumStruct/ECsEnumStructCustomization.h"

/**
* Customizes a FECsUpdateGroup property to use a dropdown
*/
class CSEDITOR_API FECsUpdateGroupCustomization : public FECsEnumStructCustomization
{
private:
	typedef FECsEnumStructCustomization Super;

public:

	FECsUpdateGroupCustomization();

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void CustomPopulateEnumMap() override;

	virtual void AddEnumToMap(const FString& Name) override;

	virtual const FString& GetEnumStructName() override;
	virtual const FName& GetEnumStructFName() override;

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle) override;
	virtual void SetEnumWithDisplayName(const FString& DisplayName) override;
	virtual void GetDisplayNamePropertyValue(FString& OutDisplayName) const override;
};
