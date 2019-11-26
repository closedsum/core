// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsTower.generated.h"

UINTERFACE(Blueprintable)
class UCsTower : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsData_Tower;

class ICsTower
{
	GENERATED_IINTERFACE_BODY()

public:
	
	virtual ICsData_Tower* GetData()  = 0;

	virtual float GetHealth() = 0;

	virtual void Shoot() = 0;

	virtual void ShootAt(UObject* InTarget) = 0;

	virtual void ShootAtLocation(const FVector& Location) = 0;

	virtual void SetTarget(UObject* InTarget) = 0;

	virtual UObject* GetTarget() = 0;

	virtual int32 GetLevel() = 0;
};