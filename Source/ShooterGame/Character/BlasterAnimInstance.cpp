// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	//A Prefix: In Unreal Engine, classes that derive from AActor are typically prefixed with A.
	//This prefix helps to distinguish actor classes from other types of classes in Unreal,
	//such as UObject-derived classes (which have a U prefix) or other types.
	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	/*if(!BlasterCharacter)
	{
		BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
	}*/

	if(!BlasterCharacter) return;
	
	// Get the velocity of the BlasterCharacter
	FVector Velocity = BlasterCharacter->GetVelocity();
	// Set the Z component of the velocity to 0 (ignore vertical movement)
	Velocity.Z = 0.f;
	// Calculate the speed (magnitude) of the horizontal velocity
	Speed = Velocity.Size();

	bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();

	// Unity Equivalent: `isAccelerating = rb.velocity.magnitude > 0.1f;`
	bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
}
