// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsData_StatusEffect_DamageSphere.h"
#include "CsSe.h"

// Library
#include "Library/Load/CsLibrary_Load.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Data/Shape/CsData_DamageSphereEmu.h"

const FName NCsStatusEffect::NData::NDamage::FSphereEmu::Name = FName("NCsStatusEffect::NData::NDamage::FSphereEmu");

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NDamage
		{
			FSphereEmu::FSphereEmu() :
				Outer(nullptr),
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// NCsStatusEffect::NData::IData
				TriggerCondition(nullptr),
				TriggerFrequencyParams(nullptr),
				TransferFrequencyParams(nullptr),
				Children(nullptr),
				// NCsStatusEffect::NData::NDamage::IDamage
				DamageData(nullptr)
			{
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FSphereEmu>(this);

				typedef NCsData::IData DataType;
				typedef NCsStatusEffect::NData::IData StatusEffectDataType;
				typedef NCsStatusEffect::NData::NDamage::IDamage StatusEffectDamageDataType;

				InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
				InterfaceMap->Add<StatusEffectDataType>(static_cast<StatusEffectDataType*>(this));
				InterfaceMap->Add<StatusEffectDamageDataType>(static_cast<StatusEffectDamageDataType*>(this));
			}

			FSphereEmu::~FSphereEmu()
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
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
	// ICsStatusEffect_Damage
	if (DamageSphereEmu)
	{
		typedef NCsDamage::NData::NShape::NSphere::FEmu SphereDataEmuType;

		SphereDataEmuType* Emu = static_cast<SphereDataEmuType*>(DamageSphereEmu);
		delete Emu;
		DamageSphereEmu = nullptr;
	}
	if (DataEmu)
	{
		delete DataEmu;
		DataEmu = nullptr;
	}
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
	if (!DamageSphereEmu)
	{
		typedef NCsDamage::NData::NShape::NSphere::FEmu SphereDataEmuType;

		DamageSphereEmu = new SphereDataEmuType();
		DamageSphere.SetData(static_cast<SphereDataEmuType*>(DamageSphereEmu));
	}
	if (!DataEmu)
	{
		typedef NCsStatusEffect::NData::NDamage::FSphereEmu DataEmuType;

		DataEmu = new DataEmuType();

		DataEmuType* Emu = (DataEmuType*)DataEmu;
		Emu->SetOuter(this);
		// // NCsStatusEffect::NData::IData
		//Emu->SetTriggerCondition(this);
		//Emu->SetTriggerFrequencyParams(this);
		//Emu->SetTransferFrequencyParams(this);
		//Emu->SetChildren(this);
		// NCsStatusEffect::NData::NDamage::IDamage
		//Emu->SetDamageData();
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