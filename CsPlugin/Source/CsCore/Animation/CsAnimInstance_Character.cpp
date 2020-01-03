#include "Animation/CsAnimInstance_Character.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Library/CsLibrary_Load.h"
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

namespace NCsAnimInstanceCharacterCached
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

#if WITH_EDITOR
	if (UCsLibrary_Common::IsPlayInEditor(GetWorld()))
		return;

	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		if (!MyPawn)
			return;

		if (MyPawn->bSetupInGameSimulation)
		{
			MyPawn->SetupInGameSimulation();
			SetupInGameSimulation();
		}
		return;
	}
#endif // #if WITH_EDITOR
	
	// TODO: IsOnBoardCompleted_Game needs to be changed to IsOnBoardCompleted
	if (!MyPawn->IsOnBoardCompleted_Game())
		return;

	// Data_Character
	Data_Character.Data = TSoftClassPtr<UCsData_Character>(MyPawn->GetMyData_Character());
	Data_Character.Data_Internal = MyPawn->GetMyData_Character();
	// Data_CharacterMeshSkin
	Data_CharacterMeshSkin.Data = TSoftClassPtr<UCsData_CharacterMeshSkin>(MyPawn->GetMyData_CharacterMeshSkin());
	Data_CharacterMeshSkin.Data_Internal = MyPawn->GetMyData_CharacterMeshSkin();
	// Data_CharacterMaterialSkin
	Data_CharacterMaterialSkin.Data = TSoftClassPtr<UCsData_CharacterMaterialSkin>(MyPawn->GetMyData_CharacterMaterialSkin());
	Data_CharacterMaterialSkin.Data_Internal = MyPawn->GetMyData_CharacterMaterialSkin();
	// Data_Weapon
	Data_Weapon.Data = TSoftClassPtr<UCsData_Weapon>(MyPawn->GetCurrentData_Weapon());
	Data_Weapon.Data_Internal = MyPawn->GetCurrentData_Weapon();
	// Data_WeaponMaterialSkin
	Data_WeaponMaterialSkin.Data = TSoftClassPtr<UCsData_WeaponMaterialSkin>(MyPawn->GetCurrentData_WeaponMaterialSkin());
	Data_WeaponMaterialSkin.Data_Internal = MyPawn->GetCurrentData_WeaponMaterialSkin();
	
	LoadAnims();
}

// Setup
#pragma region

#if WITH_EDITOR

void UCsAnimInstance_Character::SetupInGameSimulation()
{
	Super::SetupInGameSimulation();

	if (!UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
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
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		OnTick_Handle_Data_Character();
		OnTick_Handle_Data_CharacterMeshSkin();
		OnTick_Handle_Data_CharacterMaterialSkin();
		OnTick_Handle_Data_Weapon();
		OnTick_Handle_Data_WeaponMaterialSkin();

		OnTick_Handle_Weapon(DeltaTimeX);
	}
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

UCsData_Character* UCsAnimInstance_Character::GetData()
{
	return Data_Character.Get();
}

void UCsAnimInstance_Character::LoadData_Character()
{
	const FString& DataString   = NCsAnimInstanceCharacterCached::Str::Data_Character;
	const FString& CsDataString = NCsAnimInstanceCharacterCached::Str::CsData_Character;

	UCsLibrary_Load::LoadTSoftClassPtr(DataString, Data_Character.Data, Data_Character.Data_Internal, CsDataString);

	if (UCsData_Character* MyData_Charater = GetData())
		MyData_Charater->Load(UCsLibrary_Common::ViewTypeToLoadFlags(CurrentViewType));
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

UCsData_CharacterMeshSkin* UCsAnimInstance_Character::GetData_CharacterMeshSkin()
{
	return Data_CharacterMeshSkin.Get();
}

void UCsAnimInstance_Character::LoadData_CharacterMeshSkin()
{
	const FString& DataString   = NCsAnimInstanceCharacterCached::Str::Data_CharacterMeshSkin;
	const FString& CsDataString = NCsAnimInstanceCharacterCached::Str::CsData_CharacterMeshSkin;

	UCsLibrary_Load::LoadTSoftClassPtr(DataString, Data_CharacterMeshSkin.Data, Data_CharacterMeshSkin.Data_Internal, CsDataString);

	if (UCsData_CharacterMeshSkin* MyData_CharacterMeshSkin = GetData_CharacterMeshSkin())
		MyData_CharacterMeshSkin->Load(UCsLibrary_Common::ViewTypeToLoadFlags(CurrentViewType));
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

UCsData_CharacterMaterialSkin* UCsAnimInstance_Character::GetData_CharacterMaterialSkin()
{
	return Data_CharacterMaterialSkin.Get();
}

void UCsAnimInstance_Character::LoadData_CharacterMaterialSkin()
{
	const FString& DataString   = NCsAnimInstanceCharacterCached::Str::Data_CharacterMaterialSkin;
	const FString& CsDataString = NCsAnimInstanceCharacterCached::Str::CsData_CharacterMaterialSkin;

	UCsLibrary_Load::LoadTSoftClassPtr(DataString, Data_CharacterMaterialSkin.Data, Data_CharacterMaterialSkin.Data_Internal, CsDataString);

	if (UCsData_CharacterMaterialSkin* MyData_CharacterMaterialSkin = GetData_CharacterMaterialSkin())
		MyData_CharacterMaterialSkin->Load(UCsLibrary_Common::ViewTypeToLoadFlags(CurrentViewType));
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

UCsData_Weapon* UCsAnimInstance_Character::GetData_Weapon()
{
	return Data_Weapon.Get();
}

void UCsAnimInstance_Character::LoadData_Weapon()
{
	const FString& DataString   = NCsAnimInstanceCharacterCached::Str::Data_Weapon;
	const FString& CsDataString = NCsAnimInstanceCharacterCached::Str::CsData_Weapon;

	UCsLibrary_Load::LoadTSoftClassPtr(DataString, Data_Weapon.Data, Data_Weapon.Data_Internal, CsDataString);

	if (UCsData_Weapon* MyData_Weapon = GetData_Weapon())
		MyData_Weapon->Load(UCsLibrary_Common::ViewTypeToLoadFlags(CurrentViewType));
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

UCsData_WeaponMaterialSkin* UCsAnimInstance_Character::GetData_WeaponMaterialSkin()
{
	return Data_WeaponMaterialSkin.Get();
}

void UCsAnimInstance_Character::LoadData_WeaponMaterialSkin()
{
	const FString& DataString   = NCsAnimInstanceCharacterCached::Str::Data_WeaponMaterialSkin;
	const FString& CsDataString = NCsAnimInstanceCharacterCached::Str::CsData_WeaponMaterialSkin;

	UCsLibrary_Load::LoadTSoftClassPtr(DataString, Data_WeaponMaterialSkin.Data, Data_WeaponMaterialSkin.Data_Internal, CsDataString);

	if (UCsData_WeaponMaterialSkin* MyData_WeaponMaterialSkin = GetData_WeaponMaterialSkin())
		MyData_WeaponMaterialSkin->Load(UCsLibrary_Common::ViewTypeToLoadFlags(CurrentViewType));
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

UAimOffsetBlendSpace* UCsAnimInstance_Character::GetAimOffset(const FECsCharacterBlendSpace &BlendType) const
{
	return nullptr;
}

void UCsAnimInstance_Character::StopAnimation(const FECsCharacterAnim &AnimType, const int32 &Index /*0*/, const float BlendOutTime /*=0.0f*/){}

#pragma endregion Anims