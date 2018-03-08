#pragma once
#include "Animation/CsAnimInstance.h"
#include "Types/CsTypes_AnimInstance.h"
#include "Types/CsTypes_Weapon.h"
#include "CsAnimInstance_Weapon.generated.h"

UCLASS()
class CSCORE_API UCsAnimInstance_Weapon : public UCsAnimInstance
{
	GENERATED_UCLASS_BODY()

// Event Graph
#pragma region
public:

	virtual void NativeInitializeAnimation() override;

	// Setup
#pragma region
public:

#if WITH_EDITOR
	virtual void SetupInGameSimulation() override;
#endif // #if WITH_EDITOR

	TWeakObjectPtr<class ACsWeapon> Weapon;

	class ACsWeapon* GetWeapon();

	template<typename T>
	T* GetWeapon()
	{
		return Cast<T>(GetWeapon());
	}

	TSubclassOf<class ACsWeapon> WeaponClass;

	virtual void ApplyData_Weapon();

#pragma endregion Setup

	//virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	// Data
#pragma region
public:

	// Weapon

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_WeaponPtr Data_Weapon;

	class ACsData_Weapon* GetData_Weapon();

	template<typename T>
	T* GetData_Weapon()
	{
		return Cast<T>(GetData_Weapon());
	}

	void OnTick_Handle_Data_Weapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_WeaponMaterialSkinPtr Data_WeaponMaterialSkin;

	class ACsData_WeaponMaterialSkin* GetData_WeaponMaterialSkin();

	template<typename T>
	T* GetData_WeaponMaterialSkin()
	{
		return Cast<T>(GetData_WeaponMaterialSkin());
	}

	void OnTick_Handle_Data_WeaponMaterialSkin();

#pragma endregion Data

	// Anims
#pragma region
public:

	virtual void LoadAnims();

	virtual class UAnimMontage* GetAnimMontage(const TCsWeaponAnim &AnimType, const int32 &Index = 0) const;
	virtual class UAnimSequence* GetAnimSequence(const TCsWeaponAnim &AnimType) const;
	virtual class UBlendSpace* GetBlendSpace(const TCsWeaponBlendSpace &BlendType) const;

	virtual void StopAnimation(const TCsWeaponAnim &AnimType, const int32 &Index = 0, const float BlendOutTime = 0.0f);

#pragma endregion Anims

#pragma endregion Event Graph
};