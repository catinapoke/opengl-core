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

bool Mesh::load(std::string filePath)
{
	// Open the file and check if it's opened
	std::ifstream meshFile;
	meshFile.open(filePath);
	if (!meshFile.is_open())
	{
		printf("Cannot open the file: %s\n", filePath.c_str());
		return false;
	}

	std::vector<vec3> coordinates;
	std::vector<vec2> texCoords;
	std::vector<vec3> normals;
	std::vector<vec3> faces;
	char lineEnd[512];
	while (!meshFile.eof())
	{
		char ch;
		std::string inputString;
		meshFile >> inputString;

		if (inputString == "v")
		{
			vec3 coords;
			meshFile >> coords.x;
			meshFile >> coords.y;
			meshFile >> coords.z;
			coordinates.push_back(coords);
		}
		else if (inputString == "vt")
		{
			vec2 textureCoordinates;
			meshFile >> textureCoordinates.s;
			meshFile >> textureCoordinates.t;
			texCoords.push_back(textureCoordinates);
		}
		else if (inputString == "vn")
		{
			vec3 normal_coords;
			meshFile >> normal_coords.x;
			meshFile >> normal_coords.y;
			meshFile >> normal_coords.z;

			normals.push_back(normal_coords);
		}
		else if (inputString == "f")
		{
			for (int i = 0; i < 3; i++)
			{
				vec3 face;
				meshFile >> face.x;
				meshFile >> ch;
				meshFile >> face.y;
				meshFile >> ch;
				meshFile >> face.z;
				faces.push_back(face);
			}
		}
		meshFile.getline(lineEnd, 512);
	}
	// Close the file
	meshFile.close();

	std::map<std::string, int> m;

	// Make a vertices
	for (auto it : faces)
	{
		vec3 vCoord = coordinates[it.x - 1];
		vec2 vTexCoord = texCoords[it.y - 1];
		vec3 vNormal = normals[it.z - 1];
		std::string str = std::to_string(it.x) + '/' + std::to_string(it.y) + '/' + std::to_string(it.z);

		auto v = m.find(str);
		if (v == m.end())
		{
			Vertex tmp{ {vCoord.x, vCoord.y, vCoord.z}, {vNormal.x, vNormal.y, vNormal.z}, {vTexCoord.s, vTexCoord.t} };
			vertices.push_back(tmp);
			m.emplace(str, vertices.size() - 1);
		}
		indices.push_back(m[str]);
	}
	printf("Vertices loaded: %i\n", vertices.size());
	printf("Vertex count - %i\n Indices count - %i \n", static_cast<int>(vertices.size()), static_cast<int>(indices.size()));

	GLint buffers[2];
	// Generate buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::coord));	// 0 is vertex coordinate data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal));	// 1 is vertex normal data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::textureCoord)); // 2 is vertex texture coordinate data
	glEnableVertexAttribArray(2);

	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// Unbind all buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

void Mesh::draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}