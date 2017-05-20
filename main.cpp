#include <iostream>
#include <glm/glm.hpp>

int main(int argc, char** argv) {
	int width = 1024;
	int height = 768;

	std::cout << "P3\n" << width << " " << height << "\n255\n";
	for(int i = height - 1; i > 0; --i) {
		for(int j = 0; j < width; ++j) {
			glm::vec3 color = glm::vec3(
				float(i) / float(height),
				float(j) / float(width),
				0.2f
			);

			int ir = int(255.99 * color.r);
			int ig = int(255.99 * color.g);
			int ib = int(255.99 * color.b);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0;
}