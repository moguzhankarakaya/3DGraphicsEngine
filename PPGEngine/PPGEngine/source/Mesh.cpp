#include "Mesh.h"

bool PPG::Mesh::LoadObjectFile(std::wstring pathToFile)
{
	std::ifstream f;

	f.open(pathToFile, std::ifstream::in);
	if (!f.is_open()) return false;
	
	std::string line;

	// Cache of vertices
	std::vector<Math::vec3> vertices;

	while ( f >> line)
	{
		char desc;
		std::strstream stream;
		stream << line;
		stream >> desc;

		if (desc == '#')
		{
			f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (desc == 'v')
		{
			Math::vec3 v;
			f >> v.x >> v.y >> v.z;
			vertices.push_back(v);
		}
		
		if (desc == 'f')
		{
			int ind[3];
			f >> ind[0] >> ind[1] >> ind[2];
			mesh.push_back({ vertices[ind[0] - 1], vertices[ind[1] - 1], vertices[ind[2] - 1]});
		}
	}

	return true;
}
