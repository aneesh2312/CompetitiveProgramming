/*
	Do a flood fill algorithm to identify connected components. Fill gaps in vertical and horizontal lines (the # belonging to same component
	shouldnt have any gaps). Recursively call same function to take care of merged blocks.
*/

#include <iostream>
#include <vector>
using namespace std;
class FixImage
{
	vector< vector<int> > matrix;
	public:
		void dfs(vector <string> v, int n, int x, int y, int c)
		{
			matrix[x][y] = c;
			if (x+1 < n and v[x+1][y] == '#' and matrix[x+1][y] == 0)
				dfs(v, n, x+1, y, c);
			if (x-1 >= 0 and v[x-1][y] == '#' and matrix[x-1][y] == 0)
				dfs(v, n, x-1, y, c);
			if (y+1 < v[0].size() and v[x][y+1] == '#' and matrix[x][y+1] == 0)
				dfs(v, n, x, y+1, c);
			if (y-1 >= 0 and v[x][y-1] == '#' and matrix[x][y-1] == 0)
				dfs(v, n, x, y-1, c);
		}
	
		vector <string> originalImage(vector <string> alteredImage)
		{
			matrix.clear();
			for (int i = 0; i < alteredImage.size(); i++)
			{
				vector<int> temp;
				matrix.push_back(temp);
				for (int j = 0; j < alteredImage[i].size(); j++)
				{
					matrix[i].push_back(0);
				}
			}	
			int comp = 1;
			for (int i = 0; i < alteredImage.size(); i++)
			{
				for (int j = 0; j < alteredImage[i].size(); j++)
				{
					if (alteredImage[i][j] == '#' and matrix[i][j] == 0)
					{
						dfs(alteredImage, alteredImage.size(), i, j, comp++);
					}
				}	
			}
			int change = 0;
			for (int i = 0; i < alteredImage.size(); i++)
			{
				for (int j = 0; j < alteredImage[i].size(); j++)
				{
					if (matrix[i][j] != 0)
					{
						int maxim1 = 0, maxim2 = 0;
						for (int k = i+1; k < alteredImage.size(); k++)
						{
							if (matrix[k][j] == matrix[i][j])
								maxim1 = k;
						} 
						for (int k = j+1; k < alteredImage[i].size(); k++)
						{
							if (matrix[i][k] == matrix[i][j])
								maxim2 = k;
						}
						
						for (int k = i+1; k < maxim1; k++)
						{
							if (matrix[k][j] == 0)
							{
								matrix[k][j] = matrix[i][j];
								alteredImage[k][j] = '#';
								change++;
							}
						}
						
						for (int k = j+1; k < maxim2; k++)
						{
							if (matrix[i][k] == 0)
							{
								matrix[i][k] = matrix[i][j];
								alteredImage[i][k] = '#';
								change++;
							}
						}	
					}
				}
			}
			if (change > 0)
				alteredImage = originalImage(alteredImage);
			return alteredImage;
		}
};