// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
// Containers
#include "Containers/CsInterfaceObject.h"
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/Pool/CsTypes_Manager_PooledObject.h"

#include "CsPooledObject.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsPooledObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

class CSCORE_API ICsPooledObject
{
	GENERATED_IINTERFACE_BODY()

#define CacheType NCsPooledObject::NCache::ICache
#define PayloadType NCsPooledObject::NPayload::IPayload

public:

	/**
	*
	*
	* return
	*/
	virtual CacheType* GetCache() const = 0;

	/**
	*
	*
	* @param Payload
	*/
	virtual void Allocate(PayloadType* Payload) = 0;

	/**
	*
	*/
	virtual void Deallocate() = 0;

#undef CacheType
#undef PayloadType
};

// FCsPooledObject
#pragma region

class ICsUpdate;
class ICsOnConstructObject;
class ICsPause;
class ICsShutdown;

struct CSCORE_API FCsPooledObject : public TCsInterfaceObject<ICsPooledObject>
{
private:

	typedef TCsInterfaceObject<ICsPooledObject> Super;

#define CacheType NCsPooledObject::NCache::ICache
#define PayloadType NCsPooledObject::NPayload::IPayload
#define ConstructParamsType NCsPooledObject::NManager::FConstructParams

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

	/** Reference to interface of type: ICsPause. */
	ICsPause* _Pause;

	/** Does the object implements a script interface of type: ICsPause. */
	bool bScriptPause;

	/** Reference to interface of type: ICsShutdown. */
	ICsShutdown* _Shutdown;

	/** Does the object implements a script interface of type: ICsShutdown. */
	bool bScriptShutdown;

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
	DECLARE_DELEGATE_RetVal_OneParam(CacheType* /*Cache*/, FScript_GetCache, UObject* /*Object*/);

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
	DECLARE_DELEGATE_TwoParams(FScript_Allocate, UObject* /*Object*/, PayloadType* /*Payload*/);

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
	DECLARE_DELEGATE_TwoParams(FScript_OnConstructObject, UObject* /*Object*/, const ConstructParamsType& /*Params*/);

	/** Delegate to execute after an object has been constructed.
		 The object implements a script interface of type: ICsOnConstructObject. */
	FScript_OnConstructObject Script_OnConstructObject_Impl;

#pragma endregion ICsOnConstructObject

	// ICsPause
#pragma region
public:

	/**
	* Delegate type for pausing.
	*  The object implements a script interface of type: ICsPause.
	*
	* @param Object		An object of type: ICsPause.
	* @param bPaused	Set whether to pause or un-pause.
	*/
	DECLARE_DELEGATE_TwoParams(FScript_Pause, UObject* /*Object*/, bool /*bPaused*/);

	/** Delegate for pausing.
		  The object implements a script interface of type: ICsPause. */
	FScript_Pause Script_Pause_Impl;


#pragma endregion ICsPause

	// ICsShutdown
#pragma region
public:

	/**
	* Delegate type for pausing.
	*  The object implements a script interface of type: ICsShutdown.
	*
	* @param Object		An object of type: ICsShutdown.
	*/
	DECLARE_DELEGATE_OneParam(FScript_Shutdown, UObject* /*Object*/);

	/** Delegate for pausing.
		  The object implements a script interface of type: ICsShutdown. */
	FScript_Shutdown Script_Shutdown_Impl;


#pragma endregion ICsShutdown

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
			   bScriptUpdate == B.bScriptUpdate &&
			   _OnConstructObject == B._OnConstructObject &&
			   bScriptOnConstructObject == B.bScriptOnConstructObject &&
			   _Pause == B._Pause &&
			   bScriptPause == B.bScriptPause &&
			   _Shutdown == B._Shutdown &&
			   bScriptShutdown == B.bScriptShutdown;
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

	FORCEINLINE CacheType* GetCache() const
	{
		if (bScript)
			return Script_GetCache_Impl.Execute(Object);
		return Interface->GetCache();
	}

	FORCEINLINE void Allocate(PayloadType* Payload)
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

	FORCEINLINE bool Implements_ICsUpdate() const { return _Update != nullptr || bScriptUpdate; }

	FORCEINLINE void SetScriptUpdate() { bScriptUpdate = true; }

	FORCEINLINE const bool& IsScriptUpdate() const { return bScriptUpdate; }

	FORCEINLINE void SetUpdate(ICsUpdate* InUpdate) { _Update = InUpdate; }

	FORCEINLINE ICsUpdate* GetUpdate() const { return _Update; }

	FORCEINLINE ICsUpdate* GetUpdateChecked(const FString& Context) const
	{
		checkf(_Update, TEXT("%s: _Update is NULL."), *Context);

		return _Update;
	}

// ICsOnConstructObject
#pragma region
public:

	void OnConstructObject(const ConstructParamsType& Params);

#pragma endregion ICsOnConstructObject

public:

	FORCEINLINE bool Implements_ICsOnConstructObject() const { return _OnConstructObject != nullptr || bScriptOnConstructObject; }

	FORCEINLINE void SetScriptOnConstructObject() { bScriptOnConstructObject = true; }

	FORCEINLINE const bool& IsScriptOnConstructObject() const { return bScriptOnConstructObject; }

	FORCEINLINE ICsOnConstructObject* GetOnConstructObject() const { return _OnConstructObject; }

	FORCEINLINE void SetOnConstructObject(ICsOnConstructObject* O) { _OnConstructObject = O; }

// ICsPause
#pragma region
public:

	void Pause(bool bPaused);

#pragma endregion ICsPause

public:

	FORCEINLINE bool Implements_ICsPause() const { return _Pause != nullptr || bScriptPause; }

	FORCEINLINE void SetScriptPause() { bScriptPause = true; }

	FORCEINLINE const bool& IsScriptPause() const { return bScriptPause; }

	FORCEINLINE void SetPause(ICsPause* InPause) { _Pause = InPause; }

	FORCEINLINE ICsPause* GetPause() const { return _Pause; }

// ICsShutdown
#pragma region
public:

	void Shutdown();

#pragma endregion ICsShutdown

public:

	FORCEINLINE bool Implements_ICsShutdown() const { return _Shutdown != nullptr || bScriptShutdown; }

	FORCEINLINE void SetScriptShutdown() { bScriptShutdown = true; }

	FORCEINLINE const bool& IsScriptShutdown() const { return bScriptShutdown; }

	FORCEINLINE void SetShutdown(ICsShutdown* InShutdown) { _Shutdown = InShutdown; }

	FORCEINLINE ICsShutdown* GetShutdown() const { return _Shutdown; }

#undef CacheType
#undef PayloadType
#undef ConstructParamsType
};

#pragma endregion FCsPooledObject