// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#pragma once

struct FCsConsoleCommandInfo
{
public:

	TArray<FString> Commands;
	TArray<FString> Definitions;
	FString Description;

	FCsConsoleCommandInfo() :
		Commands(),
		Definitions(),
		Description()
	{
	}
};