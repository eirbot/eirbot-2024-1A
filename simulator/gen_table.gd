extends Node2D

@export var solar_panel_scene: PackedScene;
@export var plant_scene: PackedScene;
@export var blue_team: bool = true;
@onready var TABLE_RATIO: float = $Constants.TABLE_SHAPE.x * 1.0 / \
												$TextureRect.size.x; # mm.px⁻¹
@onready var robot: Node2D = $Robot;

func get_symmetric_position(pos: Vector2) -> Vector2:
	var middle: float = $Constants.TABLE_SHAPE.x / 2 / TABLE_RATIO;
	return Vector2(2*middle-pos.x, pos.y);

func get_team_position(pos: Vector2) -> Vector2:
	"""Return the position or its symmetric if the team of the robot is yellow.
	Arguments:
		- pos: the position if the robot is in the blue team.
	"""
	if blue_team: return pos;
	else: return get_symmetric_position(pos);

func get_scale_ratio(sprite: Sprite2D, expected_cm_size: Vector2) -> Vector2:
	return expected_cm_size / (TABLE_RATIO * sprite.get_rect().size);

func rescale(sprite: Sprite2D, expected_cm_size: Vector2i) -> void:
	sprite.set_scale(get_scale_ratio(sprite, expected_cm_size));

func place_elts():
	for coord: Vector2i in $Constants.SOLAR_PANELS:
		var new_solar_panel: Sprite2D = solar_panel_scene.instantiate();
		rescale(new_solar_panel, Vector2i($Constants.SOLAR_PANEL_SIDE_SIZE,\
											$Constants.SOLAR_PANEL_SIDE_SIZE));
		new_solar_panel.position = coord/TABLE_RATIO;
		add_child(new_solar_panel);
	for coord: Vector2i in $Constants.PLANTS:
		for i in range(6):
			var arg = i*PI/3;
			var new_plant: Sprite2D = plant_scene.instantiate();
			rescale(new_plant, Vector2i($Constants.POT_RADIUS, $Constants.POT_RADIUS));
			new_plant.position = (coord + Vector2i($Constants.POT_SPOT_RADIUS*3/4 *\
					Vector2(cos(arg), sin(arg))))*1.0 / TABLE_RATIO;
			add_child(new_plant);
	# rescale robot
	robot.set_scale(get_scale_ratio($Robot/CharacterBody2D/RobotWitoutArm, $Constants.ROBOT_SHAPE));
	robot.set_position(get_team_position($Constants.INITIAL_POSITION_BLUE_TEAM / TABLE_RATIO));
	robot.set_rotation(PI/2 if blue_team else 3*PI/2);

# Called when the node enters the scene tree for the first time.
func _ready():
	print(TABLE_RATIO)
	place_elts();


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
