// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntersectionType.h"
#include "GameFramework/Actor.h"
#include "IntersectionDemonstrator.generated.h"

UCLASS()
class MATHASSIGNMENTS_API AIntersectionDemonstrator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntersectionDemonstrator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EIntersectionType> IntersectionType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition = "IntersectionType == EIntersectionType::Sphere", EditConditionHides))
	float Radius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition = "IntersectionType == EIntersectionType::AABB", EditConditionHides))
	FVector Min;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition = "IntersectionType == EIntersectionType::AABB", EditConditionHides))
	FVector Max;

	FColor Color = FColor::Green;
	
	void DrawShape() const;
};
