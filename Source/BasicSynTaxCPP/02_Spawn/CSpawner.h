
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawner.generated.h"

class ACStaticMeshActorBase;

UENUM(BlueprintType)
enum class EStaticMeshAssetType : uint8
{
	Cube,Cone,Cylinder,Sphere,Max
};

UCLASS()
class BASICSYNTAXCPP_API ACSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpawner();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
		UClass* ObjectBasedClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ACStaticMeshActorBase> StaticMeshBasedClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ACStaticMeshActorBase> StaticMeshBasedClasses[(int32)EStaticMeshAssetType::Max];

private:
	ACStaticMeshActorBase* StaticMeshBased[(int32)EStaticMeshAssetType::Max];


};
