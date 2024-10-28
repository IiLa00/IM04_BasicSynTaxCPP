#include "CAnimNotifyState_Magazine.h"
#include "Weapons/CWeaponInterface.h"
#include "Weapons/CAR4.h"

FString UCAnimNotifyState_Magazine::GetNotifyName_Implementation() const
{
	return "Magazine";
}

void UCAnimNotifyState_Magazine::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if (AR4)
			AR4->Begin_Magazine();
	}

	
}

void UCAnimNotifyState_Magazine::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if (AR4)
			AR4->End_Magazine();
	}

}