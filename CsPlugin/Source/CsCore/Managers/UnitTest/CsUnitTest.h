// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

class CSCORE_API ICsUnitTest
{
public:

	virtual ~ICsUnitTest() {}

	/**
	* Get the Name of the Test as a FName.
	*
	* return	Name as a FName for the Test.
	*/
	virtual const FName& GetFName() const = 0;

	/**
	* Get the Name of the Test as a FString.
	*
	* return	Name as a FString for the Test.
	*/
	virtual const FString& GetName() const = 0;

	/**
	* Get the Display Name of the Test as a FName.
	*
	* return Display Name as a FName for the Test.
	*/
	virtual const FName& GetDisplayFName() const = 0;

	/**
	* Get the Class Name of the Test as a FString.
	*
	* return Class Name as a FString for the Test.
	*/
	virtual const FString& GetDisplayName() const = 0;

	/**
	*
	*
	* @param InRoot
	*/
	virtual void SetMyRoot(UObject* InRoot) = 0;

	/**
	*
	*
	* return	
	*/
	virtual UObject* GetMyRoot() const = 0;

	/**
	* Start the Test.
	*/
	virtual void Start() = 0;

	/**
	* Check whether the Test is complete or not.
	*
	* return	true if the Test is complete, false otherwise.
	*/
	virtual bool IsComplete() const = 0;
};