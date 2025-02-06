extends CelestialBody

@onready var display: CSGSphere3D = $Display

# Ensure the visual radius matches the real radius. 
func _ready() -> void:
	display.radius = radius
