#include "CAR4.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "BasicSyntaxCPP.h"
#include "DrawDebugHelpers.h"
#include "CWeaponInterface.h"

ACAR4::ACAR4()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Weapons/Meshes/AR4/SK_AR4");
	MeshComp->SetSkeletalMesh(MeshAsset);

	CHelpers::GetAsset(&EquipMontage, "/Game/Character/Animations/AR4/Rifle_Grab_Montage");
	CHelpers::GetAsset(&UnequipMontage, "/Game/Character/Animations/AR4/Rifle_Ungrab_Montage");

	HolsterSocket = "holster_ar4";
	HandSocket = "hand_ar4";

	MontagesPlayRate = 1.75f;

	ShootRange = 10000.f;
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

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.f, 0, 3.f);


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
}

void ACAR4::End_Unequip()
{
	bPlayingMontage = false;
}

