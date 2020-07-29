// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"

#include "CsDataRootSet.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsDataRootSet : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UDataTable;

/**
*/
class CSCORE_API ICsDataRootSet
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual UDataTable* GetDatas() const = 0;

	/**
	*
	*
	* return
	*/
	virtual UDataTable* GetDataTables() const = 0;

	/**
	*
	*
	* return
	*/
	virtual UDataTable* GetPayloads() const = 0;
};