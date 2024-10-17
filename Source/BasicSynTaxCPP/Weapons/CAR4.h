#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAR4.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACAR4 : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAR4();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsPlayingMontage() { return bPlayingMontage; }

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* MeshComp;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket;

private:
	bool bEquipped;
	bool bPlayingMontage;

};
