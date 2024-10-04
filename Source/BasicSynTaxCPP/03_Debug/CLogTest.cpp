
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

	CLog::Log(20);
	CLog::Log(PI);
	CLog::Log("Log Test");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());
	CLog::Log(this);
	CLog::Log(__FILE__);
	//CLog::Log(__FUNCTION__, __LINE__);
	PrintLine();
	CLog::Log(GetClass()->GetName());
}

void ACLogTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	CLog::Print(GetWorld()->TimeSeconds, 500,2.f,FColor::Green);

}

