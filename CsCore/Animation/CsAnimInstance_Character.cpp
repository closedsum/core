#include "Animation/CsAnimInstance_Character.h"
#include "CsCore.h"
#include "Common/CsCommon_Load.h"
#include "Coroutine/CsCoroutineScheduler.h"

// Data
#include "Data/CsData_Character.h"
#include "Data/CsData_CharacterMeshSkin.h"
#include "Data/CsData_CharacterMaterialSkin.h"
#include "Data/CsData_Weapon.h"
#include "Data/CsData_WeaponMaterialSkin.h"
// Managers
#include "Managers/FX/CsManager_FX.h"
#include "Managers/Sound/CsManager_Sound.h"

#include "Pawn/CsPawn.h"

#include "Weapon/CsWeapon.h"

UCsAnimInstance_Character::UCsAnimInstance_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WeaponClass = ACsWeapon::StaticClass();
}

// Init
void UCsAnimInstance_Character::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

#if WITH_EDITOR 
	DoSetupInGameSimulation = false;
#endif // #if WITH_EDITOR

	OwningPawn		= TryGetPawnOwner();
	ACsPawn* MyPawn = Cast<ACsPawn>(GetOwningPawn());

	if (!MyPawn)
		return;
	
	// Data_Character
	Data_Character.Data = TAssetSubclassOf<ACsData_Character>(MyPawn->GetMyData_Character());
	Data_Character.Data_Internal = MyPawn->GetMyData_Character();
	// Data_CharacterMeshSkin
	Data_CharacterMeshSkin.Data = TAssetSubclassOf<ACsData_CharacterMeshSkin>(MyPawn->GetMyData_CharacterMeshSkin());
	Data_CharacterMeshSkin.Data_Internal = MyPawn->GetMyData_CharacterMeshSkin();
	// Data_CharacterMaterialSkin
	Data_CharacterMaterialSkin.Data = TAssetSubclassOf<ACsData_CharacterMaterialSkin>(MyPawn->GetMyData_CharacterMaterialSkin());
	Data_CharacterMaterialSkin.Data_Internal = MyPawn->GetMyData_CharacterMaterialSkin();
	// Data_Weapon
	Data_Weapon.Data = TAssetSubclassOf<ACsData_Weapon>(MyPawn->GetCurrentData_Weapon());
	Data_Weapon.Data_Internal = MyPawn->GetCurrentData_Weapon();
	// Data_WeaponMaterialSkin
	Data_WeaponMaterialSkin.Data = TAssetSubclassOf<ACsData_WeaponMaterialSkin>(MyPawn->GetCurrentData_WeaponMaterialSkin());
	Data_WeaponMaterialSkin.Data_Internal = MyPawn->GetCurrentData_WeaponMaterialSkin();
	
	LoadAnims();
}

// Setup
#pragma region

void UCsAnimInstance_Character::SetupInGameSimulation()
{
#if WITH_EDITOR
	if (!UCsCommon::IsPlayInEditorPreview(GetWorld()))
		return;

	Super::SetupInGameSimulation();

	Spawn_Manager_FX();
	Spawn_Weapon();

	// Data_Character
	UCsCommon_Load::LoadTAssetSubclassOf(TEXT("Data_Character"), Data_Character.Data, Data_Character.Data_Internal, TEXT("MboData_Character"));

	if (ACsData_Character* MyData_Charater = GetData())
		MyData_Charater->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));
	// Data_CharacterMeshSkin
	UCsCommon_Load::LoadTAssetSubclassOf(TEXT("Data_CharacterMeshSkin"), Data_CharacterMeshSkin.Data, Data_CharacterMeshSkin.Data_Internal, TEXT("MboData_CharacterMeshSkin"));

	if (ACsData_CharacterMeshSkin* MyData_CharacterMeshSkin = GetData_CharacterMeshSkin())
		MyData_CharacterMeshSkin->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));
	// Data_CharacterMaterialSkin
	UCsCommon_Load::LoadTAssetSubclassOf(TEXT("Data_CharacterMaterialSkin"), Data_CharacterMaterialSkin.Data, Data_CharacterMaterialSkin.Data_Internal, TEXT("MboData_CharacterMaterialSkin"));

	if (ACsData_CharacterMaterialSkin* MyData_CharacterMaterialSkin = GetData_CharacterMaterialSkin())
		MyData_CharacterMaterialSkin->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));
	// Data_Weapon
	UCsCommon_Load::LoadTAssetSubclassOf(TEXT("Data_Weapon"), Data_Weapon.Data, Data_Weapon.Data_Internal, TEXT("MboData_Weapon"));

	if (ACsData_Weapon* MyData_Weapon = GetData_Weapon())
		MyData_Weapon->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));
	// Data_WeaponMaterialSkin
	UCsCommon_Load::LoadTAssetSubclassOf(TEXT("Data_WeaponMaterialSkin"), Data_WeaponMaterialSkin.Data, Data_WeaponMaterialSkin.Data_Internal, TEXT("MboData_WeaponMaterialSkin"));

	if (ACsData_WeaponMaterialSkin* MyData_WeaponMaterialSkin = GetData_WeaponMaterialSkin())
		MyData_WeaponMaterialSkin->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));

	LoadAnims();

	// Weapon
	ApplyData_Weapon();
