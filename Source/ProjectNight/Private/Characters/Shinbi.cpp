// Developed by SaintFrost


#include "Characters/Shinbi.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AShinbi::AShinbi()
{
	PrimaryActorTick.bCanEverTick = true;

	// We don't want to use the controller rotation as the camera won't be rotating
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// The character needs to move towards the input
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 420.f, 0.f);

	// Camera Boom - TopDown Game: ArmLenght needs to be long and Camera needs to be at the top
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true); // We don't want the Spring Arm to rotate with the owner character
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // We don't want our Spring Arm to collide with other objects
	
	// Camera - Attaching Camera to the Camera Boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

void AShinbi::BeginPlay()
{
	Super::BeginPlay();

	// Assigning the DefaultContext to the Subsystem of the character
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}
	}
}

void AShinbi::Move(const FInputActionValue& Value)
{
	// Checking if the controller is not null
	if (Controller)
	{
		// Getting the Action Value as Vector2d
		const FVector2d MovementVector = Value.Get<FVector2d>();

		// Getting Controller Rotation Yaw
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Setting Forward and Right Directions
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Adding the Movement Action Value according the vectors we calculated
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AShinbi::Jump()
{
	// Inheriting the Jump function from the Character class
	Super::Jump();
}

void AShinbi::Attack()
{
}

void AShinbi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShinbi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Accessing the Enhanced Input Component and assigning the actions to their functions
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShinbi::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShinbi::Jump);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AShinbi::Attack);
	}
}

