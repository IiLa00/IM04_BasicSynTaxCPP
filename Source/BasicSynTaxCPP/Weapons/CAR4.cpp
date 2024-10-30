#include "CAR4.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "BasicSyntaxCPP.h"
#include "DrawDebugHelpers.h"
#include "CWeaponInterface.h"
#include "UI/CBulletWidget.h"
#include "CBullet.h"
#include "CMagazine.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"

static TAutoConsoleVariable<bool> CVarDrawDebugLine(TEXT("IM.DrawDebug"), false, TEXT(" Visible AR4 Aim Line"),ECVF_Cheat);

ACAR4::ACAR4()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Weapons/Meshes/AR4/SK_AR4");
	MeshComp->SetSkeletalMesh(MeshAsset);

	CHelpers::GetAsset(&EquipMontage, "/Game/Character/Animations/AR4/Rifle_Grab_Montage");
	CHelpers::GetAsset(&UnequipMontage, "/Game/Character/Animations/AR4/Rifle_Ungrab_Montage");
	CHelpers::GetAsset(&ReloadMontage, "/Game/Character/Animations/AR4/Rifle_Jog_Reload_Montage");

	CHelpers::GetClass(&ShakeClass, "/Game/AR4/Shake_Fire");
	CHelpers::GetClass(&BulletClass, "/Game/AR4/BP_CBullet");

	CHelpers::GetClass(&MagazineClass, "/Game/Magazine/BP_Magazine");

	CHelpers::GetAsset(&MuzzleEffect,"/Game/Particles_Rifle/Particles/VFX_Muzzleflash");
	CHelpers::GetAsset(&EjectEffect, "/Game/Particles_Rifle/Particles/VFX_Eject_bullet");
	CHelpers::GetAsset(&ImpactEffect, "/Game/Particles_Rifle/Particles/VFX_Impact_Default");
	CHelpers::GetAsset(&FireSound, "/Game/Sounds/S_RifleShoot_Cue");
	CHelpers::GetAsset(&DecalMaterial, "/Game/Materials/M_Decal");
	
	HolsterSocket = "holster_ar4";
	HandSocket = "hand_ar4";

	MontagesPlayRate = 1.75f;

	ShootRange = 10000.f;

	PitchSpeed = 0.25f;
}

void ACAR4::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	}
}

void ACAR4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bAiming) return;

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);

	if (!OwnerInterface) return;

	FVector Start, End, Direction;
	OwnerInterface->GetAimRay(Start, End, Direction);

	if(CVarDrawDebugLine.GetValueOnGameThread())
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.f, 0, 3.f);
	

	FHitResult Hit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(OwnerCharacter);

	if (GetWorld()->LineTraceSingleByChannel
	(
		Hit,
		Start,
		End,
		ECC_PhysicsBody,
		QueryParams
	))
	{
		if (Hit.GetComponent()->IsSimulatingPhysics())
		{
			OwnerInterface->OnTarget();
			return;
		}
			
	}

	OwnerInterface->OffTarget();
}

void ACAR4::ToggleAutoFiring()
{
	bAutoFiring = !bAutoFiring;
}

void ACAR4::EnableAim()
{ 
	bAiming = true; 
}

void ACAR4::DisableAim() 
{ 
	bAiming = false; 
}

void ACAR4::Equip()
{
	if (bEquipped) return;
	if (bPlayingMontage) return;
	if (bReloading) return;

	bPlayingMontage = true;

	OwnerCharacter->PlayAnimMontage(EquipMontage, MontagesPlayRate);
}

