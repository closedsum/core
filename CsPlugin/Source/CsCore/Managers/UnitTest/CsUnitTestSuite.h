// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
class ICsUnitTest;

class CSCORE_API ICsUnitTestSuite
{
public:

	virtual ~ICsUnitTestSuite() {}

	/**
	* Get the Name of the Suite as a FName.
	*
	* return Name as a FName for the Suite.
	*/
	virtual const FName& GetFName() const = 0;

	/**
	* Get the Name of the Suite as a FString.
	*
	* return Name as a FString for the Suite.
	*/
	virtual const FString& GetName() const = 0;

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
	virtual UObject* GetMyRoot() = 0;

protected:

	/**
	* Add a Test to the list of tests for the Suite.
	*
	* @param Test	Test to add to the Suite.
	*/
	virtual void Add(ICsUnitTest* Test) = 0;

public:

	/**
	* Start the Suite.
	*/
	virtual void Start() = 0;

	/**
	* Check whether the Suite is complete or not.
	*
	* return true if the Suite is complete, false otherwise.
	*/
	virtual bool IsComplete() const = 0;
};