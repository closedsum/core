// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
// Types
#include "Types/CsTypes_Projectile.h"

#include "CsProjectile.generated.h"

UINTERFACE(Blueprintable)
class CSPRJ_API UCsProjectile : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsProjectile::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, IPayload)
// NCsProjectile::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, IData)

class CSPRJ_API ICsProjectile
{
	GENERATED_IINTERFACE_BODY()

#define PayloadType NCsProjectile::NPayload::IPayload
#define DataType NCsProjectile::NData::IData

public:

	virtual const FECsProjectile& GetProjectileType() const = 0;

	virtual void Launch(PayloadType* Payload) = 0;

	/**
	* The Data the projectile is currently using.
	*
	* return Data that implements the interface: DataType (NCsProjectile::NData::IData).
	*/
	virtual DataType* GetData() const = 0;

	/**
	* The object that "owns" the projectile.
	*
	* return Owner of the projectile.
	*/
	virtual UObject* GetOwner() const = 0;

	/**
	* The object that started the process of launching / activating the projectile.
	*
	* return Instigator of the projectile.
	*/
	virtual UObject* GetInstigator() const = 0;

#undef PayloadType
#undef DataType
};

// FCsProjectile
#pragma region

// NCsProjectile::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, IPayload)
// NCsProjectile::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, IData)

struct CSPRJ_API FCsProjectile : public TCsInterfaceObject<ICsProjectile>
{
private:

	typedef TCsInterfaceObject<ICsProjectile> Super;

#define PayloadType NCsProjectile::NPayload::IPayload
#define DataType NCsProjectile::NData::IData

public:

	static const FCsProjectile Empty;

	// Script
#pragma region

public:

	/**
	* Delegate type for
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* @param Payload
	* return
	*/
	DECLARE_DELEGATE_RetVal_OneParam(const FECsProjectile& /*Type*/, FScript_GetProjectileType, UObject* /*Object*/);

	/** Delegate type for  */
	FScript_GetProjectileType Script_GetProjectileType_Impl;

	/**
	* Delegate type for
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* @param Payload
	* return
	*/
	DECLARE_DELEGATE_TwoParams(FScript_Launch, UObject* /*Object*/, PayloadType* /*Payload*/);

	/** Delegate type for  */
	FScript_Launch Script_Launch_Impl;

	/**
	* Delegate type for
	*
	* @param Object		Object->GetClass() that implements the interface: ICsProjectile.
	* return			.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(DataType* /*Data*/, FScript_GetData, UObject* /*Object*/);

	/** Delegate type for . 
		 The Data implements a script interface of type: ICsWeapon and the UClass
		 associated with the Object have ImplementsInterface(UCsProjectile::StaticClass()) == true. */
	FScript_GetData Script_GetData_Impl;
	
	/**
	* Delegate type for 
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* return
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Owner*/, FScript_GetOwner, UObject* /*Object*/);

	/** Delegate type for  */
	FScript_GetOwner Script_GetOwner_Impl;

	/**
	* Delegate type for
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* return
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Owner*/, FScript_GetInstigator, UObject* /*Object*/);

	/** Delegate type for  */
	FScript_GetInstigator Script_GetInstigator_Impl;

#pragma endregion Script

public:

	FCsProjectile() :
		Super(),
		Script_GetProjectileType_Impl(),
		Script_Launch_Impl(),
		Script_GetData_Impl(),
		Script_GetOwner_Impl(),
		Script_GetInstigator_Impl()
	{
	}

	virtual ~FCsProjectile() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetObject(UObject* InObject) override;

#pragma endregion TCsInterfaceObject

// TCsInterfaceObject
#pragma region
public:

	virtual void Reset() override
	{
		Super::Reset();

		Script_GetProjectileType_Impl.Unbind();
		Script_Launch_Impl.Unbind();
		Script_GetData_Impl.Unbind();
		Script_GetOwner_Impl.Unbind();
		Script_GetInstigator_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

// ICsProjectile
#pragma region
public:

	FORCEINLINE const FECsProjectile& GetProjectileType()
	{
		if (bScript)
			return Script_GetProjectileType_Impl.Execute(Object);
		return Interface->GetProjectileType();
	}

	FORCEINLINE void Launch(PayloadType* Payload)
	{
		if (bScript)
			Script_Launch_Impl.Execute(Object, Payload);
		else
			Interface->Launch(Payload);
	}

	FORCEINLINE DataType* GetData()
	{
		if (bScript)
			return Script_GetData_Impl.Execute(Object);
		return Interface->GetData();
	}

	UObject* GetOwner();

	UObject* GetInstigator();

#pragma endregion ICsProjectile

#undef PayloadType
#undef DataType
};

#pragma endregion FCsProjectile