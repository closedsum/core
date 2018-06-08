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

// Cache
#pragma region

namespace ECsAnimInstanceCharacterCached
{
	namespace Str
	{
		const FString Data_Character = TEXT("Data_Character");
		const FString CsData_Character = TEXT("CsData_Character");
		const FString Data_CharacterMeshSkin = TEXT("Data_CharacterMeshSkin");
		const FString CsData_CharacterMeshSkin = TEXT("CsData_CharacterMeshSkin");
		const FString Data_CharacterMaterialSkin = TEXT("Data_CharacterMaterialSkin");
		const FString CsData_CharacterMaterialSkin = TEXT("CsData_CharacterMaterialSkin");
		const FString Data_Weapon = TEXT("Data_Weapon");
		const FString CsData_Weapon = TEXT("CsData_Weapon");
		const FString Data_WeaponMaterialSkin = TEXT("Data_WeaponMaterialSkin");
		const FString CsData_WeaponMaterialSkin = TEXT("CsData_WeaponMaterialSkin");
	}
}

#pragma endregion Cache

UCsAnimInstance_Character::UCsAnimInstance_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	WeaponClass = ACsWeapon::StaticClass();
#endif // #if WITH_EDITOR
}

// Init
void UCsAnimInstance_Character::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

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

#if WITH_EDITOR

void UCsAnimInstance_Character::SetupInGameSimulation()
{
	Super::SetupInGameSimulation();

	if (!UCsCommon::IsPlayInEditorPreview(GetWorld()))
		return;

	Spawn_Weapon();

	LoadData_Character();
	LoadData_CharacterMeshSkin();
	LoadData_CharacterMaterialSkin();
	LoadData_Weapon();
	LoadData_WeaponMaterialSkin();

	LoadAnims();

	// Weapon
	ApplyData_Weapon();
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

#endif // #if WITH_EDITOR

#pragma endregion Setup


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

	OnTick_Handle_Weapon(DeltaTimeX);
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

void UCsAnimInstance_Character::OnTick_Handle_Weapon(const float &DeltaTimeX)
{
	if (ACsWeapon* MyWeapon = GetWeapon())
		MyWeapon->OnTick(DeltaTimeX);
}

#endif // #if WITH_EDITOR

// Data
#pragma region
	
	// Character
#pragma region

ACsData_Character* UCsAnimInstance_Character::GetData()
{
	return Data_Character.Get();
}

void UCsAnimInstance_Character::LoadData_Character()
{
	const FString& DataString   = ECsAnimInstanceCharacterCached::Str::Data_Character;
	const FString& CsDataString = ECsAnimInstanceCharacterCached::Str::CsData_Character;

	UCsCommon_Load::LoadTAssetSubclassOf(DataString, Data_Character.Data, Data_Character.Data_Internal, CsDataString);

	if (ACsData_Character* MyData_Charater = GetData())
		MyData_Charater->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));
}

#if WITH_EDITOR

void UCsAnimInstance_Character::OnTick_Handle_Data_Character()
{
	if (Data_Character.HasChanged())
	{
		LoadData_Character();
		Data_Character.Update();
	}
}

#endif // #if WITH_EDITOR

#pragma endregion Character

	// CharacterMeshSkin
#pragma region

ACsData_CharacterMeshSkin* UCsAnimInstance_Character::GetData_CharacterMeshSkin()
{
	return Data_CharacterMeshSkin.Get();
}

void UCsAnimInstance_Character::LoadData_CharacterMeshSkin()
{
	const FString& DataString   = ECsAnimInstanceCharacterCached::Str::Data_CharacterMeshSkin;
	const FString& CsDataString = ECsAnimInstanceCharacterCached::Str::CsData_CharacterMeshSkin;

	UCsCommon_Load::LoadTAssetSubclassOf(DataString, Data_CharacterMeshSkin.Data, Data_CharacterMeshSkin.Data_Internal, CsDataString);

	if (ACsData_CharacterMeshSkin* MyData_CharacterMeshSkin = GetData_CharacterMeshSkin())
		MyData_CharacterMeshSkin->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));
}

#if WITH_EDITOR

void UCsAnimInstance_Character::OnTick_Handle_Data_CharacterMeshSkin()
{
	if (Data_CharacterMeshSkin.HasChanged())
	{
		LoadData_CharacterMeshSkin();
		Data_CharacterMeshSkin.Update();
	}
}

#endif // #if WITH_EDITOR

#pragma endregion CharacterMeshSkin

	// CharacterMaterialSkin
#pragma region

