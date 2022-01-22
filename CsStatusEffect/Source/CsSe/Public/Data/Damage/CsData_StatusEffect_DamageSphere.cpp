// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsData_StatusEffect_DamageSphere.h"
#include "CsSe.h"

// Library
#include "Library/Load/CsLibrary_Load.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Data/Shape/CsData_DamageSphereProxy.h"

const FName NCsStatusEffect::NData::NDamage::FSphereProxy::Name = FName("NCsStatusEffect::NData::NDamage::FSphereProxy");

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NDamage
		{
			FSphereProxy::FSphereProxy() :
				Outer(nullptr),
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// SeDataType (NCsStatusEffect::NData::IData)
				bPersistent(nullptr),
				Children(nullptr),
				StatusEffectsToRemove(nullptr),
				TriggerCondition(nullptr),
				TriggerFrequencyParams(nullptr),
				TransferFrequencyParams(nullptr),
				// DamageSeDataType (NCsStatusEffect::NData::NDamage::IDamage)
				DamageData(nullptr)
			{
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FSphereProxy>(this);

				typedef NCsData::IData DataType;
				typedef NCsStatusEffect::NData::IData SeDataType;
				typedef NCsStatusEffect::NData::NDamage::IDamage DamageSeDataType;

				InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
				InterfaceMap->Add<SeDataType>(static_cast<SeDataType*>(this));
				InterfaceMap->Add<DamageSeDataType>(static_cast<DamageSeDataType*>(this));
			}

			FSphereProxy::~FSphereProxy()
			{
				delete InterfaceMap;
			}
		}
	}
}

const FName UCsData_StatusEffect_DamageSphere::Name = FName("UCsData_StatusEffect_DamageSphere");

UCsData_StatusEffect_DamageSphere::UCsData_StatusEffect_DamageSphere(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsData_StatusEffect_DamageSphere::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_StatusEffect_DamageSphere>())
	{
		Init();
		bLoaded = false;
	}
}

void UCsData_StatusEffect_DamageSphere::BeginDestroy()
{
	Super::BeginDestroy();

	// ICsGetInterfaceMap
	CS_SAFE_DELETE_PTR(InterfaceMap)
	// ICsStatusEffect_Damage
	CS_SAFE_DELETE_PTR(DamageSphereProxy)
	CS_SAFE_DELETE_PTR(DataProxy)
}

#pragma endregion UObject Interface

void UCsData_StatusEffect_DamageSphere::Init()
{
	// ICsGetInterfaceMap
	if (!InterfaceMap)
	{
		// Setup InterfaceMap
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->SetRoot<UCsData_StatusEffect_DamageSphere>(this);

		InterfaceMap->Add<ICsData>(Cast<ICsData>(this));
		InterfaceMap->Add<ICsData_StatusEffect>(Cast<ICsData_StatusEffect>(this));
		InterfaceMap->Add<ICsData_StatusEffect_Damage>(Cast<ICsData_StatusEffect_Damage>(this));
	}
	// ICsStatusEffect_Damage
	if (!DamageSphereProxy)
	{
		typedef NCsDamage::NData::NShape::NSphere::FProxy SphereDataProxyType;

		DamageSphereProxy = new SphereDataProxyType();
		DamageSphere.SetData(static_cast<SphereDataProxyType*>(DamageSphereProxy));
	}
	if (!DataProxy)
	{
		typedef NCsStatusEffect::NData::NDamage::FSphereProxy DataProxyType;

		DataProxy = new DataProxyType();

		DataProxyType* Proxy = (DataProxyType*)DataProxy;
		Proxy->SetOuter(this);
		// SeDataType (NCsStatusEffect::NData::IData)
		Proxy->SetIsPersistent(&bPersistent);
		Proxy->SetChildren(&Children);
		Proxy->SetStatusEffectsToRemove(&StatusEffectsToRemove);
		//Proxy->SetTriggerCondition(this);
		//Proxy->SetTriggerFrequencyParams(this);
		//Proxy->SetTransferFrequencyParams(this);
		// DamageSeDataType (NCsStatusEffect::NData::NDamage::IDamage)
		//Proxy->SetDamageData();
	}
}

// ICsData
#pragma region

bool UCsData_StatusEffect_DamageSphere::IsValid(const int32& LoadFlags)
{
	return true;
}

void UCsData_StatusEffect_DamageSphere::Load(const int32& LoadFlags)
{
	UCsLibrary_Load::LoadStruct(this, GetClass(), LoadFlags, NCsLoadCodes::All);

#if WITH_EDITOR
	Init();
#endif // #if WITH_EDITOR

	bLoaded = true;
}

void UCsData_StatusEffect_DamageSphere::Unload()
{

}

bool UCsData_StatusEffect_DamageSphere::IsLoaded() const
{
	return bLoaded;
}

#pragma endregion ICsData