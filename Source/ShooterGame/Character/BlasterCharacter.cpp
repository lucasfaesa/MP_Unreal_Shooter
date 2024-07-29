// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABlasterCharacter::ABlasterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Unity Equivalent: `CameraBoom = new GameObject("CameraBoom").AddComponent<SpringArm>();`
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// Unity Equivalent: `CameraBoom.transform.parent = this.transform;`
	CameraBoom->SetupAttachment(GetMesh());
	// Unity Equivalent: `CameraBoom.targetDistance = 600f;` (or similar depending on the implementation)
	CameraBoom->TargetArmLength = 600.f;
	// Unity Equivalent: `CameraBoom.useFollowRotation = true;`
	CameraBoom->bUsePawnControlRotation = true;

	// Unity Equivalent: `FollowCamera = new GameObject("FollowCamera").AddComponent<Camera>();`
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Unity Equivalent: `FollowCamera.transform.parent = CameraBoom.transform;`
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Unity Equivalent: `FollowCamera.useFollowRotation = false;`
	FollowCamera->bUsePawnControlRotation = false;

	/*This property determines whether the character should rotate based on the controller's yaw
	 *(horizontal rotation). Setting it to false means that the character's yaw rotation is not
	 *controlled by the player's input. Instead, it will be controlled by other means, such as
	 *animations or manual adjustments in code.*/
	bUseControllerRotationYaw = false;

	/*When bOrientRotationToMovement is true, the character will
	 *automatically rotate to face the direction of movement.
	 *This makes the character’s rotation align with their movement
	 *direction, which is typically used for a more natural movement appearance.*/
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binds the "Jump" action to the Jump function from ACharacter class
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	// Binds the "MoveVertical" axis input to the MoveVertical function
	PlayerInputComponent->BindAxis("MoveVertical", this, &ABlasterCharacter::MoveVertical);
	
	// Binds the "MoveHorizontal" axis input to the MoveHorizontal function
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ABlasterCharacter::MoveHorizontal);
	
	// Binds the "Turn" axis input to the Turn function
	PlayerInputComponent->BindAxis("Turn", this, &ABlasterCharacter::Turn);
	
	// Binds the "LookUp" axis input to the LookUp function
	PlayerInputComponent->BindAxis("LookUp", this, &ABlasterCharacter::LookUp);
	
}

void ABlasterCharacter::MoveVertical(float Value)
{
	if(Controller != nullptr && Value != 0.f)
	{
		// Create a FRotator representing the yaw rotation (rotation around the vertical axis)
		// It sets the pitch and roll to 0, and uses the controller's yaw rotation
		
		// Equivalent in Unity: Get the Y-axis rotation of the camera or the player.
		// In Unity, rotations are often represented by the Quaternion class or Euler angles using Vector3.
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		
		// Create a direction vector pointing forward in the world space, based on the yaw rotation
		// Equivalent in Unity: Use Quaternion.Euler to get a forward direction.
		// In Unity, vectors in 3D space are represented by the Vector3 class.
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		
		// Add movement input in the forward direction (X-axis) with the specified value
		// Equivalent in Unity: Use CharacterController.Move or transform.Translate.
		AddMovementInput(Direction, Value);
	}
}

void ABlasterCharacter::MoveHorizontal(float Value)
{
	if(Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void ABlasterCharacter::Turn(float Value)
{
	// Adds horizontal rotation (yaw) input to the controller
	AddControllerYawInput(Value);
}

void ABlasterCharacter::LookUp(float Value)
{
	// Adds vertical rotation (pitch) input to the controller
	AddControllerPitchInput(Value);
}

// Called every frame
void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



