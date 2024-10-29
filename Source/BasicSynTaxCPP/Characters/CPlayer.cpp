#include "CPlayer.h"
#include "BasicSyntaxCPP.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Weapons/CAR4.h"
#include "Blueprint/UserWidget.h"
#include "UI/CAimWidget.h"
#include "UI/CGameInfoWidget.h"
#include "UI/CBulletWidget.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Camera Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 60));
	SpringArmComp->SocketOffset = FVector(0, 60, 0);
	SpringArmComp->TargetArmLength = 200.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	// Set Skeletal Mesh Asset
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Character/Mesh/SK_Mannequin"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

		ConstructorHelpers::FClassFinder<UAnimInstance> AnimClass(TEXT("/Game/Player/ABP_CPlayer"));

		if(AnimClass.Succeeded())
			GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}
		
	BackPackComp = CreateDefaultSubobject<UStaticMeshComponent>("BackPackComp");

	ConstructorHelpers::FObjectFinder<UStaticMesh> BackpackMeshAsset(TEXT("/Game/StaticMeshes/Backpack/Backpack"));

	if (BackpackMeshAsset.Succeeded())
		BackPackComp->SetStaticMesh(BackpackMeshAsset.Object);

	BackPackComp->SetupAttachment(GetMesh(), "backpack");

	CHelpers::GetClass(&WeaponClass, "/Game/AR4/BP_CAR4");

	// Character Movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	CHelpers::GetClass(&AimWidgetClass, "/Game/UI/WB_Aim");
	CHelpers::GetClass(&GameInfoWidgetClass, "/Game/UI/WB_GameInfo");
	CHelpers::GetClass(&BulletWidgetClass, "/Game/UI/WB_Bullet");
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	BodyMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);
	
	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	AR4 = GetWorld()->SpawnActor<ACAR4>(WeaponClass, SpawnParam);

	AimWidget = CreateWidget<UCAimWidget>(GetController<APlayerController>(), AimWidgetClass);
	AimWidget->AddToViewport();
	AimWidget->SetVisibility(ESlateVisibility::Hidden);
	

	GameInfoWidget = CreateWidget<UCGameInfoWidget>(GetController<APlayerController>(), GameInfoWidgetClass);
	GameInfoWidget->AddToViewport();
	
	BulletWidget = CreateWidget<UCBulletWidget>(GetController<APlayerController>(), BulletWidgetClass);
	BulletWidget->AddToViewport();
	BulletWidget->SetVisibility(ESlateVisibility::Hidden);
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!(GetBulletWidget()->IsShoot()))
		OnReload();

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRifle);

	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ACPlayer::OnFire);
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Released, this, &ACPlayer::OffFire);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);

	PlayerInputComponent->BindAction("AutoFire", EInputEvent::IE_Pressed, this, &ACPlayer::OnAutoFire);

	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ACPlayer::OnReload);

}

void ACPlayer::AddLaunch(float Height)
{
	FVector Current = GetActorLocation();
	TeleportTo(Current + FVector(0, 0, Height), GetActorRotation());
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetForwardVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetRightVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

void ACPlayer::OnRifle()
{
	if (AR4->IsEquipped())
	{
		if(AR4->IsAiming())
			OffAim();

		AR4->Unequip();

		GetBulletWidget()->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	AR4->Equip();

	GetBulletWidget()->SetVisibility(ESlateVisibility::Visible);

}

void ACPlayer::OnFire()
{
	AR4->OnFire();
}

void ACPlayer::OffFire()
{
	AR4->OffFire();
}

void ACPlayer::OnAim()
{
	if (!AR4->IsEquipped()) return;
	if (AR4->IsPlayingMontage()) return;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArmComp->TargetArmLength = 100.f;
	SpringArmComp->SocketOffset = FVector(0, 30, 10);

	AR4->EnableAim();

	ZoomIn();

	if(AimWidget)
		AimWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void ACPlayer::OffAim()
{
	if (!AR4->IsEquipped()) return;
	if (AR4->IsPlayingMontage()) return;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->SocketOffset = FVector(0, 60, 0);

	AR4->DisableAim();

	ZoomOut();

	if (AimWidget)
		AimWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ACPlayer::OnAutoFire()
{
	if (AR4->IsFiring()) return;
	
	AR4->ToggleAutoFiring();

	AR4->IsAutoFiring() ? GameInfoWidget->EnableAutoFire() : GameInfoWidget->DisableAutoFire();
}

void ACPlayer::OnReload()
{
	OffAim();

	AR4->OffFire();
	
	AR4->Reload();
}

void ACPlayer::SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InBodyColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InLogoColor);
}

void ACPlayer::ResetBodyColor()
{
	SetBodyColor(FLinearColor(0.45098f, 0.403922f, 0.360784f), FLinearColor(0.45098f, 0.403922f, 0.360784f));
}

void ACPlayer::GetAimRay(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection)
{
	OutAimDirection = CameraComp->GetForwardVector();

	FVector CamLoc = CameraComp->GetComponentToWorld().GetLocation();
	FVector MuzzleLoc = AR4->GetMesh()->GetSocketLocation("MuzzleFlash");
	
	float Projected = (MuzzleLoc - CamLoc) | OutAimDirection;

	OutAimStart = CamLoc + OutAimDirection * Projected;

	FVector RandomConeDegree = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(OutAimDirection, 0.2f);

	RandomConeDegree *= AR4->GetShootRange();

	OutAimEnd = OutAimStart + RandomConeDegree;
	
}

void ACPlayer::OnTarget()
{
	AimWidget->OnTarget();
}

void ACPlayer::OffTarget()
{
	AimWidget->OffTarget();
}