void ACAR4::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void ACAR4::End_Equip()
{
	bPlayingMontage = false;

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ACAR4::Unequip()
{
	if (!bEquipped) return;
	if (bPlayingMontage) return;

	if(bAutoFiring)
		OffFire();

	bPlayingMontage = true;

	OwnerCharacter->PlayAnimMontage(UnequipMontage, MontagesPlayRate);
}

void ACAR4::Begin_Unequip()
{
	bEquipped = false;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACAR4::End_Unequip()
{
	bPlayingMontage = false;
}

void ACAR4::Reload()
{
	if (!bEquipped) return;
	if (bPlayingMontage) return;
	if (bReloading) return;

	bPlayingMontage = true;

	OwnerCharacter->PlayAnimMontage(ReloadMontage, 1.f);
}

void ACAR4::Begin_Reload()
{
	bReloading = true;
}

void ACAR4::End_Reload()
{

	bReloading = false;
	bPlayingMontage = false;
}

void ACAR4::Begin_Magazine()
{
	GetMesh()->HideBoneByName("b_gun_mag", EPhysBodyOp::PBO_None);

	FTransform Tf = GetMesh()->GetSocketTransform("b_gun_mag");
	ACMagazine* Magazine = GetWorld()->SpawnActor<ACMagazine>(MagazineClass, Tf);

	if (!Magazine) return;

	Magazine->MeshComp->SetSimulatePhysics(true);
	Magazine->SetLifeSpan(1.f);
	
}

void ACAR4::End_Magazine()
{
	GetMesh()->UnHideBoneByName("b_gun_mag");

	if (Hand_Magazine)
	{
		Hand_Magazine->DetachAllSceneComponents(OwnerCharacter->GetMesh(), FDetachmentTransformRules::KeepRelativeTransform);
		Hand_Magazine->Destroy();
	}
		
	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);

	if (!OwnerInterface) return;

	OwnerInterface->GetBulletWidget()->Reload();
}

void ACAR4::Spawn_Magazine()
{
	Hand_Magazine = GetWorld()->SpawnActor<ACMagazine>(MagazineClass);

	if (!Hand_Magazine) return;

	Hand_Magazine->SetActorEnableCollision(false);
	Hand_Magazine->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "ring_01_l");
}

void ACAR4::OnFire()
{
	if (!bEquipped) return;
	if (bPlayingMontage) return;
	//if (!bAiming) return;
	if (bFiring) return;
	if (bReloading) return;

	bFiring = true;

	CurrentPitch = 0.f;

	if (bAutoFiring)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoFireTimer, this, &ACAR4::Firing_Internal, 0.1f, true, 0.f);
		return;
	}
		
	Firing_Internal();
}

void ACAR4::OffFire()
{
	bFiring = false;

	if (bAutoFiring)
		GetWorld()->GetTimerManager().ClearTimer(AutoFireTimer);
}

void ACAR4::Firing_Internal()
{
	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);
	if (!OwnerInterface) return;

	UCBulletWidget* BulletWidget = OwnerInterface->GetBulletWidget();

	if (!(BulletWidget->IsShoot()))
	{
		Reload();
		return;
	}
	BulletWidget->Shooting();

	FVector Start, End, Direction;
	OwnerInterface->GetAimRay(Start, End, Direction);

	if (!OwnerCharacter) return;
	APlayerController* PC = OwnerCharacter->GetController<APlayerController>();

	if (PC)
		PC->PlayerCameraManager->PlayCameraShake(ShakeClass);
	
	FVector MuzzleLocation = MeshComp->GetSocketLocation("b_gun_muzzleflash");
	if (BulletClass)
		GetWorld()->SpawnActor<ACBullet>(BulletClass, MuzzleLocation, Direction.Rotation());

	UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, "MuzzleFlash");
	UGameplayStatics::SpawnEmitterAttached(EjectEffect, MeshComp, "EjectBullet");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, MuzzleLocation);

	CurrentPitch -= PitchSpeed * GetWorld()->GetDeltaSeconds();

	if (CurrentPitch > -CurrentPitch)
		OwnerCharacter->AddControllerPitchInput(CurrentPitch);
	
	
	FHitResult Hit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(OwnerCharacter);

	if (GetWorld()->LineTraceSingleByChannel
	(
		Hit,
		Start,
		End,
		ECollisionChannel::ECC_Visibility,
		QueryParams
	))
	{
		FRotator ImpactRotation = Hit.ImpactNormal.Rotation();

		UDecalComponent* DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), Hit.ImpactPoint, ImpactRotation, 3.f);
		DecalComp->SetFadeScreenSize(0);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, ImpactRotation);

		UPrimitiveComponent* HitComp = Hit.GetComponent();
		if (Hit.GetComponent()->IsSimulatingPhysics())
		{
			Direction = Hit.GetActor()->GetActorLocation() - OwnerCharacter->GetActorLocation();
			Direction.Normalize();

			HitComp->AddImpulseAtLocation(Direction * 3000.f, OwnerCharacter->GetActorLocation());
		}
	}

	
}

