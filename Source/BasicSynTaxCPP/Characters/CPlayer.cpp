#include "CPlayer.h"
#include "BasicSyntaxCPP.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Weapons/CAR4.h"


ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Camera Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 60));
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
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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