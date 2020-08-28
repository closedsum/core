// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsUserWidgetPooled.generated.h"

UINTERFACE(BlueprintType)
class CSUI_API UCsUserWidgetPooled : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UUserWidget;

/**
* Interface for a pooled UObject "container" holding a reference to a User Widget.
* Pipe pool related interface functions through the container to avoid having to make
* derived classes for User Widget (at this point it seems unnecessary).
*
* FUTURE: Potentially do NOT have a UObject as the container and use a normal class / struct
*		  that is more light weight.
*/
class CSUI_API ICsUserWidgetPooled
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/**
	* 
	*
	* return
	*/
	virtual UUserWidget* GetUserWidget() const = 0;
};

// FCsUserWidgetPooled
#pragma region

class ICsUserWidgetPooled;

struct CSUI_API FCsUserWidgetPooled : public FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

public:

	static const FCsUserWidgetPooled Empty;

protected:

	/** Reference to interface of type: ICsUserWidgetPooled. */
	ICsUserWidgetPooled* UserWidgetPooled;

	/** Does the User Widget implement a script interface of type: ICsUserWidgetPooled. */
	bool bScriptUserWidgetPooled;

// Script
#pragma region
public:

	// ICsUserWidgetPooled
#pragma region
public:

	/**
	* Delegate type for getting the pooled User Widget.
	*  The object implements a script interface of type: ICsUserWidgetPooled.
	*
	* @param Object		An object of type: ICsUserWidgetPooled.
	* return UserWidget	User Widget.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UUserWidget* /*UserWidget*/, FScript_GetUserWidget, UObject* /*Object*/);

	/** Delegate for getting the pooled UserWidget. 
		 The object implements a script interface of type: ICsUserWidgetPooled. */
	FScript_GetUserWidget Script_GetUserWidget_Impl;

#pragma endregion ICsUserWidgetPooled

#pragma endregion Script

public:

	FCsUserWidgetPooled();

	virtual ~FCsUserWidgetPooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsUserWidgetPooled
#pragma region
public:

	UUserWidget* GetUserWidget() const;

#pragma endregion ICsUserWidgetPooled

	FORCEINLINE void SetScriptUserWidgetPooled()
	{
		bScriptUserWidgetPooled = true;
	}

	FORCEINLINE const bool& IsScriptUserWidgetPooled() const
	{
		return bScriptUserWidgetPooled;
	}

	FORCEINLINE ICsUserWidgetPooled* GetUserWidgetPooled() const
	{
		return UserWidgetPooled;
	}

	FORCEINLINE void SetUserWidgetPooled(ICsUserWidgetPooled* InUserWidgetPooled)
	{
		UserWidgetPooled = InUserWidgetPooled;
	}

public:

	void SetPooledObject(const FCsPooledObject& PooledObject);
};

#pragma endregion FCsFXActorPooled