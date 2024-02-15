# import pyray as pr
from pyray import *
from raylib import *

class MenuButton:
    def __init__(self, text="", x=0, y=0):
        self.label = text
        self.recs = Rectangle(x, y, 150.0, 30.0)

class Menu:
    def __init__(self, options=[], pos_x=0, pos_y=0):
        btns = []
        for i, opt in enumerate(options):
            btns.append(MenuButton(opt, pos_x - 150.0/2, pos_y + 32*i))
        self.option = btns
        self.optionSelected = 0
        self.mouseHoverRec = -1
    
    def update(self):
        for i, opt in enumerate(self.option):
            if check_collision_point_rec(get_mouse_position(), opt.recs):
                self.mouseHoverRec = i
                if is_mouse_button_released(MOUSE_BUTTON_LEFT):
                    self.optionSelected = i
                break
            else:
                self.mouseHoverRec = -1
    def draw(self):
        for i, opt in enumerate(self.option):
            draw_rectangle_rec(
                opt.recs, 
                SKYBLUE if ((i == self.optionSelected) or (i == self.mouseHoverRec)) else LIGHTGRAY
            )
            draw_rectangle_lines(
                int(opt.recs.x), 
                int(opt.recs.y), 
                int(opt.recs.width), 
                int(opt.recs.height), 
                BLUE if ((i == self.optionSelected) or (i == self.mouseHoverRec)) else GRAY
            )
            draw_text(
                opt.label, 
                int(opt.recs.x + opt.recs.width/2 - measure_text(opt.label, 10)/2), 
                int(opt.recs.y + 11), 
                10, 
                DARKBLUE if ((i == self.optionSelected) or (i == self.mouseHoverRec)) else DARKGRAY
            )

    def is_option_selected(self, text):
        if text in self.option[self.optionSelected].label:
            return True
        return False

def main():
    # Initialization
    #--------------------------------------------------------------------------------------
    screenWidth = 800
    screenHeight = 600
    set_config_flags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT)
    init_window(screenWidth, screenHeight, "raylib [core] example - main menu")
    set_target_fps(60)      # Set our game to run at 60 frames-per-second

    main_menu = Menu(["START", "SETTINGS", "EXIT"], screenWidth/2, screenHeight/2)
    
    texture_bg_main_menu = load_texture("../assets/textures/bg_main_menu.png")
    
    init_audio_device()
    sfx_main_menu = load_sound("../assets/sounds/main_menu.wav")
    play_sound(sfx_main_menu)

    # config background size
    aspect_ratio = texture_bg_main_menu.width / texture_bg_main_menu.height
    target_width = screenWidth #* 0.8
    target_height = target_width / aspect_ratio
    imageRect = Rectangle(
        (screenWidth - target_width) / 2,
        (screenHeight - target_height) / 2,
        target_width,
        target_height,
    )
    
    #--------------------------------------------------------------------------------------

    # Main game loop
    while not window_should_close():
        # Update
        #----------------------------------------------------------------------------------
        main_menu.update()

        if not is_sound_playing(sfx_main_menu):
            play_sound(sfx_main_menu)
        
        # if main_menu.is_option_selected("START"):
        #     print("START is selected")
        # if main_menu.is_option_selected("SETTINGS"):
        #     print("SETTINGS is selected")
        if main_menu.is_option_selected("EXIT"):
            print("EXIT is selected")
            break

        #----------------------------------------------------------------------------------

        # Draw
        #----------------------------------------------------------------------------------
        begin_drawing()
       
        # DrawTextureV(texture_bg_main_menu, Vector2((screenWidth/2 - texture_bg_main_menu.width/2), (screenHeight/2 - texture_bg_main_menu.height/2 - 20)), WHITE);
        DrawTexturePro(texture_bg_main_menu, Rectangle(0,0, texture_bg_main_menu.width, texture_bg_main_menu.height), imageRect, Vector2(0, 0), 0, WHITE)
        main_menu.draw()
        
        end_drawing()
        #----------------------------------------------------------------------------------

    # De-Initialization
    #--------------------------------------------------------------------------------------
    stop_sound(sfx_main_menu)
    unload_sound(sfx_main_menu)
    close_audio_device()
    close_window()      # Close window and OpenGL context
    #--------------------------------------------------------------------------------------

if __name__ == '__main__':
    main()