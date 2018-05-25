// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchainCommand.h"

EMCsBlockchainCommand* EMCsBlockchainCommand::Instance;

EMCsBlockchainCommand& EMCsBlockchainCommand::Get()
{
	if (!Instance)
		Instance = new EMCsBlockchainCommand();
	return *Instance;
}