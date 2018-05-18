// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class ICsBlockchainAccount
{
public:

	ICsBlockchainAccount();
	virtual ~ICsBlockchainAccount();

	virtual const FString& GetNamename() = 0;

	virtual FString ToString() = 0;
	virtual void Parse(const FString &Str) = 0;
	virtual void ParseFromFilePath(const FString &Path) = 0;
};