#include "CAR4.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "BasicSyntaxCPP.h"

ACAR4::ACAR4()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Weapons/Meshes/AR4/SK_AR4");
	MeshComp->SetSkeletalMesh(MeshAsset);

	HolsterSocket = "holster_ar4";
	HandSocket = "hand_ar4";
}

void ACAR4::BeginPlay()
{
	Super::BeginPlay();
	
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	}
	
}

void ACAR4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

