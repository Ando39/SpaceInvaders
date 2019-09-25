#include "Firework.h"

Firework::Firework(sf::Color color, size_t maxSparks, size_t maxWidth, size_t maxHeight)
	: sparks(), color(color), maxSparks(maxSparks), maxWidth(maxWidth), maxHeight(maxHeight)
{

	x = std::floor(random_float * maxWidth);
	y = std::floor(random_float * maxHeight);
	age = 0;

	for (auto _ = maxSparks; --_;) {

		float xs = random_float * 5 + 0.5;
		float ys = random_float * 5 + 0.5;
		float weight = random_float * .3 + 0.03;

		if (random_float > 0.5) xs = -xs;
		if (random_float > 0.5) ys = -ys;

		sparks.push_back(Spark(xs, ys, xs, ys, weight, color));

	}

}

bool Firework::explode() {

	if (++age > 100) return false;

	for (auto& spark : sparks) {
		size_t trailAge = age;
		spark.x = this->x + spark.defx * trailAge;
		spark.y = this->y + spark.defy * trailAge + spark.weight * trailAge * spark.weight * trailAge;
	}

	sparks.erase(std::remove_if(sparks.begin(), sparks.end(), [&](Spark e) {
		return e.x < 0 || e.x > maxWidth || e.y < 0 || e.y > maxHeight;
	}), sparks.end());

	return true;
}