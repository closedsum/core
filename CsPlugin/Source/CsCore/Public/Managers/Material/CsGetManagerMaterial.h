// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerMaterial.generated.h"

class UCsManager_Material;

UINTERFACE(Blueprintable)
class UCsGetManagerMaterial : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerMaterial
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Material* GetManager_Material() const = 0;

	virtual void SetManager_Material(UCsManager_Material* InManager) = 0;
};