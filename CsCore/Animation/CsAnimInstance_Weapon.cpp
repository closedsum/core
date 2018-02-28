#include "Animation/CsAnimInstance_Weapon.h"
#include "CsCore.h"
#include "Common/CsCommon.h"
#include "Common/CsCommon_Load.h"
#include "Coroutine/CsCoroutineScheduler.h"

// Data
#include "Data/CsData_Weapon.h"
#include "Data/CsData_WeaponMaterialSkin.h"

#include "Weapon/CsWeapon.h"

UCsAnimInstance_Weapon::UCsAnimInstance_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WeaponClass = ACsWeapon::StaticClass();
}

// Setup
#pragma region

void UCsAnimInstance_Weapon::SetupInGameSimulation()
{
#if WITH_EDITOR
	if (!UCsCommon::IsPlayInEditorPreview(GetWorld()))
		return;

	Super::SetupInGameSimulation();

	// Check if Weapon was already created. This may be the case when Refreshing Nodes for the AnimInstance

	for (TActorIterator<ACsWeapon> Itr(GetWorld()); Itr; ++Itr)
	{
		if (Itr &&
			Itr->GetMyOwner() == this)
		{
			Weapon = *Itr;
			break;
		}
	}

	if (!GetWeapon())
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.ObjectFlags					|= RF_Transient;

		Weapon			= GetWorld()->SpawnActor<ACsWeapon>(WeaponClass, SpawnInfo);
		Weapon->SetMyOwner(this);
	}

	UCsCommon_Load::LoadTAssetSubclassOf(TEXT("Data_Weapon"), Data_Weapon.Data, Data_Weapon.Data_Internal, TEXT("MboData_Weapon"));

	if (ACsData_Weapon* MyData_Weapon = GetData_Weapon())
		MyData_Weapon->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));

	UCsCommon_Load::LoadTAssetSubclassOf(TEXT("Data_WeaponMaterialSkin"), Data_WeaponMaterialSkin.Data, Data_WeaponMaterialSkin.Data_Internal, TEXT("CsData_WeaponMaterialSkin"));

	if (ACsData_WeaponMaterialSkin* MyData_WeaponMaterialSkin = GetData_WeaponMaterialSkin())
		MyData_WeaponMaterialSkin->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));

	LoadAnims();
	ApplyData_Weapon();

#endif // #if WITH_EDITOR
}

ACsWeapon* UCsAnimInstance_Weapon::GetWeapon()
{
	return Weapon.IsValid() ? Weapon.Get() : nullptr;
}

void UCsAnimInstance_Weapon::ApplyData_Weapon(){}

#pragma endregion Setup

/*
void UCsAnimInstance_Weapon::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

#if WITH_EDITOR
	OnTick_Handle_Data_Weapon();

	OnTick_Handle_IsFiring();

	if (ACsWeapon* MyWeapon = GetWeapon())
		MyWeapon->OnTick(DeltaTimeX);
#endif // #if WITH_EDITOR
}
*/

// Data
#pragma region

ACsData_Weapon* UCsAnimInstance_Weapon::GetData_Weapon()
{
	return Data_Weapon.Get();
}

void UCsAnimInstance_Weapon::OnTick_Handle_Data_Weapon()
{
	if (Data_Weapon.HasChanged())
	{
		LoadAnims();

		Data_Weapon.Update();
	}
}

ACsData_WeaponMaterialSkin* UCsAnimInstance_Weapon::GetData_WeaponMaterialSkin()
{
	return Data_WeaponMaterialSkin.Get();
}

void UCsAnimInstance_Weapon::OnTick_Handle_Data_WeaponMaterialSkin()
{
	if (Data_WeaponMaterialSkin.HasChanged())
	{
		Data_WeaponMaterialSkin.Update();
	}
}

#pragma endregion Data

// Anims
#pragma region

void UCsAnimInstance_Weapon::LoadAnims(){}

UAnimMontage* UCsAnimInstance_Weapon::GetAnimMontage(const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/) const
{
	return nullptr;
}

UAnimSequence* UCsAnimInstance_Weapon::GetAnimSequence(const TCsWeaponAnim &AnimType) const
{
	return nullptr;
}

UBlendSpace* UCsAnimInstance_Weapon::GetBlendSpace(const TCsWeaponBlendSpace &BlendType) const
{
	return nullptr;
}

void UCsAnimInstance_Weapon::StopAnimation(const TCsWeaponAnim &AnimType, const int32 &Index /*0*/, const float BlendOutTime /*=0.0f*/){}

#pragma endregion Anims