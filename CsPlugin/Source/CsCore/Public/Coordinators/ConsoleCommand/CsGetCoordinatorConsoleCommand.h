// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "CsGetCoordinatorConsoleCommand.generated.h"

class UCsCoordinator_ConsoleCommand;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetCoordinatorConsoleCommand : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSCORE_API ICsGetCoordinatorConsoleCommand
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsCoordinator_ConsoleCommand* GetCoordinator_ConsoleCommand() const = 0;

	virtual void SetCoordinator_ConsoleCommand(UCsCoordinator_ConsoleCommand* InCoordinator) = 0;
};