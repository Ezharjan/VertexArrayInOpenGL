//
//  texture.cpp
//  openGL-Lightning
//
//  Created by Lax Zhang on 2019/3/2.
//  Copyright © 2019 Lax Zhang. All rights reserved.
//

#include "texture.hpp"
#include "../stb/stb.cpp"

using namespace std;

unsigned int loadTexture(char *file){
    
    string filename = file;
    unsigned long suffix_pos = filename.find_last_of(".");
    string suffix = filename.substr(suffix_pos);
    // 箱子的纹理
    unsigned int texture_cube;
    glGenTextures(1, &texture_cube);
    glBindTexture(GL_TEXTURE_2D, texture_cube);
    stbi_set_flip_vertically_on_load(true);

    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int t_width, t_height, nrChannels;
    unsigned char *data= NULL;
    if (suffix.compare(".jpg") == 0 || suffix.compare(".JPG") == 0) {
        cout << "Texture image is jpg" << endl;
        data = stbi_load(file, &t_width, &t_height, &nrChannels, NULL);
    }else if(suffix.compare(".png") == 0 || suffix.compare(".PNG") == 0){
        cout << "Texture image is png" << endl;
        data = stbi_load(file, &t_width, &t_height, &nrChannels, STBI_rgb);
    }else{
        data = stbi_load(file, &t_width, &t_height, &nrChannels, STBI_rgb_alpha);
    }
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else
        std::cout << "Failed to load texture"  << endl;
    stbi_image_free(data);
    
    return texture_cube;
}
