#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include "VectorsLib.cpp"
using namespace std;

class Ball {
private: 

	std::vector<float> position;
	std::vector<float> velocity;
	float radius;
	VectorsLib vectors;
	float mass = 5;

public:
	Ball(float g_x, float g_y, float g_radius)
	{
		position.push_back(g_x);
		position.push_back(g_y);
		radius = g_radius;
		velocity.push_back(2);
		velocity.push_back(2);
	}
	float get_x()
	{
		return position.at(0);
	}
	float get_y()
	{
		return position.at(1);
	}
	float get_radius()
	{
		return radius;
	}
	float get_velX()
	{
		return velocity.at(0);
	}float get_velY()
	{
		return velocity.at(1);
	}

	void set_x(float X)
	{
		position.at(0) = X;
	}
	void set_y(float Y)
	{
		position.at(1) = Y;
	}
	void set_radius(float Radius)
	{
		radius=Radius;
	}
	void set_velX(float x)
	{
		velocity.at(0) = x;
	}
	void set_velY(float y)
	{
		velocity.at(1) = y;
	}


	void move()
	{
		position = vectors.addVectors(position,velocity);
		//position.insert(position.end(),velocity.begin(),velocity.end());
		//cout << velocity.at(0) << " " << velocity.at(1) << endl;
	}

	void direction_set()
	{
		int randX = rand() % (1 - 0 + 1) + 0;
		int randY = rand() % (1 - 0 + 1) + 0;

		if (randX == 1)
		{
			velocity.at(0) = -velocity.at(0);
		}
		if (randY == 1)
		{
			velocity.at(1) = -velocity.at(1);
		}
	}

	void chceckwallcolision(float Width, float Height)
	{
		if (position.at(0) < 0+radius || position.at(0) > Width-radius)
		{
			velocity.at(0) = -velocity.at(0);
		}
		if (position.at(1) < 0 + radius || position.at(1) > Height - radius)
		{
			velocity.at(1) = -velocity.at(1);
		}
	}

	bool equal(Ball ball)
	{
		if (this->get_x() == ball.get_x() && this->get_y() == ball.get_y())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void reflect(Ball* otherBall, float distance)
	{
		vector<float> one = { 1,1 };
		//cout << otherBall->position.at(0) << " " << otherBall->position.at(1) << endl;
		
		vector<float>centerOne = vectors.addVectors(position, vectors.multipyScalarVectors(one, radius / 2));
		vector<float>centerTwo = vectors.addVectors(otherBall->position, vectors.multipyScalarVectors(one, otherBall->radius / 2));

		vector<float>unitNormalVector = vectors.normalize(vectors.subbtractVectors(centerTwo, centerOne));
		vector<float>unitTangentVector = { -unitNormalVector.at(1),unitNormalVector.at(0) };

		float velocityOneNormal = vectors.multiplyVectors(unitNormalVector,velocity);
		float velocityOneTangent = vectors.multiplyVectors(unitTangentVector, velocity);
		float velocityTwoNormal = vectors.multiplyVectors(unitNormalVector, otherBall->velocity);
		float velocityTwoTangent = vectors.multiplyVectors(unitTangentVector, otherBall->velocity);

		float newNormalVelocityOne = (velocityOneNormal * (mass - otherBall->mass) + 2 * otherBall->mass * velocityTwoNormal) / (mass + otherBall->mass);
		float newNormalVelocityTwo = (velocityTwoNormal * (otherBall->mass - mass) + 2 * mass * velocityOneNormal) / (mass + otherBall->mass);

		vector<float>newVelocityOne = vectors.addVectors(vectors.multipyScalarVectors(unitNormalVector, newNormalVelocityOne), vectors.multipyScalarVectors(unitTangentVector, velocityOneTangent));
		vector<float>newVelocityTwo = vectors.addVectors(vectors.multipyScalarVectors(unitNormalVector, newNormalVelocityTwo), vectors.multipyScalarVectors(unitTangentVector, velocityTwoTangent));

		velocity = newVelocityOne;
		otherBall->velocity = newVelocityTwo;
		/*
		vector<float>normal = vectors.divideScalarVectors(one,distance);
		vector<float>tangental = {-normal.at(1),normal.at(0)};
		float productTng = vectors.multiplyVectors(velocity,tangental);
		float productTng2 = vectors.multiplyVectors(otherBall->velocity, tangental);
		float m = (productTng * (mass - otherBall->mass) + 2 * otherBall->mass * productTng2) / (mass + otherBall->mass);

		velocity = vectors.addVectors(vectors.multipyScalarVectors(tangental,productTng),vectors.multipyScalarVectors(normal,m));*/

		//cout << normal.at(0) << " " << normal.at(1)<<endl;
	}

	void separete(Ball* otherBall, float distance, float Width, float Height)
	{
		float overlap = (distance - get_radius() - otherBall->get_radius()) / 2;
		float changeX = get_x() - (overlap * (get_x() - otherBall->get_x()) / distance);
		float changeY = get_y() - (overlap * (get_y() - otherBall->get_y()) / distance);

		if(changeX>0+radius && changeX<Width-radius)
		set_x(changeX);
		if(changeY > 0 + radius && changeY < Height - radius)
		set_y(changeY);
	}
};


