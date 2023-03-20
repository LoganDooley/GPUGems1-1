#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

struct Triangle{
    Triangle(glm::vec3 nv0, glm::vec3 nv1, glm::vec3 nv2):
        v0(nv0), v1(nv1), v2(nv2)
    {

    }

    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;

    glm::vec3 getNormal(){
        return glm::normalize(glm::cross(v1-v0, v2-v0));
    }
};

struct Tile{
    Tile(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3):
        t1(Triangle(v0, v1, v2)), t2(Triangle(v2, v3, v0))
    {

    }

    Triangle t1;
    Triangle t2;

    std::vector<float> unpack(){
        glm::vec3 n1 = t1.getNormal();
        glm::vec3 n2 = t2.getNormal();
        std::vector<float> data;
        data.resize(6 * 6);

        data[0] = t1.v0.x;
        data[1] = t1.v0.y;
        data[2] = t1.v0.z;
        data[3] = n1.x;
        data[4] = n1.y;
        data[5] = n1.z;

        data[6] = t1.v1.x;
        data[7] = t1.v1.y;
        data[8] = t1.v1.z;
        data[9] = n1.x;
        data[10] = n1.y;
        data[11] = n1.z;

        data[12] = t1.v2.x;
        data[13] = t1.v2.y;
        data[14] = t1.v2.z;
        data[15] = n1.x;
        data[16] = n1.y;
        data[17] = n1.z;

        data[18] = t2.v0.x;
        data[19] = t2.v0.y;
        data[20] = t2.v0.z;
        data[21] = n2.x;
        data[22] = n2.y;
        data[23] = n2.z;

        data[24] = t2.v1.x;
        data[25] = t2.v1.y;
        data[26] = t2.v1.z;
        data[27] = n2.x;
        data[28] = n2.y;
        data[29] = n2.z;

        data[30] = t2.v2.x;
        data[31] = t2.v2.y;
        data[32] = t2.v2.z;
        data[33] = n2.x;
        data[34] = n2.y;
        data[35] = n2.z;

        return data;
    }
};

class Water{
public:
    Water(glm::vec2 size, unsigned int resolution);
    ~Water();

    void bind();
    void unbind();

    int getSize();

private:
    GLuint m_vbo;
    GLuint m_vao;
    int m_size;
};