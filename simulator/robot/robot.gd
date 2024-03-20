extends CharacterBody2D

@onready var armSprite: Sprite2D = $Arm;
@onready var armCollider: CollisionShape2D = $ArmCollision;

const SPEED = 300.0
const JUMP_VELOCITY = -400.0

func deactivate():
	armSprite.frame = 1;
	armCollider.disabled = true;
	
func activate():
	armSprite.fram = 0;
	armCollider.disabled = false;

func _physics_process(delta):
	pass
