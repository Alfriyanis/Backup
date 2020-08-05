#pragma once

int num;
int jumVertex = 512;
int jumTampilan = 718;

struct list { int u1, u2, u3; };
struct pos { float x, y, z; };
struct uv { float u, v; };

float ax, ay, az, bx, by, bz, cx, cy, cz;

list* _list = new list[jumTampilan];
pos* _pos = new pos[jumVertex];
uv* _uv = new uv[jumVertex];

int Load(const char* model) {
	FILE* f;
	fopen_s(&f, model, "r");
	if (!f) {
		printf("Gagal Membuka File");
		return 0;
	}
	fscanf_s(f, "NrVertices:%d", &jumVertex);
	for (int i = 0; i < jumVertex; i++) {
		fscanf_s(f, "   %d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&num, &_pos[i].x, &_pos[i].y, &_pos[i].z, &ax, &ay, &az, &bx, &by, &bz, &cx, &cy, &cz, &_uv[i].u, &_uv[i].v);
		std::cout << _pos[i].x << " : " << _pos[i].y << " : " << _pos[i].z << " : " << _uv[i].u << " : " << _uv[i].v << std::endl;
	}

	fscanf_s(f, "\nNrIndices:%d", &jumTampilan);
	for (int i = 0; i < (int)jumTampilan / 3; i++) {
		fscanf_s(f, "   %d.    %d,    %d,    %d", &num, &_list[i].u1, &_list[i].u2, &_list[i].u3);
		std::cout << num << " : " << _list[i].u1 << " : " << _list[i].u2 << " : " << _list[i].u3 << std::endl;
	}
}