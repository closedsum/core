// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Team/CsTypes_Team.h"

#include "CsTeam.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsTeam : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSCORE_API ICsTeam
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*/
	virtual const uint32& GetTeam() const = 0;

	/**
	*/
	virtual bool IsOnTeam(const FECsTeam& Team) const = 0;
};