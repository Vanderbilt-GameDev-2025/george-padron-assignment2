extends NBodySystem

# Start the simulation by default
func _ready() -> void:
	set_running(true)

# Enable toggling running state with the space key.
func _physics_process(delta: float) -> void:
	if Input.is_action_just_pressed("toggle_pause"): 
				set_running(!is_running())
	
