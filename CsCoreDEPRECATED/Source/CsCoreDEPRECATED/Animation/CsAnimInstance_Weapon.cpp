#include "Animation/CsAnimInstance_Weapon.h"
#include "CsCoreDEPRECATED.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "Library/Load/CsLibrary_Load.h"
// Data
#include "Data/CsData_Weapon_DEPRECATED.h"
#include "Data/CsData_WeaponMaterialSkin.h"

#include "Weapon/CsGunWeapon_DEPRECATED.h"

UCsAnimInstance_Weapon::UCsAnimInstance_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	WeaponClass = ACsWeapon_DEPRECATED::StaticClass();
#endif // #if WITH_EDITOR
}

// Init
void UCsAnimInstance_Weapon::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ACsWeapon_DEPRECATED* MyWeapon = GetMyOwningActor<ACsWeapon_DEPRECATED>();

	if (!MyWeapon)
		return;

	// Data_Weapon
	Data_Weapon.Data		  = TSoftClassPtr<UCsData_Weapon_DEPRECATED>(MyWeapon->GetMyData_Weapon());
	Data_Weapon.Data_Internal = MyWeapon->GetMyData_Weapon();

	if (ACsGunWeapon_DEPRECATED* MyGunWeapon = Cast<ACsGunWeapon_DEPRECATED>(MyWeapon))
	{
		// Data_WeaponMaterialSkin
		Data_WeaponMaterialSkin.Data		  = TSoftClassPtr<UCsData_WeaponMaterialSkin>(MyGunWeapon->GetMyData_WeaponMaterialSkin());
		Data_WeaponMaterialSkin.Data_Internal = MyGunWeapon->GetMyData_WeaponMaterialSkin();
	}
	LoadAnims();
}

// Setup
#pragma region

#if WITH_EDITOR

void UCsAnimInstance_Weapon::SetupInGameSimulation()
{
	if (!UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
		return;

	Super::SetupInGameSimulation();

	// Check if Weapon was already created. This may be the case when Refreshing Nodes for the AnimInstance

	for (TActorIterator<ACsWeapon_DEPRECATED> Itr(GetWorld()); Itr; ++Itr)
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

		Weapon			= GetWorld()->SpawnActor<ACsWeapon_DEPRECATED>(WeaponClass, SpawnInfo);
		Weapon->SetMyOwner(this);
	}

	UCsLibrary_Load::LoadTSoftClassPtr(TEXT("Data_Weapon"), Data_Weapon.Data, Data_Weapon.Data_Internal, TEXT("MboData_Weapon"));

	if (UCsData_Weapon_DEPRECATED* MyData_Weapon = GetData_Weapon())
		MyData_Weapon->Load(UCsLibrary_Common::ViewTypeToLoadFlags(CurrentViewType));

	UCsLibrary_Load::LoadTSoftClassPtr(TEXT("Data_WeaponMaterialSkin"), Data_WeaponMaterialSkin.Data, Data_WeaponMaterialSkin.Data_Internal, TEXT("CsData_WeaponMaterialSkin"));

	if (UCsData_WeaponMaterialSkin* MyData_WeaponMaterialSkin = GetData_WeaponMaterialSkin())
		MyData_WeaponMaterialSkin->Load(UCsLibrary_Common::ViewTypeToLoadFlags(CurrentViewType));

	LoadAnims();
	ApplyData_Weapon();
}

ACsWeapon_DEPRECATED* UCsAnimInstance_Weapon::GetWeapon()
{
	return Weapon.IsValid() ? Weapon.Get() : nullptr;
}

void UCsAnimInstance_Weapon::ApplyData_Weapon(){}

#endif // #if WITH_EDITOR

#pragma endregion Setup

/*
void UCsAnimInstance_Weapon::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

#if WITH_EDITOR
	OnTick_Handle_Data_Weapon();

	OnTick_Handle_IsFiring();

	if (ACsWeapon_DEPRECATED* MyWeapon = GetWeapon())
		MyWeapon->OnTick(DeltaTimeX);
#endif // #if WITH_EDITOR
}
*/

// Data
#pragma region

UCsData_Weapon_DEPRECATED* UCsAnimInstance_Weapon::GetData_Weapon()
{
	return Data_Weapon.Get();
}

#if WITH_EDITOR

void UCsAnimInstance_Weapon::OnTick_Handle_Data_Weapon()
{
	if (Data_Weapon.HasChanged())
	{
		LoadAnims();

		Data_Weapon.Update();
	}
}

#endif // #if WITH_EDITOR

UCsData_WeaponMaterialSkin* UCsAnimInstance_Weapon::GetData_WeaponMaterialSkin()
{
	return Data_WeaponMaterialSkin.Get();
}

#if WITH_EDITOR

void UCsAnimInstance_Weapon::OnTick_Handle_Data_WeaponMaterialSkin()
{
	if (Data_WeaponMaterialSkin.HasChanged())
	{
		Data_WeaponMaterialSkin.Update();
	}
}

#endif // #if WITH_EDITOR

#pragma endregion Data

// Anims
#pragma region

void UCsAnimInstance_Weapon::LoadAnims(){}

UAnimMontage* UCsAnimInstance_Weapon::GetAnimMontage(const FECsWeaponAnim& AnimType, const int32& Index /*=0*/) const
{
	return nullptr;
}

UAnimSequence* UCsAnimInstance_Weapon::GetAnimSequence(const FECsWeaponAnim& AnimType) const
{
	return nullptr;
}

UBlendSpace* UCsAnimInstance_Weapon::GetBlendSpace(const FECsWeaponBlendSpace& BlendType) const
{
	return nullptr;
}

void UCsAnimInstance_Weapon::StopAnimation(const FECsWeaponAnim& AnimType, const int32& Index /*0*/, const float BlendOutTime /*=0.0f*/){}

#pragma endregion Anims