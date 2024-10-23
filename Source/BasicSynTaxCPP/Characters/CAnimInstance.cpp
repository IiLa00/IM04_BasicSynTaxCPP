#include "CAnimInstance.h"
#include "Weapons/CWeaponInterface.h"
#include "Weapons/CAR4.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!TryGetPawnOwner())
		return;

	Speed = TryGetPawnOwner()->GetVelocity().Size2D();
	Direction = CalculateDirection(TryGetPawnOwner()->GetVelocity(), TryGetPawnOwner()->GetControlRotation());
	Pitch = TryGetPawnOwner()->GetBaseAimRotation().Pitch;

	ICWeaponInterface* Owner = Cast<ICWeaponInterface>(TryGetPawnOwner());

	if (Owner && Owner->GetWeapon())
	{
		bEquipped = Owner->GetWeapon()->IsEquipped();
		bAiming = Owner->GetWeapon()->IsAiming();
	}
		
}