#endif // #if WITH_EDITOR
}

ACsWeapon* UCsAnimInstance_Character::GetWeapon()
{
	return Weapon.IsValid() ? Weapon.Get() : nullptr;
}

void UCsAnimInstance_Character::Spawn_Weapon()
{
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
		SpawnInfo.ObjectFlags |= RF_Transient;

		Weapon = GetWorld()->SpawnActor<ACsWeapon>(WeaponClass, SpawnInfo);
		Weapon->SetMyOwner(this);
	}
}

void UCsAnimInstance_Character::ApplyData_Weapon(){}

#pragma endregion Setup

/*
void UCsAnimInstance_Character::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
#if WITH_EDITOR
	if (!UCsCommon::IsPlayInEditorPreview(GetWorld()))
		return;

	OnTick_Handle_Data_Character();
	OnTick_Handle_Data_CharacterMeshSkin();
	OnTick_Handle_Data_CharacterMaterialSkin();
	OnTick_Handle_Data_Weapon();
	OnTick_Handle_Data_WeaponMaterialSkin();

	if (ACsWeapon* MyWeapon = GetWeapon())
		MyWeapon->OnTick(DeltaTimeX);
#endif // #if WITH_EDITOR

}
*/

// Data
#pragma region

ACsData_Character* UCsAnimInstance_Character::GetData()
{
	return Data_Character.Get();
}

void UCsAnimInstance_Character::OnTick_Handle_Data_Character()
{
	if (Data_Character.HasChanged())
	{
		Data_Character.Update();
	}
}

ACsData_CharacterMeshSkin* UCsAnimInstance_Character::GetData_CharacterMeshSkin()
{
	return Data_CharacterMeshSkin.Get();
}

void UCsAnimInstance_Character::OnTick_Handle_Data_CharacterMeshSkin()
{
	if (Data_CharacterMeshSkin.HasChanged())
	{
		Data_CharacterMeshSkin.Update();
	}
}

ACsData_CharacterMaterialSkin* UCsAnimInstance_Character::GetData_CharacterMaterialSkin()
{
	return Data_CharacterMaterialSkin.Get();
}

void UCsAnimInstance_Character::OnTick_Handle_Data_CharacterMaterialSkin()
{
	if (Data_CharacterMaterialSkin.HasChanged())
	{
		Data_CharacterMaterialSkin.Update();
	}
}

ACsData_Weapon* UCsAnimInstance_Character::GetData_Weapon()
{
	return Data_Weapon.Get();
}

void UCsAnimInstance_Character::OnTick_Handle_Data_Weapon()
{
	if (Data_Weapon.HasChanged())
	{
		Data_Weapon.Update();
	}
}

ACsData_WeaponMaterialSkin* UCsAnimInstance_Character::GetData_WeaponMaterialSkin()
{
	return Data_WeaponMaterialSkin.Get();
}

void UCsAnimInstance_Character::OnTick_Handle_Data_WeaponMaterialSkin()
{
	if (Data_WeaponMaterialSkin.HasChanged())
	{
		Data_WeaponMaterialSkin.Update();
	}
}

#pragma endregion Data

// Anims
#pragma region

void UCsAnimInstance_Character::LoadAnims(){}

UAnimMontage* UCsAnimInstance_Character::GetAnimMontage(const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/) const
{
	return nullptr;
}

UAnimSequence* UCsAnimInstance_Character::GetAnimSequence(const TCsCharacterAnim &AnimType) const
{
	return nullptr;
}

UBlendSpace* UCsAnimInstance_Character::GetBlendSpace(const TCsCharacterBlendSpace &BlendType) const
{
	return nullptr;
}

void UCsAnimInstance_Character::StopAnimation(const TCsCharacterAnim &AnimType, const int32 &Index /*0*/, const float BlendOutTime /*=0.0f*/){}

#pragma endregion Anims