#include <iostream>
#include <vector>

using namespace std;
class VectorsLib {
public:
	vector<float> addVectors(vector<float>first, vector<float> second)
	{
		vector<float> vec;
		float x = first.at(0) + second.at(0);
		float y = first.at(1) + second.at(1);
		vec.push_back(x);
		vec.push_back(y);
		return vec;
	}
	vector<float> subbtractVectors(vector<float>first, vector<float> second)
	{
		vector<float> vec;
		float x = first.at(0) - second.at(0);
		float y = first.at(1) - second.at(1);
		vec.push_back(x);
		vec.push_back(y);
		return vec;
	}
	float multiplyVectors(vector<float>first, vector<float> second)
	{
		float result = first.at(0)*second.at(0)+ first.at(1) * second.at(1);
		return result;
	}
	vector<float> multipyScalarVectors(vector<float>first,float scalar)
	{
		vector<float> vec;
		float x = first.at(0)*scalar;
		float y = first.at(1)*scalar;
		vec.push_back(x);
		vec.push_back(y);
		return vec;
	}
	float lengthVector(vector<float>one)
	{
		float x = one.at(0)*one.at(0);
		float y = one.at(1)*one.at(1);
		return sqrt(x + y);

	}
	vector<float> divideScalarVectors(vector<float>first, float scalar)
	{
		vector<float> vec;
		float x = first.at(0) / scalar;
		float y = first.at(1) / scalar;
		vec.push_back(x);
		vec.push_back(y);
		return vec;
	}

	vector<float> normalize(vector<float>one)
	{
		return divideScalarVectors(one, lengthVector(one));
	}




};