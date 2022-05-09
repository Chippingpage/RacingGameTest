// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UHoverComponent::UHoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TraceLength = 100.f;
	HoverForce = 100000.f;
	Gravity = 9.81f;
}


// Called when the game starts
void UHoverComponent::BeginPlay()
{
	Super::BeginPlay();

	MeshComp = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	
}


// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult OutHit;
	FVector Start = GetComponentLocation();
	FVector End = Start + (GetUpVector() * (-TraceLength));

	FCollisionQueryParams CollisionParams = FCollisionQueryParams();
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bTraceComplex = true;

	bool bHit = (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams));
	if (bHit) {
		// Hit Information.
		FVector SurfaceImpactNormal = OutHit.ImpactNormal;
		FVector HitLocation = OutHit.Location;

		// Get Length between hit and component.
		FVector WorldLocation = (HitLocation - GetComponentLocation());
		float VectorLength = WorldLocation.Size();
		

		// Value from 0 - 1.
		float Alpha = (VectorLength / TraceLength);
		

		// Linear interpolation between two values, functions as suspension.
		float CompressionRatio = FMath::Lerp(HoverForce, 0.f, Alpha);


		// Add force to Component Location
		FVector Force = (CompressionRatio * SurfaceImpactNormal);
		MeshComp->AddForceAtLocation(Force, GetComponentLocation());
	}

	else
	{
		MeshComp->AddForce(FVector(0.f, 0.f, -1) * (Gravity * 10000));
	
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, -1, 0, 3);
}



