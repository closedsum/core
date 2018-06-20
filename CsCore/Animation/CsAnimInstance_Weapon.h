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

	TWeakObjectPtr<class ACsWeapon> Weapon;

	class ACsWeapon* GetWeapon();

	template<typename T>
	T* GetWeapon()
	{
		return Cast<T>(GetWeapon());
	}

	TSubclassOf<class ACsWeapon> WeaponClass;

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

	class ACsData_Weapon* GetData_Weapon();

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

	class ACsData_WeaponMaterialSkin* GetData_WeaponMaterialSkin();

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

	UFUNCTION(BlueprintCallable, Category = "Weapon AnimInstance", meta = (BlueprintThreadSafe, AutoCreateRefTerm = "AnimType"))
	virtual class UAnimMontage* GetAnimMontage(const FECsWeaponAnim &AnimType, const int32 &Index = 0) const;
	UFUNCTION(BlueprintCallable, Category = "Weapon AnimInstance", meta = (BlueprintThreadSafe, AutoCreateRefTerm = "AnimType"))
	virtual class UAnimSequence* GetAnimSequence(const FECsWeaponAnim &AnimType) const;
	UFUNCTION(BlueprintCallable, Category = "Weapon AnimInstance", meta = (BlueprintThreadSafe, AutoCreateRefTerm = "BlendType"))
	virtual class UBlendSpace* GetBlendSpace(const FECsWeaponBlendSpace &BlendType) const;

	UFUNCTION(BlueprintCallable, Category = "AI Weapon AnimInstance")
	virtual void StopAnimation(const FECsWeaponAnim &AnimType, const int32 &Index = 0, const float BlendOutTime = 0.0f);

#pragma endregion Anims

#pragma endregion Event Graph
};