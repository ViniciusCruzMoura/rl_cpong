from pyray import *
from raylib import *

def main():
    # Initialization
    #--------------------------------------------------------------------------------------
    camera = None
    screenWidth = 800
    screenHeight = 450
    player = Rectangle(400, 280, 40, 40)
    buildings = []
    buildColors = []
    spacing = 0

    # Config backgrouds
    for i in range(100):
        width = get_random_value(50, 200)
        height = get_random_value(100, 800)
        y = screenHeight - 130.0 - height
        x = -6000.0 + spacing
        buildings.append(Rectangle(x, y, width, height))
        spacing += buildings[i].width
        buildColors.append(Color(get_random_value(200, 240), get_random_value(200, 240), get_random_value(200, 250), 255))

    # Config camera
    offset = Vector2(screenWidth/2.0, screenHeight/2.0)
    target = Vector2(player.x + 20.0, player.y + 20.0)
    rotation = 0.0
    zoom = 1.0
    camera = Camera2D(offset, target, rotation, zoom)

    set_config_flags(FLAG_VSYNC_HINT)
    init_window(screenWidth, screenHeight, "raylib [core] example - 2d camera")
    set_target_fps(60)      # Set our game to run at 60 frames-per-second
    #--------------------------------------------------------------------------------------

    # Main game loop
    while not window_should_close():
        # Update
        #----------------------------------------------------------------------------------
        # Player movement
        if is_key_down(KEY_RIGHT):
            player.x += 2
        elif is_key_down(KEY_LEFT):
            player.x -= 2

        # Camera target follows player
        camera.target = Vector2(player.x + 20, player.y + 20)

        # Camera rotation controls
        if is_key_down(KEY_A):
            camera.rotation = camera.rotation - 1 
        elif is_key_down(KEY_S): 
            camera.rotation = camera.rotation + 1

        # Limit camera rotation to 80 degrees (-40 to 40)
        if camera.rotation > 40:
            camera.rotation = 40
        elif camera.rotation < -40:
            camera.rotation = -40

        # Camera zoom controls
        camera.zoom += (get_mouse_wheel_move()*0.05)

        # Limit camera zoom 
        if camera.zoom > 3.0:
            camera.zoom = 3.0
        elif camera.zoom < 0.1:
            camera.zoom = 0.1

        # Camera reset (zoom and rotation)
        if (is_key_down(KEY_R)):
            camera.zoom = 1.0
            camera.rotation = 0.0
        #----------------------------------------------------------------------------------

        # Draw
        #----------------------------------------------------------------------------------
        begin_drawing()

        clear_background(RAYWHITE)

        begin_mode_2d(camera)

        draw_rectangle(-6000, 320, 13000, 8000, DARKGRAY)

        for i in range(len(buildings)): 
            draw_rectangle_rec(buildings[i], buildColors[i])

        draw_rectangle_rec(player, RED)

        draw_line(int(camera.target.x), -screenHeight*10, int(camera.target.x), screenHeight*10, GREEN)
        draw_line(-screenWidth*10, int(camera.target.y), screenWidth*10, int(camera.target.y), GREEN)

        end_mode_2d()

        draw_text("SCREEN AREA", 640, 10, 20, RED)

        draw_rectangle(0, 0, screenWidth, 5, RED)
        draw_rectangle(0, 5, 5, screenHeight - 10, RED)
        draw_rectangle(screenWidth - 5, 5, 5, screenHeight - 10, RED)
        draw_rectangle(0, screenHeight - 5, screenWidth, 5, RED)

        draw_rectangle( 10, 10, 250, 113, fade(SKYBLUE, 0.5))
        draw_rectangle_lines( 10, 10, 250, 113, BLUE)

        draw_text("Free 2d camera controls:", 20, 20, 10, BLACK)
        draw_text("- Right/Left to move Offset", 40, 40, 10, DARKGRAY)
        draw_text("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY)
        draw_text("- A / S to Rotate", 40, 80, 10, DARKGRAY)
        draw_text("- R to reset Zoom and Rotation", 40, 100, 10, DARKGRAY)
        
        end_drawing()
        #----------------------------------------------------------------------------------
    
    # De-Initialization
    #--------------------------------------------------------------------------------------
    close_window()      # Close window and OpenGL context
    #--------------------------------------------------------------------------------------

if __name__ == '__main__':
    main()