extends Camera3D

@export var drag_speed: float = 0.1 
@export var zoom_speed: float = 1.0 
@export var zoom_min: float = 5.0
@export var zoom_max: float = 20.0 
@export var drag_button = MOUSE_BUTTON_RIGHT

var dragging: bool = false
var last_mouse_pos: Vector2 = Vector2()

func _input(event: InputEvent) -> void:
	# Handle moust button inputs
	if event is InputEventMouseButton:
		match event.button_index: 
			drag_button: 
				dragging = event.pressed
				last_mouse_pos = event.position  
			MOUSE_BUTTON_WHEEL_UP: 
				position.z = clamp(position.z - zoom_speed, zoom_min, zoom_max)
			MOUSE_BUTTON_WHEEL_DOWN:
				position.z = clamp(position.z + zoom_speed, zoom_min, zoom_max)
	
	# Handle dragging
	if event is InputEventMouseMotion and dragging: 	
		var delta = event.position - last_mouse_pos
		var velocity = delta * drag_speed
		
		var right = global_transform.basis.x 
		var up = global_transform.basis.y 
		var movement = -right * velocity.x + up * velocity.y 
		
		# Restrict movement to horizontal plane 
		position += movement
		last_mouse_pos = event.position
