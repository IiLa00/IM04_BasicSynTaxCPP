#include "CAnimInstance.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!TryGetPawnOwner())
		return;

	Speed = TryGetPawnOwner()->GetVelocity().Size2D();
}