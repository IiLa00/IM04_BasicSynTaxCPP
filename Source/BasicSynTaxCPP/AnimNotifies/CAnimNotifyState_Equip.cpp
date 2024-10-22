#include "CAnimNotifyState_Equip.h"
#include "Weapons/CWeaponInterface.h"
#include "Weapons/CAR4.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);


	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if(AR4)
			AR4->Begin_Equip();
	}
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if (AR4)
			AR4->End_Equip();
	}
}
