#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapons/CWeaponInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACAR4;
class UCAimWidget;
class UCGameInfoWidget;
class UCBulletWidget;

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
	FORCEINLINE void GetAimRay(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection) override;

	FORCEINLINE UCBulletWidget* GetBulletWidget() override { return BulletWidget; }

	void OnTarget() override;
	void OffTarget() override;

	
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void ZoomIn();

	UFUNCTION(BlueprintImplementableEvent)
		void ZoomOut();

	UFUNCTION(Exec)
		void AddLaunch(float Height = 1000.f);

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void OnRifle();

	void OnFire();
	void OffFire();

	void OnAim();
	void OffAim();

	void OnAutoFire();

	void OnReload();

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

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		TSubclassOf<ACAR4> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UCAimWidget> AimWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UCGameInfoWidget> GameInfoWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> BulletWidgetClass;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	ACAR4* AR4;

	UCAimWidget* AimWidget;
	UCBulletWidget* BulletWidget;
	UCGameInfoWidget* GameInfoWidget;
};
