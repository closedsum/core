// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
class ICsUnitTest;

class CSCORE_API ICsUnitTestPlan
{
public:

	virtual ~ICsUnitTestPlan() {}

	/**
	* Get the Class Name of the Plan as a FName.
	*
	* return Class Name as a FName for the Plan.
	*/
	virtual const FName& GetFName() const = 0;

	/**
	* Get the Class Name of the Plan as a FString.
	*
	* return Class Name as a FString for the Plan.
	*/
	virtual const FString& GetName() const = 0;

	/**
	* Get the Display Name of the Plan as a FName.
	*
	* return Display Name as a FName for the Plan.
	*/
	virtual const FName& GetDisplayFName() const = 0;

	/**
	* Get the Class Name of the Plan as a FString.
	*
	* return Class Name as a FString for the Plan.
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

protected:

	/**
	* Add a Test to the list of tests for the Plan.
	*
	* @param Test	Test to add to the Plan.
	*/
	virtual void Add(ICsUnitTest* Test) = 0;

public:

	/**
	*
	*
	* return Current Test
	*/
	virtual const ICsUnitTest* GetCurrentTest() const = 0;

	/**
	* Start the Plan.
	*/
	virtual void Start() = 0;

	/**
	* Check whether the Plan is complete or not.
	*
	* return true if the Plan is complete, false otherwise.
	*/
	virtual bool IsComplete() const = 0;
};