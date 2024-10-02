
#include "CLogTest.h"
#include "Utilities/CLog.h"

ACLogTest::ACLogTest()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACLogTest::BeginPlay()
{
	Super::BeginPlay();
	
	CLog::Print(1);
	CLog::Print(2,1);
	CLog::Print(3, 2, 10.f);
	CLog::Print(4, 2, 10.f);
	CLog::Print(4, 2, 10.f,FColor::Red);
	CLog::Print("Test");
	CLog::Print(GetActorLocation());
	CLog::Print(GetActorRotation());
}

void ACLogTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