ACsData_CharacterMaterialSkin* UCsAnimInstance_Character::GetData_CharacterMaterialSkin()
{
	return Data_CharacterMaterialSkin.Get();
}

void UCsAnimInstance_Character::LoadData_CharacterMaterialSkin()
{
	const FString& DataString   = ECsAnimInstanceCharacterCached::Str::Data_CharacterMaterialSkin;
	const FString& CsDataString = ECsAnimInstanceCharacterCached::Str::CsData_CharacterMaterialSkin;

	UCsCommon_Load::LoadTAssetSubclassOf(DataString, Data_CharacterMaterialSkin.Data, Data_CharacterMaterialSkin.Data_Internal, CsDataString);

	if (ACsData_CharacterMaterialSkin* MyData_CharacterMaterialSkin = GetData_CharacterMaterialSkin())
		MyData_CharacterMaterialSkin->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));
}

#if WITH_EDITOR

void UCsAnimInstance_Character::OnTick_Handle_Data_CharacterMaterialSkin()
{
	if (Data_CharacterMaterialSkin.HasChanged())
	{
		LoadData_CharacterMaterialSkin();
		Data_CharacterMaterialSkin.Update();
	}
}

#endif // #if WITH_EDITOR

#pragma endregion CharacterMaterialSkin

	// Weapon
#pragma region

ACsData_Weapon* UCsAnimInstance_Character::GetData_Weapon()
{
	return Data_Weapon.Get();
}

void UCsAnimInstance_Character::LoadData_Weapon()
{
	const FString& DataString   = ECsAnimInstanceCharacterCached::Str::Data_Weapon;
	const FString& CsDataString = ECsAnimInstanceCharacterCached::Str::CsData_Weapon;

	UCsCommon_Load::LoadTAssetSubclassOf(DataString, Data_Weapon.Data, Data_Weapon.Data_Internal, CsDataString);

	if (ACsData_Weapon* MyData_Weapon = GetData_Weapon())
		MyData_Weapon->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));
}

#if WITH_EDITOR

void UCsAnimInstance_Character::OnTick_Handle_Data_Weapon()
{
	if (Data_Weapon.HasChanged())
	{
		LoadData_Weapon();
		Data_Weapon.Update();
	}
}

#endif // #if WITH_EDITOR

#pragma endregion Weapon

	// WeaponMaterialSkin
#pragma region

ACsData_WeaponMaterialSkin* UCsAnimInstance_Character::GetData_WeaponMaterialSkin()
{
	return Data_WeaponMaterialSkin.Get();
}

void UCsAnimInstance_Character::LoadData_WeaponMaterialSkin()
{
	const FString& DataString   = ECsAnimInstanceCharacterCached::Str::Data_WeaponMaterialSkin;
	const FString& CsDataString = ECsAnimInstanceCharacterCached::Str::CsData_WeaponMaterialSkin;

	UCsCommon_Load::LoadTAssetSubclassOf(DataString, Data_WeaponMaterialSkin.Data, Data_WeaponMaterialSkin.Data_Internal, CsDataString);

	if (ACsData_WeaponMaterialSkin* MyData_WeaponMaterialSkin = GetData_WeaponMaterialSkin())
		MyData_WeaponMaterialSkin->Load(UCsCommon::ViewTypeToLoadFlags(CurrentViewType));
}

#if WITH_EDITOR

void UCsAnimInstance_Character::OnTick_Handle_Data_WeaponMaterialSkin()
{
	if (Data_WeaponMaterialSkin.HasChanged())
	{
		LoadData_WeaponMaterialSkin();
		Data_WeaponMaterialSkin.Update();
	}
}

#endif // #if WITH_EDITOR

#pragma endregion WeaponMaterialSkin

#pragma endregion Data

// Anims
#pragma region

void UCsAnimInstance_Character::LoadAnims(){}

UAnimMontage* UCsAnimInstance_Character::GetAnimMontage(const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/) const
{
	return nullptr;
}

UAnimSequence* UCsAnimInstance_Character::GetAnimSequence(const FECsCharacterAnim &AnimType) const
{
	return nullptr;
}

UBlendSpace1D* UCsAnimInstance_Character::GetBlendSpace1D(const FECsCharacterBlendSpace &BlendType) const
{
	return nullptr;
}

UBlendSpace* UCsAnimInstance_Character::GetBlendSpace(const FECsCharacterBlendSpace &BlendType) const
{
	return nullptr;
}

void UCsAnimInstance_Character::StopAnimation(const FECsCharacterAnim &AnimType, const int32 &Index /*0*/, const float BlendOutTime /*=0.0f*/){}

#pragma endregion Anims