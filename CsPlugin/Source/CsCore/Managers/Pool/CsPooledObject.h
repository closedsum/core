// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsTypes_Pool.h"
#include "Containers/CsInterfaceObject.h"
#include "CsPooledObject.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsPooledObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsPooledObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual ICsPooledObjectCache* GetCache() const = 0;

	virtual void Allocate(ICsPooledObjectPayload* Payload) = 0;

	virtual void Deallocate() = 0;
};

// FCsPooledObject
#pragma region

struct CSCORE_API FCsPooledObject : public TCsInterfaceObject<ICsPooledObject>
{
private:

	typedef TCsInterfaceObject<ICsPooledObject> Super;

public:

	static const FCsPooledObject Empty;

// Script
#pragma region
public:

	/**
	* Delegate type for getting the Cache associated with a Pooled Object.
	*  The Pooled Object implements a script interface of type: ICsPooledObject.
	*
	* @param Object		A Pooled Object of type: ICsPooledObject.
	* return Cache		The cache associated with the Pooled Object.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(ICsPooledObjectCache* /*Cache*/, FScript_GetCache, UObject* /*Object*/);

	/** Delegate for getting the Cache associated with a Pooled Object. 
		 The Pooled Object implements a script interface of type: ICsPooledObject. */
	FScript_GetCache Script_GetCache_Impl;

	/**
	* Delegate type for allocating a Pooled Object.
	*  The Pooled Object implements a script interface of type: ICsPooledObject.
	*
	* @param Object		A Pooled Object of type: ICsPooledObject.
	* @param Payload	A "blob" of parameters to pass in when allocating a Pooled Object.
	*/
	DECLARE_DELEGATE_TwoParams(FScript_Allocate, UObject* /*Object*/, ICsPooledObjectPayload* /*Payload*/);

	/** Delegate for allocating a Pooled Object. 
		  The Pooled Object implements a script interface of type: ICsPooledObject. */
	FScript_Allocate Script_Allocate_Impl;

	/**
	* Delegate type for deallocating a Pooled Object.
	*   The Pooled Object implements a script interface of type: ICsPooledObject.
	*
	* @param Object		A Pooled Object of type: ICsPooledObject.
	*/
	DECLARE_DELEGATE_OneParam(FScript_Deallocate, UObject* /*Object*/);

	/** Delegate for deallocating a Pooled Object. */
	FScript_Deallocate Script_Deallocate_Impl;

#pragma endregion Script

public:

	FCsPooledObject() :
		Super(),
		Script_GetCache_Impl(),
		Script_Allocate_Impl(),
		Script_Deallocate_Impl()
	{
	}

	virtual ~FCsPooledObject() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void Reset() override 
	{
		Super::Reset();

		Script_GetCache_Impl.Unbind();
		Script_Allocate_Impl.Unbind();
		Script_Deallocate_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

// ICsPooledObject
#pragma region
public:

	FORCEINLINE ICsPooledObjectCache* GetCache() const
	{
		if (bScript)
			return Script_GetCache_Impl.Execute(Object);
		return Interface->GetCache();
	}

	FORCEINLINE void Allocate(ICsPooledObjectPayload* Payload)
	{
		if (bScript)
			Script_Allocate_Impl.Execute(Object, Payload);
		else
			Interface->Allocate(Payload);
	}

	FORCEINLINE void Deallocate()
	{
		if (bScript)
			Script_Deallocate_Impl.Execute(Object);
		else
			Interface->Deallocate();
	}
#pragma endregion ICsPooledObject
};

#pragma endregion FCsPooledObject