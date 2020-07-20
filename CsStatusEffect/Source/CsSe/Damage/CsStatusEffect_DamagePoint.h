// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "CsStatusEffect_DamagePoint.generated.h"

struct FCsInterfaceMap;

UCLASS(BlueprintType, Blueprintable)
class CSSE_API UCsStatusEffect_DamagePoint : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	static const FName Name;

// UObject Interface
#pragma region
public:

	virtual void PostLoad() override;

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

private:

	FCsInterfaceMap* InterfaceMap;

// ICsGetInterfaceMap
#pragma region
public:

	FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

protected:

	bool bLoaded;
};