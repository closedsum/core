// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsInteractiveObject.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCOREDEPRECATED_API UCsInteractiveObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class CSCOREDEPRECATED_API ICsInteractiveObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Freeze();
	virtual void UnFreeze();
	virtual void Hold();
	virtual void Release();
	virtual void Touch();
	virtual void Hover();
	virtual void UnHover();
	virtual void Collide();
	virtual void UnCollide();
	virtual void Remove();
};