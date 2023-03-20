#include "water.h"
#include <iostream>
#include "debug.h"

Water::Water(glm::vec2 size, unsigned int resolution){
    std::vector<float> data;

    glm::vec3 anchor = glm::vec3(-size.x/2, 0, -size.y/2);
    glm::vec3 xoffset = glm::vec3(-size.x/resolution, 0, 0);
    glm::vec3 zoffset = glm::vec3(0, 0, -size.y/resolution);
    for(int i = 0; i<resolution; i++){
        anchor.x = -size.x/2 + size.x/resolution * i;
        for(int j = 0; j<resolution; j++){
            anchor.z = -size.y/2 + size.y/resolution * j;
            Tile t = Tile(anchor, anchor + xoffset, anchor + xoffset + zoffset, anchor + zoffset);
            std::vector<float> tileData = t.unpack();
            data.insert(data.end(), tileData.begin(), tileData.end());
        }
    }

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<GLvoid*>(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_size = data.size() / 6;
}

Water::~Water(){

}

void Water::bind(){
    glBindVertexArray(m_vao);
}

void Water::unbind(){
    glBindVertexArray(0);
}

int Water::getSize(){
    return m_size;
}