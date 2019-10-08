#pragma once
#ifndef __MTF_H__
#define __MTF_H__

#include <vector>
#include <string>

namespace mtf
{
	struct Color
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;
		unsigned char A;
	};

	class Texture
	{
	public:
		int Width;
		int Height;
		std::vector<std::vector<Color>> Data;
		void LoadTexture(std::string Path);
		void SaveTexture(std::string Path);
	};
}


#endif
