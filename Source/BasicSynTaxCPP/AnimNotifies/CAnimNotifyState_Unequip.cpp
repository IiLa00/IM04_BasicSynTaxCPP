#include "CAnimNotifyState_Unequip.h"
#include "Weapons/CWeaponInterface.h"
#include "Weapons/CAR4.h"

FString UCAnimNotifyState_Unequip::GetNotifyName_Implementation() const
{
	return "Unequip";
}

void UCAnimNotifyState_Unequip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);


	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if(AR4)
			AR4->Begin_Unequip();
	}
}

void UCAnimNotifyState_Unequip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if (AR4)
			AR4->End_Unequip();
	}
}
