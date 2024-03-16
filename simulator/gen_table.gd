extends Node2D

@export var solar_panel_scene: PackedScene
@export var plant_scene: PackedScene
@onready var TABLE_RATIO: float = $Constants.TABLE_SHAPE.x * 1.0 / \
												$TextureRect.size.x # mm.px⁻¹

func rescale(sprite: Sprite2D, expected_cm_size: Vector2i) -> void:
	sprite.set_scale((expected_cm_size*1.0) / (TABLE_RATIO * \
													sprite.get_rect().size));

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

# Called when the node enters the scene tree for the first time.
func _ready():
	print(TABLE_RATIO)
	place_elts();


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
