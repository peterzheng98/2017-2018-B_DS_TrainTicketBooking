#include "Vector.h"
#include "CoreData.h"
#include "BPlusTree.hpp"
#include <vector>

const int N = 100;

int flag[N];
std::vector<int> V[N];
myAlgorithm::BPlusTree<myAlgorithm::Pair<int, int> , int> bpt(true);

int main()
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			bpt.insert(myAlgorithm::Pair<int, int>(i, j), j);
			V[i][j] = 1;
		}
	for(int i = 0; i < N; i++)
	{
		myAlgorithm::Vector<int> A = bpt.searchFirst(myAlgorithm::Pair<int, int>(i, 0));
		if(A.size() != N)
		{
			puts("WA!");
			return 0;
		}
		memset(flag, 0, sizeof(flag));
		for(int j = 0; j < A.size(); j++)
		{
			if(flag[A[j]])
			{
				puts("WA!!");
				return 0;
			}
			flag[A[j]] = 1;
		}
	}
	puts("Yeah!");
}
