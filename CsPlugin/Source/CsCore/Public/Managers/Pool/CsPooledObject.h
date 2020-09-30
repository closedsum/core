// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/Pool/CsTypes_Manager_PooledObject.h"
#include "CsPooledObject.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsPooledObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

namespace NCsPooledObject {
	namespace NCache {
		struct ICache; } }

namespace NCsPooledObject {
	namespace NPayload {
		struct IPayload; } }

class CSCORE_API ICsPooledObject
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual NCsPooledObject::NCache::ICache* GetCache() const = 0;

	/**
	*
	*
	* @param Payload
	*/
	virtual void Allocate(NCsPooledObject::NPayload::IPayload* Payload) = 0;

	/**
	*
	*/
	virtual void Deallocate() = 0;
};

// FCsPooledObject
#pragma region

class ICsUpdate;
class ICsOnConstructObject;

struct CSCORE_API FCsPooledObject : public TCsInterfaceObject<ICsPooledObject>
{
private:

	typedef TCsInterfaceObject<ICsPooledObject> Super;

public:

	static const FCsPooledObject Empty;

protected:

	/** Reference to interface of type: ICsUpdate. */
	ICsUpdate* _Update;

	/** Does the object implements a script interface of type: ICsUpdate. */
	bool bScriptUpdate;

	/** Reference to interface of type: ICsOnConstructObject. */
	ICsOnConstructObject* _OnConstructObject;

	/** Does the object implements a script interface of type: ICsOnConstructObject. */
	bool bScriptOnConstructObject;

// Script
#pragma region
public:

	// ICsPooledObject
#pragma region
public:

	/**
	* Delegate type for getting the Cache associated with a Pooled Object.
	*  The Pooled Object implements a script interface of type: ICsPooledObject.
	*
	* @param Object		A Pooled Object of type: ICsPooledObject.
	* return Cache		The cache associated with the Pooled Object.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(NCsPooledObject::NCache::ICache* /*Cache*/, FScript_GetCache, UObject* /*Object*/);

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
	DECLARE_DELEGATE_TwoParams(FScript_Allocate, UObject* /*Object*/, NCsPooledObject::NPayload::IPayload* /*Payload*/);

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

#pragma endregion ICsPooledObject;

	// ICsUpdate
#pragma region
public:

	/**
	* Delegate type for updating an object.
	*   The object implements a script interface of type: ICsUpdate.
	*
	* @param Object		A Pooled Object of type: ICsUpdate.
	* @param DeltaTime
	*/
	DECLARE_DELEGATE_TwoParams(FScript_Update, UObject* /*Object*/, const FCsDeltaTime& /*DeltaTime*/);

	/** Delegate for updating a Pooled Object. */
	FScript_Update Script_Update_Impl;

#pragma endregion ICsUpdate

	
	// ICsOnConstructObject
#pragma region
public:

	/**
	* Delegate type to execute after an object has been constructed.
	*  The object implements a script interface of type: ICsOnConstructObject.
	*
	* @param Object		An object of type: ICsOnConstructObject.
	* @para Params
	*/
	DECLARE_DELEGATE_TwoParams(FScript_OnConstructObject, UObject* /*Object*/, const FCsManagerPooledObjectConstructParams& /*Params*/);

	/** Delegate to execute after an object has been constructed.
		 The object implements a script interface of type: ICsOnConstructObject. */
	FScript_OnConstructObject Script_OnConstructObject_Impl;

#pragma endregion ICsOnConstructObject

#pragma endregion Script

public:

	FCsPooledObject();

	virtual ~FCsPooledObject() {}

	FORCEINLINE bool operator==(const FCsPooledObject& B) const
	{
		return Interface == B.Interface &&
			   WeakObject == B.WeakObject &&
			   Object == B.Object &&
			   bObject == B.bObject &&
			   bScript == B.bScript &&
			   _Update == B._Update &&
			   bScriptUpdate == B.bScriptUpdate;
	}

	FORCEINLINE bool operator!=(const FCsPooledObject& B) const
	{
		return !(*this == B);
	}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsPooledObject
#pragma region
public:

	FORCEINLINE NCsPooledObject::NCache::ICache* GetCache() const
	{
		if (bScript)
			return Script_GetCache_Impl.Execute(Object);
		return Interface->GetCache();
	}

	FORCEINLINE void Allocate(NCsPooledObject::NPayload::IPayload* Payload)
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

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

public:

	FORCEINLINE void SetScriptUpdate()
	{
		bScriptUpdate = true;
	}

	FORCEINLINE const bool& IsScriptUpdate() const
	{
		return bScriptUpdate;
	}

	FORCEINLINE void SetUpdate(ICsUpdate* InUpdate)
	{
		_Update = InUpdate;
	}

	FORCEINLINE ICsUpdate* GetUpdate() const 
	{
		return _Update;
	}

// ICsOnConstructObject
#pragma region
public:

	void OnConstructObject(const FCsManagerPooledObjectConstructParams& Params);

#pragma endregion ICsOnConstructObject

public:

	FORCEINLINE bool Implements_ICsOnConstructObject() const
	{
		return _OnConstructObject != nullptr || bScriptOnConstructObject;
	}

	FORCEINLINE void SetScriptOnConstructObject()
	{
		bScriptOnConstructObject = true;
	}

	FORCEINLINE const bool& IsScriptOnConstructObject() const
	{
		return bScriptOnConstructObject;
	}

	FORCEINLINE ICsOnConstructObject* GetOnConstructObject() const
	{
		return _OnConstructObject;
	}

	FORCEINLINE void SetOnConstructObject(ICsOnConstructObject* O)
	{
		_OnConstructObject = O;
	}
};

#pragma endregion FCsPooledObject