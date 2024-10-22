#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapons/CWeaponInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACAR4;

UCLASS()
class BASICSYNTAXCPP_API ACPlayer : public ACharacter, public ICWeaponInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE ACAR4* GetWeapon() override { return AR4; }

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void ZoomIn();

	UFUNCTION(BlueprintImplementableEvent)
		void ZoomOut();

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void OnRifle();

	void OnAim();
	void OffAim();

public:
	UFUNCTION(BlueprintCallable)
		void SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

	UFUNCTION(BlueprintCallable)
		void ResetBodyColor();
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UStaticMeshComponent* BackPackComp;

	UPROPERTY(EditDefaultsOnly, Category = "Class")
		TSubclassOf<ACAR4> WeaponClass;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	ACAR4* AR4;
};
