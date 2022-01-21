// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Pool/CsPooledObject.h"

class ICsWidgetActor;
class UCsWidgetComponent;

struct CSUI_API FCsWidgetActorPooled : public FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

public:

	static const FCsWidgetActorPooled Empty;

protected:

	/** Reference to interface of type: ICsWidgetActor. */
	ICsWidgetActor* WidgetActor;

	/** Does the Widget Actor implement a script interface of type: ICsWidgetActor. */
	bool bScriptWidgetActor;

// Script
#pragma region
public:

	// ICsWidgetActor
#pragma region
public:

	/**
	* Delegate type for getting the pooled Widget Actor.
	*  The object implements a script interface of type: ICsWidgetActor.
	*
	* @param Object				An object of type: ICsWidgetActor.
	* return WidgetComponent	Widget Component.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UCsWidgetComponent* /*WidgetComponent*/, FScript_GetWidgetComponent, UObject* /*Object*/);

	/** Delegate for getting the WidgetComponent associated with Widget Actor. 
		 The object implements a script interface of type: ICsWidgetActor. */
	FScript_GetWidgetComponent Script_GetWidgetComponent_Impl;

#pragma endregion ICsWidgetActor

#pragma endregion Script

public:

	FCsWidgetActorPooled();

	virtual ~FCsWidgetActorPooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsWidgetActor
#pragma region
public:

	UCsWidgetComponent* GetWidgetComponent() const;

#pragma endregion ICsWidgetActor

	FORCEINLINE void SetScriptWidgetActor()
	{
		bScriptWidgetActor = true;
	}

	FORCEINLINE const bool& IsScriptWidgetActor() const
	{
		return bScriptWidgetActor;
	}

	FORCEINLINE ICsWidgetActor* GetWidgetActor() const
	{
		return WidgetActor;
	}

	FORCEINLINE void SetWidgetActor(ICsWidgetActor* InWidgetActor)
	{
		WidgetActor = InWidgetActor;
	}

public:

	void SetPooledObject(const FCsPooledObject& PooledObject);
};