#include <iostream>
#include <bits/stdc++.h>
#define <Point> P
const int SIZE = 8;
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

struct Othello_board
{
	int now_player;
	bool done;
	int winner;
	int disc_sum[3];
	bool player_pass[3];
	std::array<std::array<int, SIZE>, SIZE> board;
	std::vector<Point> next_valid_spots;
	array <Point> direction
	{
		P(-1, 0), P(1, 0), P(0, -1), P(0, 1);
		P(-1, -1), P(1, 1), P(-1, -1), P(1, 1);
	}
	
	Othello_board()
	{
    	initialize();
	}
	
	void initialize()
	{
		disc_sum[BLACK]=0, disc_sum[WHITE]=0;
		//initialize empty board
    	for(int i = 0; i < SIZE; i++){
    	    for(int j = 0; j < SIZE; j++)
			{
    	        if((i==3 && j==4) || (i==4 && j==3))
    	        {
   		         	board[i][j]=BLACK;
    	        	disc_sum[BLACK]++;
				}
				else if((i==3 && j==3) || (i==4 && j==4))
				{
					board[i][j]=WHITE;
            		disc_sum[WHITE]++;
				}
				else
					board[i][j] = EMPTY;
        	}
    	}

		player_pass[BLACK]=false, player_pass[WHITE]=false;
    	now_Player = BLACK;
    	done = false;
    	winner=EMPTY;
	}
	
	//  copy constructor, NEED MODIFY 
	Othello_board(Othello_board bd)
	{
    	for(int i = 0; i < SIZE; i++)
    	{
    		for(int j = 0; j < SIZE; j++)
    	        this->board[i][j] = bd.board[i][j];
		}
    	for(int i = 1; i < 3; i++)
        {
        	this->disc_sum[i] = bd.disc_sum[i];
        	this->player_pass[i] = bd.player_pass[i];
		}
    	this->now_Player = bd.now_Player;
    	this->done=bd.done;
    	this->winner=bd.winner;

	}

	
	bool check_valid_spot(Point start_pt)
	{
		int enemy_player = now_player=BLACK? WHITE : BLACK;
		if(board[start_pt.x][start_pt.y]==EMPTY)
		{
			for(auto it : direction)
			{
				Point tmp;
				tmp = start_pt + *it;
				if(board[tmp.x][tmp.y]==enemy_player)
				{
					tmp+=*it;
					while(is_inside_board(tmp))
					{
						if(board[tmp.x][tmp.y]==now_player)
						{
							//next_valid_spots.push_back(tmp);
							return true;
						}
						tmp+=*it;
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
	void flip_disc(Point start_pt)  //NEED MODIFY
	{
		int enemy_player = now_player=BLACK? WHITE : BLACK;
		if(board[start_pt.x][start_pt.y]==now_player)
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
	
	int get_node_value()
	{
		// intialize black and white total
    	int BLACK_score = 0;
    	int WHITE_score = 0;

    	// factor in the amount of moves each player has
    	b_total += getBlackLegalMoves(board).size();
    	w_total += getWhiteLegalMoves(board).size();

    	// factor in the amount of pieces each player has on the board
    	b_total += getScore(board, 'b');
    	w_total += getScore(board, 'w');

    	for(int i=0;i<8;i++)
    	{
    		for(int j=0;j<8;j++)
    		{
    			if(board[i][j]!=EMPTY)
    			{
    				//check four corners
    				if(i==0)
    				{
    					if(j==0 || j==7)
    					{
    						if(board[i][j]==BLACK) BLACK_score+=15;
    	    				else WHITE_score+=15;
    	    				continue;
						}
					}
					if(i==7)
					{
						if(j==0 || j==7)
    					{
    						if(board[i][j]==BLACK) BLACK_score+=15;
    	    				else WHITE_score+=15;
    	    				continue;
						}
					}
					
					//check central area
					if(i==2 || i==3 || i=4 || i=5)
					{
						if(j==2 || j==3 || j==4 || j==5)
						{
							if(board[i][j]==BLACK) BLACK_score-=2;
    	    				else WHITE_score-=2;
						}
					}
					
					//check the boundaries rolls and collums as well as special bonus points
					if(i==0 || i==7)
					{
						if(board[i][j]==BLACK) BLACK_score+=5;
    	    			else WHITE_score+=5;
    	    			if(j==2 || j==5)
    	    			{
    	    				if(board[i][j]==BLACK) BLACK_score+=2;
    	    				else WHITE_score+=2;
						}
					}
					if(j==0 || j==7)
					{
						if(board[i][j]==BLACK) BLACK_score+=5;
    	    			else WHITE_score+=5;
    	    			if(i==2 || i==5)
    	    			{
    	    				if(board[i][j]==BLACK) BLACK_score+=2;
    	    				else WHITE_score+=2;
						}
					}
					
					//check if next to the corners
					if(i==0)
					{
						if(j==1 || j==6)
						{
							if(board[i][j]==BLACK) BLACK_score-=3;
    	    				else WHITE_score-=3;
						}
					}
					else if(i==1)
					{
						if(j==0 || j==1 || j==6 ||j==7)
						{
							if(board[i][j]==BLACK) BLACK_score-=3;
    	    				else WHITE_score-=3;
						}
					}
					else if(i==6)
					{
						if(j==0 || j==1 || j==6 ||j==7)
						{
							if(board[i][j]==BLACK) BLACK_score-=3;
    	    				else WHITE_score-=3;
						}
					}
					else if(i==7)
					{
						if(j==1 || j==6)
						{
							if(board[i][j]==BLACK) BLACK_score-=3;
    	    				else WHITE_score-=3;
						}
					}
				}
			}
		}
		
    	// subtract white's total from black, let black be the maximizer
    	return (BLACK_score-WHITE_score);
	}
	
	bool is_finish()
	{
		if((player_pass[BLACK]==true && player_pass[WHITE]==true) || disc_sum[BLACK]+disc_sum[WHITE]==64)
			return true;
		return false;
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
