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
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        printf("Cannot open file %s\n", filename.c_str());
        return false;
    };

    std::string s; // First word in line
    char temp[512]; // Line residue
    std::vector<vec3> v; // Coords
    std::vector<vec3> vn; // Normals
    std::vector<vec2> vt; // Texture coords
    std::vector<ivec3> faces; // Polygons
    std::map<std::string, int> vertexToIndex;

    while (!file.eof()) {
        file >> s;
        if (s == "v") // Coords
        {
            vec3 coords;
            file >> coords.x;
            file >> coords.y;
            file >> coords.z;
            v.push_back(coords);
        }
        else if (s == "vn") // Normals
        {
            vec3 normals;
            file >> normals.x;
            file >> normals.y;
            file >> normals.z;
            vn.push_back(normals);
        }
        else if (s == "vt") // Textures
        {
            vec2 textureCoords;
            file >> textureCoords.x;
            file >> textureCoords.y;
            vt.push_back(textureCoords);
        }
        else if (s == "f") {
            for (int i = 0; i < 3; i++)
            {
                ivec3 fTemp;
                char temp_c;
                file >> fTemp.x;
                file >> temp_c;
                file >> fTemp.y;
                file >> temp_c;
                file >> fTemp.z;
                faces.push_back(fTemp);
            }
        }
        file.getline(temp, 512);
    };
    file.close();

    vertices = std::vector<Vertex>(0);

    for (auto it : faces)
    {
        vec3 coord = v[it.x - 1];
        vec3 normals = vn[it.z - 1];
        vec2 textureCoords = vt[it.y - 1];

        std::string faceString = std::to_string(it.x) + "/" + std::to_string(it.y) + "/" + std::to_string(it.z);

        auto vertex = vertexToIndex.find(faceString);

        if (vertex != vertexToIndex.end())
        {
            indices.push_back((GLuint)(vertex->second));
        }
        else
        {
            Vertex tmp = { { coord.x, coord.y, coord.z }, { normals.x, normals.y, normals.z }, { textureCoords.s, textureCoords.t } };
            vertices.push_back(tmp);
            indices.push_back(vertices.size() - 1);
            vertexToIndex.emplace(faceString, vertices.size() - 1);
        }
    }

#if debug
    printf("Vertex count - %i\n Indices count - %i \n\n", static_cast<int>(faces.size()), static_cast<int>(indices.size()));

    printf("Vertices\n");
    for (int i = 0; i < vertices.size(); i++)
    {
        printf("%d) P: %f %f %f N: %f %f %f T: %f %f\n", i,
            vertices[i].coord[0], vertices[i].coord[1], vertices[i].coord[2],
            vertices[i].normal[0], vertices[i].normal[1], vertices[i].normal[2],
            vertices[i].textureCoord[0], vertices[i].textureCoord[1]
        );
    }
    printf("Indices\n");
    for (int i = 0; i < indices.size(); i += 3)
    {
        printf("%d %d %d\n", indices[i], indices[i + 1], indices[i + 2]);
    }
#endif

    GLuint buffers[2];
    glGenBuffers(2, buffers);
    glGenVertexArrays(1, &VAO);
    VBO = buffers[0];//VBO
    EBO = buffers[1];

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

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
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return true;
}

void Mesh::drawSingle()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::drawInstanced(int count)
{
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, count);
    glBindVertexArray(0);
}

#if 0
bool Mesh::oldLoad(std::string filename)
{
    printf("Processing file: %s\n", filename.c_str());
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        printf("Cannot open file %s\n", filename.c_str());
        return false;
    };

    std::string s; // First word in line
    char temp[512]; // Line residue
    std::vector<vec3> v; // Coords
    std::vector<vec3> vn; // Normals
    std::vector<vec2> vt; // Texture coords
    std::vector<ivec3> faces; // Polygons
    std::map<std::string, int> vertexToIndex;

    while (!file.eof()) {
        file >> s;
        if (s == "v") // Coords
        {
            vec3 coords;
            file >> coords.x;
            file >> coords.y;
            file >> coords.z;
            v.push_back(coords);
        }
        else if (s == "vn") // Normals
        {
            vec3 normals;
            file >> normals.x;
            file >> normals.y;
            file >> normals.z;
            vn.push_back(normals);
        }
        else if (s == "vt") // Textures
        {
            vec2 textureCoords;
            file >> textureCoords.x;
            file >> textureCoords.y;
            vt.push_back(textureCoords);
        }
        else if (s == "f") {
            for (int i = 0; i < 3; i++)
            {
                ivec3 fTemp;
                char temp_c;
                file >> fTemp.x;
                file >> temp_c;
                file >> fTemp.y;
                file >> temp_c;
                file >> fTemp.z;

                fTemp = ivec3(fTemp.x - 1, fTemp.y - 1, fTemp.z - 1);
                std::string faceString = std::to_string(fTemp.x) + "/" + std::to_string(fTemp.y) + "/" + std::to_string(fTemp.z);

                auto vertex = vertexToIndex.find(faceString);
                if (vertex != vertexToIndex.end())
                {
                    indices.push_back((GLuint)(vertex->second));
                }
                else
                {
                    Vertex tmp = { { v[fTemp.x].x, v[fTemp.x].y, v[fTemp.x].z }, { vn[fTemp.z].x, vn[fTemp.z].y, vn[fTemp.z].z }, { vt[fTemp.y].s, vt[fTemp.y].t } };
                    vertices.push_back(tmp);
                    indices.push_back(vertices.size() - 1);
                    vertexToIndex.emplace(faceString, vertices.size() - 1);
                }
            }
        }
        file.getline(temp, 512);
    };
    file.close();
    printf("File proceeded\n");

    printf("Vertex count - %i\n Indices count - %i \n\n", static_cast<int>(vertices.size()), static_cast<int>(indices.size()));
    printf("Vertices\n");
    for (int i = 0; i < vertices.size(); i++)
    {
        printf("%d) P: %f %f %f N: %f %f %f T: %f %f\n", i,
            vertices[i].coord[0], vertices[i].coord[1], vertices[i].coord[2],
            vertices[i].normal[0], vertices[i].normal[1], vertices[i].normal[2],
            vertices[i].textureCoord[0], vertices[i].textureCoord[1]
        );
    }
    printf("Indices\n");
    for (int i = 0; i < indices.size(); i += 3)
    {
        printf("%d %d %d\n", indices[i], indices[i + 1], indices[i + 2]);
    }

    GLuint buffers[2];
    glGenBuffers(2, buffers);
    glGenVertexArrays(1, &VAO);
    VBO = buffers[0];//VBO
    EBO = buffers[1];

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

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
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return true;
}
#endif