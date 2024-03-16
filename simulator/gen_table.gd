extends Node2D

@export var solar_panel_scene: PackedScene
@onready var TABLE_RATIO = 3000/$TextureRect.size[1] # cm.px⁻¹

func transpose(vec: Vector2i):
	return Vector2i(vec.y, vec.x);

func place_elts():
	for coord: Vector2i in $Constants.SOLAR_PANELS:
		var new_solar_panel = solar_panel_scene.instantiate();
		new_solar_panel.global_position = transpose(coord)/TABLE_RATIO;
		# new_solar_panel.size = Vector2i($Constants.SOLAR_PANEL_SIDE_SIZE / TABLE_RATIO,
		# 						$Constants.SOLAR_PANEL_SIDE_SIZE / TABLE_RATIO);
		new_solar_panel.scale = Vector2(0.2, 0.2);
		add_child(new_solar_panel);

# Called when the node enters the scene tree for the first time.
func _ready():
	place_elts();


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
