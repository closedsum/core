// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#ifndef __CSCORE_H__
#define __CSCORE_H__

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCs, Log, All);

class CSCORE_API FCsCore : public IModuleInterface
{
public:

	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

	virtual bool IsGameModule() const
	{
		return true;
	}
};

#endif