//
//  Fonts.cpp
//  openGL-TEST1
//
//  Created by Lax Zhang on 2019/3/6.
//  Copyright © 2019 Lax Zhang. All rights reserved.
//

#include "FontsManager.hpp"

using namespace std;

FontsManager::FontsManager(){
}

void FontsManager::load_fonts(char *font_path){
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
    FT_Face face;
    if (FT_New_Face(ft, font_path, 0, &face))
        cout << "ERROR::FREETYPE: Failed to load font" << endl;
    FT_Set_Pixel_Sizes(face, 0, 48); // 设置字体的宽高
    // 强制按照1bit对齐
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // 保存128个字符
    for (GLubyte c = 0; c < 128; c++) {
        // 加载字体
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
            continue;
        }
        // 生成字体纹理
        GLuint texture;
        glGenTextures(1, &texture);
        
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        // 设置纹理选项
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(pair<GLchar, Character>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
