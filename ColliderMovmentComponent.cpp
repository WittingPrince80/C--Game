// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovmentComponent.h"

void UColliderMovmentComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}
   
	FVector DesiredMovment = ConsumeInputVector().GetClampedToMaxSize(2.0f);

	if (!DesiredMovment.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovment, UpdatedComponent->GetComponentRotation(),true,Hit);

		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovment, 1.f - Hit.Time, Hit.Normal, Hit);
			UE_LOG(LogTemp, Warning, TEXT("Slide Mode"))
		}
	}

}