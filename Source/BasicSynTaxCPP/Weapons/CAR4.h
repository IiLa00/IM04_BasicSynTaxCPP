#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAR4.generated.h"

class UAnimMontage;
class ACharacter;
class UCBulletWidget;
class ACBullet;
class ACMagazine;
class UParticleSystem;
class USoundCue;


UCLASS()
class BASICSYNTAXCPP_API ACAR4 : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAR4();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsPlayingMontage() { return bPlayingMontage; }
	FORCEINLINE bool IsAiming() { return bAiming; }
	FORCEINLINE bool IsFiring() { return bFiring; }
	FORCEINLINE bool IsAutoFiring() { return bAutoFiring; }
	void ToggleAutoFiring();

	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }
	FORCEINLINE float GetShootRange() { return ShootRange; }

	void EnableAim();
	void DisableAim();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void Reload();
	void Begin_Reload();
	void End_Reload();

	void Begin_Magazine();
	void End_Magazine();

	void Spawn_Magazine();

public:
	void OnFire();
	void OffFire();

private:
	UFUNCTION()
		void Firing_Internal();
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* MeshComp;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* UnequipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* ReloadMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		float MontagesPlayRate;

	UPROPERTY(EditDefaultsOnly, Category = "Range")
		float ShootRange;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
		TSubclassOf<UCameraShake> ShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		TSubclassOf<ACBullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		UParticleSystem* EjectEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		UMaterial* DecalMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		float PitchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
		TSubclassOf<ACMagazine> MagazineClass;

private:
	ACharacter* OwnerCharacter;
	ACMagazine* Hand_Magazine;

	bool bEquipped;
	bool bPlayingMontage;
	bool bAiming;
	bool bFiring;
	bool bAutoFiring;
	bool bReloading;

	FTimerHandle AutoFireTimer;

	float CurrentPitch;

};