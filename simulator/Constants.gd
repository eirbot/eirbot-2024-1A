extends Node

# All the units are mm

@export var TABLE_SHAPE = Vector2i(3000, 2000);
@export var SOLAR_PANELS: Array[Vector2i] = [
	Vector2i(275, 2050), Vector2i(500, 2050), Vector2i(725, 2050),
	Vector2i(1275, 2050), Vector2i(1500, 2050), Vector2i(1725, 2050),
	Vector2i(2275, 2050), Vector2i(2500, 2050), Vector2i(2725, 2050)
	];
@export var SOLAR_PANEL_SIDE_SIZE: int = 100;
@export var POT_SPOT_RADIUS: int = 125;
@export var POT_RADIUS: int = 55;
@export var PLANTS: Array[Vector2i] = [
	Vector2i(1000, 1300), Vector2i(1000, 700), Vector2i(1500, 1500),
	Vector2i(1500, 500), Vector2i(2000, 1300), Vector2i(2000, 700),
	];
@export var OBSTACLE_RADIUS: int = 250;
@export var OBSTACLE_AREAS: Array[Vector2i] = [
	Vector2i(1387, 35), Vector2i(612, 35), Vector2i(1965, 1000),
	Vector2i(1965, 2000), Vector2i(1387, 2965), Vector2i(612, 2965)
	];

@export var ROBOT_SHAPE = Vector2(306, 192.5); # robot 2D body without the arm
@export var INITIAL_POSITION_BLUE_TEAM = Vector2i(3000-300, 1000);

