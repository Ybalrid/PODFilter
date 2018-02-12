#include "CSVLoader.hpp"

using namespace std;

CSVLoader::sample::sample(long long t, int x, int y) :
	timecodeNanosec{t},
	X{x},
	Y{y}
{}

CSVLoader::CSVLoader(const std::string& path)
{
	if(!load(path))
	{
		//TODO handle error
	}
}



bool CSVLoader::load(const std::string& path)
{
	ifstream input(path);
	if(!input)
	{
		qDebug() << "failed to open " << path.c_str();
		return false;
	}

	std::string lineBuffer;
	while(std::getline(input, lineBuffer))
	{
		std::stringstream instream(lineBuffer);
		std::string nanosec, X, Y;
		std::getline(instream, nanosec, ',');
		std::getline(instream, X, ',');
		std::getline(instream, Y, ',');

		long long timepoint = stoll(nanosec);
		int x = stoi(X);
		int y = stoi(Y);

		data.emplace_back(timepoint, x, y);
	}

	return true;
}

CSVLoader::sampleVect&& CSVLoader::getData()
{
	return std::move(data);
}
