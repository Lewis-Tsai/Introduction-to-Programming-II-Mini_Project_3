#include <iostream>
#include <bits/stdc++.h>
#define max(a, b) (a>b? a:b)
#define min(a, b) (a<b? a:b)
#define <Point> P
using namespace std;
enum spot_status
{
	EMPTY:0;
	BLACK=1;
	WHITE=2;
}
struct Point
{
	int x, y;
	Point() : Point(0, 0) {}
	Point(int x, int y) : x(x), y(y) {}
	Point operator+(const Point& point) const {
		return Point(this.x + point.x, this.y + point.y);
	}
	Point operator-(const Point& point) const {
		return Point(this.x - point.x, this.y - point.y);
	}
};

int player;
const int SIZE = 8;
std::array<std::array<int, SIZE>, SIZE> board;
std::vector<Point> next_valid_spots;

struct Othello_board
{
	int now_player;
	bool done;
	int winner;
	int disc_sum[2];
	array <Point> direction
	{
		P(-1, 0), P(1, 0), P(0, -1), P(0, 1);
		P(-1, -1), P(1, 1), P(-1, -1), P(1, 1);
	}
	bool check_valid_spot(Point start_pt)
	{
		int enemy_player = cur_player=BLACK? WHITE : BLACK;
		if(board[start_pt.x][start_pt.y]!=EMPTY)
			return false;
		for(auto it : direction)
		{
			Point tmp;
			tmp = start_pt + *it;
			if(board[x][y]==enemy_player)
			{
				tmp+=*it;
				while(is_inside_board(tmp))
				{
					if(board[tmp.x][tmp.y]==cur_player)
					{
						//next_valid_spots.push_back(tmp);
						return true;
					}
				}
			}
		}
		return false;
	}
	bool is_inside_board(Point point)
	{
		if(point.x>=0 && point.x <8)
		{
			if(point.y>=0 && point.y <8)
				return true;
		}
		return false;
	}
	void flip_disc(Point start_pt)
	{
		int enemy_player = cur_player=BLACK? WHITE : BLACK;
		if(board[start_pt.x][start_pt.y]==cur_player)
		{
			for(auto it : direction)
			{
				Point tmp;
				tmp = start_pt + *it;
				while(board[tmp.x][tmp.y]==enemy_player)
				{
					board[tmp.x][tmp.y]==cur_player;
					disc_sum[cur_player]++;
					disc_sum[enemy_player]--;
					tmp+=*it;
				}
				return;
			}
		}
		return;
	}
};
struct Node
{
	int x, y;
	Node alphabeta_pruning(Node node, int depth, int alpha, int beta, bool biggest)
	{
		int value;
		if depth = 0 or node是?端節點
    	     return 節點的啟發值
    	if (biggest)
		{
			value = INT_MIN
    	    for ()
    	          v := max(v, alphabeta(child, depth - 1, α, β, FALSE)) // child = 子節點
    	         α := max(α, v)
    	         if β ? α
    	             break // β裁剪
    	     return v
		}  
		else
    	{
    		v := INT_MAX
    	      for 每?子節點
     	        v := min(v, alphabeta(child, depth - 1, α, β, TRUE))
     	        β := min(β, v)
     	        if β ? α                  break // α裁剪
      	    return v
		}
	}	
    
};

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

void read_valid_spots(std::ifstream& fin) {
    int n_valid_spots;
    fin >> n_valid_spots;
    int x, y;
    for (int i = 0; i < n_valid_spots; i++) {
        fin >> x >> y;
        next_valid_spots.push_back({x, y});
    }
}

void write_valid_spot(std::ofstream& fout) {
    int n_valid_spots = next_valid_spots.size();
    srand(time(NULL));
    // Choose random spot. (Not random uniform here)
    int index = (rand() % n_valid_spots);
    Point p = next_valid_spots[index];
    // Remember to flush the output to ensure the last action is written to file.
    fout << p.x << " " << p.y << std::endl;
    fout.flush();
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    read_valid_spots(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
