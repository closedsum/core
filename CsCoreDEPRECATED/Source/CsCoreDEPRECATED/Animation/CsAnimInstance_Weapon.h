#pragma once
#include "Animation/CsAnimInstance.h"
#include "Animation/CsTypes_AnimInstance_Weapon.h"
#include "CsTypes_Weapon.h"
#include "CsAnimInstance_Weapon.generated.h"

class ACsWeapon_DEPRECATED;
class UCsData_Weapon_DEPRECATED;
class UCsData_WeaponMaterialSkin;
class UAnimMontage;
class UAnimSequence;
class UBlendSpace;

UCLASS()
class CSCOREDEPRECATED_API UCsAnimInstance_Weapon : public UCsAnimInstance
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

	TWeakObjectPtr<ACsWeapon_DEPRECATED> Weapon;

	ACsWeapon_DEPRECATED* GetWeapon();

	template<typename T>
	T* GetWeapon()
	{
		return Cast<T>(GetWeapon());
	}

	TSubclassOf<ACsWeapon_DEPRECATED> WeaponClass;

	virtual void ApplyData_Weapon();

#endif // #if WITH_EDITOR

#pragma endregion Setup

	//virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	// Data
#pragma region
public:

	// Weapon

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_WeaponPtr Data_Weapon;

	UCsData_Weapon_DEPRECATED* GetData_Weapon();

	template<typename T>
	T* GetData_Weapon()
	{
		return Cast<T>(GetData_Weapon());
	}

#if WITH_EDITOR
	void OnTick_Handle_Data_Weapon();
#endif // #if WITH_EDITOR

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_WeaponMaterialSkinPtr Data_WeaponMaterialSkin;

	UCsData_WeaponMaterialSkin* GetData_WeaponMaterialSkin();

	template<typename T>
	T* GetData_WeaponMaterialSkin()
	{
		return Cast<T>(GetData_WeaponMaterialSkin());
	}

#if WITH_EDITOR
	void OnTick_Handle_Data_WeaponMaterialSkin();
#endif // #if WITH_EDITOR

#pragma endregion Data

	// Anims
#pragma region
public:

	virtual void LoadAnims();

	UFUNCTION(BlueprintCallable, Category = "Weapon AnimInstance", meta = (BlueprintThreadSafe, AutoCreateRefTerm = "AnimType,Index"))
	virtual UAnimMontage* GetAnimMontage(const FECsWeaponAnim& AnimType, const int32& Index = 0) const;
	UFUNCTION(BlueprintCallable, Category = "Weapon AnimInstance", meta = (BlueprintThreadSafe, AutoCreateRefTerm = "AnimType"))
	virtual UAnimSequence* GetAnimSequence(const FECsWeaponAnim& AnimType) const;
	UFUNCTION(BlueprintCallable, Category = "Weapon AnimInstance", meta = (BlueprintThreadSafe, AutoCreateRefTerm = "BlendType"))
	virtual UBlendSpace* GetBlendSpace(const FECsWeaponBlendSpace& BlendType) const;

	UFUNCTION(BlueprintCallable, Category = "AI Weapon AnimInstance")
	virtual void StopAnimation(const FECsWeaponAnim& AnimType, const int32& Index = 0, const float BlendOutTime = 0.0f);

#pragma endregion Anims

#pragma endregion Event Graph
};