

#include "CProperty.h"

ACProperty::ACProperty()
{
	PrimaryActorTick.bCanEverTick = true;

	NumB = 999;

	// When this construct is called
	GLog->Log("ACProperty::ACProperty()");

}

void ACProperty::BeginPlay()
{
	Super::BeginPlay();

	FString Message;
	//Message.Append("NumA = ");
	//Message.Append(FString::FromInt(NumA));

	Message = FString::Printf(TEXT("NumA = %d, NumB = %d, NumC = %d"), NumA, NumB, NumC);

	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::White,Message);
}

void ACProperty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

