#include <random>
#include <vector>

class myRandom {
public:	
	static int uniform(int N);
	static double uniform();
	static int discrete(std::vector<double> a);

private:
	myRandom();
	static std::mt19937 mt_;
	static std::mt19937 init() { 
		std::random_device rd;
		return std::mt19937(rd()); 
	}

};
