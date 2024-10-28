#include "CAnimNotifyState_Reloading.h"
#include "Weapons/CWeaponInterface.h"
#include "Weapons/CAR4.h"

FString UCAnimNotifyState_Reloading::GetNotifyName_Implementation() const
{
	return "Reloading";
}

void UCAnimNotifyState_Reloading::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if (AR4)
			AR4->Begin_Reload();
	}
}

void UCAnimNotifyState_Reloading::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if (AR4)
			AR4->End_Reload();
	}

}