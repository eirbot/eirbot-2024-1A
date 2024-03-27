extends Node2D

@onready var armSprite: Sprite2D = $CharacterBody2D/Arm;
@onready var armCollider: CollisionShape2D = $CharacterBody2D/ArmCollision;
@export var speed = Vector2(0,0);

const SPEED = 300.0
const JUMP_VELOCITY = -400.0

func deactivate():
	armSprite.frame = 1;
	armCollider.disabled = true;
	
func activate():
	armSprite.fram = 0;
	armCollider.disabled = false;

func _physics_process(delta):
	$CharacterBody2D.move_and_collide(speed);
