extends Node2D

@export var solar_panel_scene: PackedScene
@onready var TABLE_RATIO = $Constants.TABLE_SHAPE.x * 1.0 /$TextureRect.size.x # cm.px⁻¹

func place_elts():
	for coord: Vector2i in $Constants.SOLAR_PANELS:
		var new_solar_panel: Sprite2D = solar_panel_scene.instantiate();
		var side_scale: float = ($Constants.SOLAR_PANEL_SIDE_SIZE*1.0) / (TABLE_RATIO * new_solar_panel.get_rect().size.x);
		new_solar_panel.scale = Vector2(side_scale, side_scale);
		new_solar_panel.position = coord/TABLE_RATIO;
		add_child(new_solar_panel);

# Called when the node enters the scene tree for the first time.
func _ready():
	place_elts();


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
