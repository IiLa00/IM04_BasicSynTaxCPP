#include "CAnimNotify_SpawnMagazine.h"
#include "Weapons/CWeaponInterface.h"
#include "Weapons/CAR4.h"

FString UCAnimNotify_SpawnMagazine::GetNotifyName_Implementation() const
{
	return "SpawnMagazine";
}

void UCAnimNotify_SpawnMagazine::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if (AR4)
			AR4->Spawn_Magazine();
	}
}