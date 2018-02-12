#ifndef CSVLOADER_HPP
#define CSVLOADER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include <QDebug>

class CSVLoader
{
	public:
		struct sample
		{
				sample(long long t, int x, int y);
				long long timecodeNanosec;
				int X, Y;
		};

		using sampleVect = std::vector<sample>;
		CSVLoader(const std::string& path);
		size_t getSamplesCount();
		sampleVect&& getData();
	private:
		sampleVect data;
		bool load(const std::string& path);
};

#endif // CSVLOADER_HPP
