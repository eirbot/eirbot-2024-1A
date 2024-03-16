extends Node

@export var TABLE_SHAPE = Vector2i(3000, 2000);
@export var SOLAR_PANELS: Array[Vector2i] = [Vector2i(275, 2050), Vector2i(500, 2050), Vector2i(725, 2050),
Vector2i(1275, 2050), Vector2i(1500, 2050), Vector2i(1725, 2050),
Vector2i(2275, 2050), Vector2i(2500, 2050), Vector2i(2725, 2050)];
@export var SOLAR_PANEL_SIDE_SIZE: int = 100;
@export var POT_RADIUS: int = 250
@export var PLANTS: Array[Vector2i] = [Vector2i(1300, 1000), Vector2i(700, 1000), Vector2i(1500, 1500),
					  Vector2i(500, 1500), Vector2i(1300, 2000), Vector2i(700, 2000)]
@export var OBSTACLE_RADIUS: int = 250
@export var OBSTACLE_AREAS: Array[Vector2i] = [Vector2i(1387, 35), Vector2i(612, 35), Vector2i(1965, 1000),
							  Vector2i(1965, 2000), Vector2i(1387, 2965), Vector2i(612, 2965)]

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
