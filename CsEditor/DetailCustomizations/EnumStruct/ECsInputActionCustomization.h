// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "DetailCustomizations/EnumStruct/ECsEnumCustomization.h"

/**
* Customizes a FECsInputAction property to use a dropdown
*/
class CSEDITOR_API FECsInputActionCustomization : public FECsEnumCustomization
{
private:
	typedef FECsEnumCustomization Super;

public:

	FECsInputActionCustomization();

protected:

	virtual void CustomPopulateEnumMap() override;

	virtual void AddEnumToMap(const FString& Name) override;
	virtual FString GetEnumStructName() override;
	
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle) override;
	virtual void SetEnumWithDisplayName(const FString& DisplayName) override;
};
