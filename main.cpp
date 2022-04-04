#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library library;

int main() {
	FT_Error error = FT_Init_FreeType(&library);
	if (error) {
		std::cout << "An error occured!" << std::endl;
	}
	else {
		std::cout << "No error" << std::endl;
	}
	return 0;
}
