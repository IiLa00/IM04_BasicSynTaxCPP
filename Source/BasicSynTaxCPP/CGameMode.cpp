#include "CGameMode.h"
#include "Characters/CPlayer.h"

ACGameMode::ACGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> PlayerClass(TEXT("Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"));
	
	if (PlayerClass.Succeeded())
		DefaultPawnClass = PlayerClass.Class;
}
