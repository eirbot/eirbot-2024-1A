extends Node

@export var TABLE_SHAPE = [Vector2i(3000, 2000)];
@export var SOLAR_PANELS = [Vector2i(2050, 275), Vector2i(2050, 500), Vector2i(2050, 725),
							Vector2i(2050, 1275), Vector2i(2050, 1500), Vector2i(2050, 1725),
							Vector2i(2050, 2*1500 -275), Vector2i(2050, 2*1500 -500), Vector2i(2050, 2*1500 -725)];
@export var SOLAR_PANEL_SIDE_SIZE = 100;
@export var POT_RADIUS = 250
@export var PLANTS = [Vector2i(1300, 1000), Vector2i(700, 1000), Vector2i(1500, 1500),
					  Vector2i(500, 1500), Vector2i(1300, 2000), Vector2i(700, 2000)]
@export var OBSTACLE_RADIUS = 250
@export var OBSTACLE_AREAS = [Vector2i(1387, 35), Vector2i(612, 35), Vector2i(1965, 1000),
							  Vector2i(1965, 2000), Vector2i(1387, 2965), Vector2i(612, 2965)]

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
