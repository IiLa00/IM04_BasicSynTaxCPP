#include "CAR4.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "BasicSyntaxCPP.h"
#include "DrawDebugHelpers.h"
#include "CWeaponInterface.h"
#include "UI/CBulletWidget.h"

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

	HolsterSocket = "holster_ar4";
	HandSocket = "hand_ar4";

	MontagesPlayRate = 1.75f;

	ShootRange = 10000.f;

	CHelpers::GetClass(&ShakeClass, "/Game/AR4/Shake_Fire");

	CHelpers::GetClass(&MagazineClass, "/Game/Magazine/BP_Magazine");

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

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);

	if (!OwnerInterface) return;

	UCBulletWidget* BulletWidget = OwnerInterface->GetBulletWidget();
	BulletWidget->SetVisibility(ESlateVisibility::Visible);
}

void ACAR4::End_Equip()
{
	bPlayingMontage = false;
}

void ACAR4::Unequip()
{
	if (!bEquipped) return;
	if (bPlayingMontage) return;

	bPlayingMontage = true;

	OwnerCharacter->PlayAnimMontage(UnequipMontage, MontagesPlayRate);
}

void ACAR4::Begin_Unequip()
{
	bEquipped = false;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);

	if (!OwnerInterface) return;

	UCBulletWidget* BulletWidget = OwnerInterface->GetBulletWidget();
	BulletWidget->SetVisibility(ESlateVisibility::Hidden);
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

	OwnerCharacter->PlayAnimMontage(ReloadMontage, MontagesPlayRate);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);

	if (!OwnerInterface) return;

	UCBulletWidget* BulletWidget = OwnerInterface->GetBulletWidget();
	BulletWidget->Reload();
}

void ACAR4::Begin_Reload()
{
	// 재장전상태 돌입
	
	bReloading = true;
}

void ACAR4::End_Reload()
{
	// 재장전 상태 끝, 막은 것(줌인, 1번) 풀기

	bReloading = false;
	bPlayingMontage = false;
}

void ACAR4::Begin_Magazine()
{
	//  장탄 수 초기화?, 기존 탄창 떨어트리고 숨기기

	GetMesh()->HideBoneByName("b_gun_mag", EPhysBodyOp::PBO_None);

	FTransform HandTF = GetMesh()->GetSocketTransform("hand_r");
	AActor* Magazine = GetWorld()->SpawnActor<AActor>(MagazineClass, HandTF);

	if (!Magazine) return;

}

void ACAR4::End_Magazine()
{
	// 스폰된 탄창 삭제 / 기존 탄창 숨기기 풀기 / 총알 수 늘리기

}

void ACAR4::OnFire()
{
	if (!bEquipped) return;
	if (bPlayingMontage) return;
	if (!bAiming) return;
	if (bFiring) return;
	if (bReloading) return;

	bFiring = true;

	Firing_Internal();

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);

	if (!OwnerInterface) return;

	UCBulletWidget* BulletWidget = OwnerInterface->GetBulletWidget();
	BulletWidget->Shooting();
}

void ACAR4::OffFire()
{
	bFiring = false;
}

void ACAR4::Firing_Internal()
{
	if (!OwnerCharacter) return;
	APlayerController* PC = OwnerCharacter->GetController<APlayerController>();

	if (PC)
		PC->PlayerCameraManager->PlayCameraShake(ShakeClass);
	

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);
	if (!OwnerInterface) return;

	FVector Start, End, Direction;
	OwnerInterface->GetAimRay(Start, End, Direction);

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
		UPrimitiveComponent* HitComp = Hit.GetComponent();
		if (Hit.GetComponent()->IsSimulatingPhysics())
		{
			Direction = Hit.GetActor()->GetActorLocation() - OwnerCharacter->GetActorLocation();
			Direction.Normalize();

			HitComp->AddImpulseAtLocation(Direction * 3000.f, OwnerCharacter->GetActorLocation());
		}
	}
}

