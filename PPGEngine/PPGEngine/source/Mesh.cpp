#include "Mesh.h"

bool PPG::Mesh::LoadObjectFile(std::wstring pathToFile)
{
	std::ifstream f;

	f.open(pathToFile, std::ifstream::in);
	if (!f.is_open()) return false;
	
	std::string line;

	// Cache of vertices
	std::vector<Math::vec4> vertices;
	std::vector<Math::vec4> normals;
	std::vector<Math::vec3> textureCoord;

	while ( f >> line)
	{
		char desc[128];
		std::strstream stream;
		stream << line;
		stream >> desc;

		if (desc[0] == '#')
		{
			f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (std::strcmp(desc, "v") == 0)
		{
			// parse vertices
			Math::vec4 v;
			f >> v.x >> v.y >> v.z;
			v.w = 1.0f;
			vertices.push_back(v);
			continue;
		}
		
		if (std::strcmp(desc, "vt") == 0)
		{
			// parse vertex textures
			Math::vec3 t;
			f >> t.u >> t.v;
			t.w = 1.0f;
			textureCoord.push_back(t);
			continue;
		}

		if (std::strcmp(desc, "vn") == 0)
		{
			// parse vertex normals
			Math::vec4 n;
			f >> n.x >> n.y >> n.z;
			n.w = 0.0f;
			normals.push_back(n);
			continue;
		}

		if (std::strcmp(desc, "f") == 0)
		{
			std::string::size_type size_type;
			size_t vIdx[3] = {0}, uvIdx[3] = {0}, nIdx[3] = {0};
			std::string facesIndices[3];
			std::smatch match;
			std::regex  rgx{R"((\d+)\/?(\d+)?\/?(\d+)?)"};
			
			f >> facesIndices[0] >> facesIndices[1] >> facesIndices[2];
			
			for (size_t i = 0; i < 3; i++)
			{
				if ( std::regex_match(facesIndices[i], match, rgx) )
				{
					if (match[1].matched)
					{
						vIdx[i] = std::stoi(match[1].str(), &size_type);
					}
					if (match[2].matched)
					{
						uvIdx[i] = std::stoi(match[2].str(), &size_type);
					}
					if (match[3].matched)
					{
						nIdx[i] = std::stoi(match[3].str(), &size_type);
					}
				}
			}
			
			Triangle tri{ vertices[vIdx[0] - 1], vertices[vIdx[1] - 1], vertices[vIdx[2] - 1] };
			if (uvIdx[0] != 0 && uvIdx[1] != 0 && uvIdx[2] != 0)
				tri.SetTextureCoordinates(textureCoord[uvIdx[0] - 1], textureCoord[uvIdx[1] - 1], textureCoord[uvIdx[2] - 1]);
			if (nIdx[0] != 0 && nIdx[2] != 0 && nIdx[2] != 0)
				tri.SetPerVertexNormals(normals[nIdx[0] - 1], normals[nIdx[1] - 1], normals[nIdx[2] - 1]);
			mesh.push_back(tri);

			continue;
		}
	}

	return true;
}
