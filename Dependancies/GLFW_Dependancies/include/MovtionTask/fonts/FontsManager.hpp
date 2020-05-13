//
//  Fonts.hpp
//  openGL-TEST1
//
//  Created by Lax Zhang on 2019/3/6.
//  Copyright © 2019 Lax Zhang. All rights reserved.
//

#ifndef FONTSMANAGER_H
#define FONTSMANAGER_H

#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include <ft2build.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include FT_FREETYPE_H

class FontsManager{
public:
    struct Character{
        GLuint TextureID;
        glm::ivec2 size;
        glm::ivec2 Bearing;
        long Advance;
    };
    std::map<char, Character> Characters;
    
    FontsManager();
    
    void load_fonts(char *font_path);
private:
    
};


#endif /* Fonts_hpp */
