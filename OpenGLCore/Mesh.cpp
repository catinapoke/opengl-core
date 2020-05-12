#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(std::string filename)
{
    load(filename);
}

std::string ivec3ToString(ivec3 vec)
{
    char buffer[256];
    sprintf_s(buffer, "%i/%i/%i", vec.x, vec.y, vec.z);
    return std::string(buffer);
}

bool Mesh::load(std::string filename)
{
    printf("Processing file: %s\n", filename.c_str());
    std::ifstream f;
    f.open(filename);
    if (!f.is_open()) {
        printf("Cannot open file %s\n", filename.c_str());
        return false;
    };

    // First word in line
    std::string s;
    // Line residue
    char temp[512];
    // Coords
    std::vector<vec3> v;
    // Normals
    std::vector<vec3> vn;
    // Texture coords
    std::vector<vec3> vt;
    // Polygons
    std::vector<ivec3> faces;

    std::map<std::string, int> vertexToIndex;

    int lines = 0;
    while (!f.eof()) {
        f >> s;
        if (s == "v") // Coords
        {
            vec3 vTemp;
            f >> vTemp.x;
            f >> vTemp.y;
            f >> vTemp.z;
            v.push_back(vTemp);
        }
        else if (s == "vn") // Normals
        {
            vec3 vnTemp;
            f >> vnTemp.x;
            f >> vnTemp.y;
            f >> vnTemp.z;
            vn.push_back(vnTemp);
        }
        else if (s == "vt") // Textures
        {
            vec3 vtTemp;
            f >> vtTemp.x;
            f >> vtTemp.y;
            vtTemp.z = 0;
            vt.push_back(vtTemp);
        }
        else if (s == "f") {
            for (int i = 0; i < 3; i++)
            {
                ivec3 fTemp;
                char temp_c;
                f >> fTemp.x;
                f >> temp_c;
                f >> fTemp.y;
                f >> temp_c;
                f >> fTemp.z;

                // Correction by start index in .obj files
                fTemp = ivec3(fTemp.x - 1, fTemp.y - 1, fTemp.z - 1);

                std::string tempStr = ivec3ToString(fTemp);

                auto vertex = vertexToIndex.find(tempStr);
                if (vertex != vertexToIndex.end())
                {
                    indices.push_back((GLuint)(vertex->second));
                }
                else
                {
                    faces.push_back(fTemp);
                    indices.push_back((GLuint)(faces.size() - 1));
                    vertexToIndex.insert(std::pair<std::string, int>(tempStr, (faces.size() - 1)));
                }
            }
        }
        f.getline(temp, 512);
    };
    f.close();
    printf("File proceeded\n");
    vertices = std::vector<Vertex>(faces.size());

    printf("Vertex count - %i\n Indices count - %i \n\n", static_cast<int>(vertices.size()), static_cast<int>(indices.size()));

    int k = 0;
    for (auto it = faces.begin(); it != faces.end(); it++)
    {
        vertices[k].coord[0] = v[(*it).x].x;
        vertices[k].coord[1] = v[(*it).x].y;
        vertices[k].coord[2] = v[(*it).x].z;

        vertices[k].textureCoord[0] = vt[(*it).y].x;
        vertices[k].textureCoord[1] = vt[(*it).y].y;
        vertices[k].textureCoord[2] = vt[(*it).y].z;

        vertices[k].normal[0] = vn[(*it).z].x;
        vertices[k].normal[1] = vn[(*it).z].y;
        vertices[k].normal[2] = vn[(*it).z].z;
        k++;
    }

    GLuint buffers[2];
    glGenBuffers(2, buffers);
    glGenVertexArrays(1, &VAO);
    vertexBufferObject = buffers[0];//VBO
    indexBufferObject = buffers[1];

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    int location = 0;
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, coord));
    glEnableVertexAttribArray(location);

    location = 1;
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(location);

    location = 2;
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoord));
    glEnableVertexAttribArray(location);

    glBindVertexArray(0);
    return true;
}

void Mesh::draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}