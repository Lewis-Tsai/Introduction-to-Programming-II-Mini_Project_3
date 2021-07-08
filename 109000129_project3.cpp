#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <cassert>
#include <climits> 
struct Point {
    int x, y;
    int value;
	Point() : Point(0, 0) {}
	Point(int x, int y) : x(x), y(y), value(0) {}
	Point(int x, int y, int value) : x(x), y(y), value(value) {}
	bool operator==(const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Point& rhs) const {
		return !operator==(rhs);
	}
	Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
};

int player;
const int SIZE = 8;
std::array<std::array<int, SIZE>, SIZE> board;
std::vector<Point> next_valid_spots;

int map[8][8];
void ini_map()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(i==0 || i==7)
			{
				if(j==0 || j==7) map[i][j]=30;
				if(j==1 || j==6) map[i][j]=1;
				if(j==2 || j==5) map[i][j]=10;
				else map[i][j]=5;
			}
			if(i==1 || i==6)
			{
				if(j==0 || j==7) map[i][j]=1;
				if(j==1 || j==6) map[i][j]=-5;
				if(j==2 || j==5) map[i][j]=1;
				else map[i][j]=1;
			}
			if(i==2 || i==5)
			{
				if(j==0 || j==7) map[i][j]=10;
				if(j==1 || j==6) map[i][j]=1;
				if(j==2 || j==5) map[i][j]=3;
				else map[i][j]=2;
			}
			if(i==3 || i==4)
			{
				if(j==0 || j==7) map[i][j]=5;
				if(j==1 || j==6) map[i][j]=1;
				if(j==2 || j==5) map[i][j]=2;
				else map[i][j]=1;
			}
		}
	}
}

class OthelloBoard {
public:
    enum SPOT_STATE {
        EMPTY = 0,
        BLACK = 1,
        WHITE = 2
    };
    static const int SIZE = 8;
    const std::array<Point, 8> directions{{
        Point(-1, -1), Point(-1, 0), Point(-1, 1),
        Point(0, -1), /*{0, 0}, */Point(0, 1),
        Point(1, -1), Point(1, 0), Point(1, 1)
    }};
    std::array<std::array<int, SIZE>, SIZE> board;
    std::vector<Point> next_valid_spots;
    std::array<int, 3> disc_count;
    int cur_player;
    bool done;
    int winner;
private:
    int get_next_player(int player) const {
        return 3 - player;
    }
    bool is_spot_on_board(Point p) const {
        return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
    }
    int get_disc(Point p) const {
        return board[p.x][p.y];
    }
    void set_disc(Point p, int disc) {
        board[p.x][p.y] = disc;
    }
    bool is_disc_at(Point p, int disc) const {
        if (!is_spot_on_board(p))
            return false;
        if (get_disc(p) != disc)
            return false;
        return true;
    }
    bool is_spot_valid(Point center) const {
        if (get_disc(center) != EMPTY)
            return false;
        for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player)))
                continue;
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, cur_player))
                    return true;
                p = p + dir;
            }
        }
        return false;
    }
    void flip_discs(Point center) {
        for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player)))
                continue;
            std::vector<Point> discs({p});
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, cur_player)) {
                    for (Point s: discs) {
                        set_disc(s, cur_player);
                    }
                    disc_count[cur_player] += discs.size();
                    disc_count[get_next_player(cur_player)] -= discs.size();
                    break;
                }
                discs.push_back(p);
                p = p + dir;
            }
        }
    }
public:
    OthelloBoard() {
        reset();
    }
    void reset() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = EMPTY;
            }
        }
        board[3][4] = board[4][3] = BLACK;
        board[3][3] = board[4][4] = WHITE;
        cur_player = BLACK;
        disc_count[EMPTY] = 8*8-4;
        disc_count[BLACK] = 2;
        disc_count[WHITE] = 2;
        next_valid_spots = get_valid_spots();
        done = false;
        winner = -1;
    }
    std::vector<Point> get_valid_spots() const {
        std::vector<Point> valid_spots;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                Point p = Point(i, j);
                if (board[i][j] != EMPTY)
                    continue;
                if (is_spot_valid(p))
                    valid_spots.push_back(p);
            }
        }
        return valid_spots;
    }
    bool put_disc(Point p) {
        if(!is_spot_valid(p)) {
            winner = get_next_player(cur_player);
            done = true;
            return false;
        }
        set_disc(p, cur_player);
        disc_count[cur_player]++;
        disc_count[EMPTY]--;
        flip_discs(p);
        // Give control to the other player.
        cur_player = get_next_player(cur_player);
        next_valid_spots = get_valid_spots();
        // Check Win
        if (next_valid_spots.size() == 0) {
            cur_player = get_next_player(cur_player);
            next_valid_spots = get_valid_spots();
            if (next_valid_spots.size() == 0) {
                // Game ends
                done = true;
                int white_discs = disc_count[WHITE];
                int black_discs = disc_count[BLACK];
                if (white_discs == black_discs) winner = EMPTY;
                else if (black_discs > white_discs) winner = BLACK;
                else winner = WHITE;
            }
        }
        return true;
    }
    
    int state_value()
	{
		int goal=player;
		int enemy=(goal==BLACK? WHITE : BLACK);
		int goal_score=0, enemy_score=0;
		int bonus=0;
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				if(board[i][j]!=EMPTY)
				{
					if(board[i][j]==goal)
						goal_score+=map[i][j];
					else
						enemy_score+=map[i][j];
				}
			}
		}
		if(winner==goal)
			goal_score+=500;
		else if(winner==enemy)
			enemy_score+=700;
		if(this->cur_player==player)
		{
			goal_score+=(this->next_valid_spots.size());
			enemy_score+=disc_count[EMPTY]-(this->next_valid_spots.size())*0.7;
			if((this->next_valid_spots.size())==0)
				goal_score-=100;
		}
		goal_score+=disc_count[goal];
		enemy_score+=disc_count[enemy];
		return goal_score-enemy_score;
	}
	
	void sum_recount()
	{
		disc_count[BLACK]=disc_count[WHITE]=disc_count[EMPTY]=0;
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				if(board[i][j]==BLACK)
					disc_count[BLACK]++;
				else if(board[i][j]==WHITE)
					disc_count[WHITE]++;
				else
					disc_count[EMPTY]++;
			}
		}
	}
};

int minimax(OthelloBoard bd, int depth, int alpha, int beta, bool maximizingPlayer) {
    int cur;
	if (depth == 0 || bd.done) {
        return bd.state_value();
    }
	if (maximizingPlayer) {
        int max=INT_MIN;
        for (auto it : bd.next_valid_spots) {
        	OthelloBoard next_bd=bd;
        	if(next_bd.put_disc(it)) {
            	cur = minimax(next_bd, depth - 1, alpha, beta, !maximizingPlayer);
           	 	if (cur > max)
            		max=cur;
            	if(cur>alpha)
            		alpha=cur;
            	if(alpha>=beta)
            		break;
        	}
    	}
    	return max;
	}
    else {
        int min=INT_MAX;
        for (auto it : bd.next_valid_spots) {
        	OthelloBoard next_bd=bd;
        	if(next_bd.put_disc(it)) {
            	cur = minimax(next_bd, depth - 1, alpha, beta, !maximizingPlayer);
            	if (cur < min)
            		min=cur;
            	if(cur<beta)
            		beta=cur;
            	if(alpha>=beta)
            		break;
        	}	
    	}
    	return min;
    }
}

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
    //srand(time(NULL));
    // Choose random spot. (Not random uniform here)
    int index = (rand() % n_valid_spots);
    Point p = next_valid_spots[index];
    fout << p.x << " " << p.y << std::endl;
    // Remember to flush the output to ensure the last action is written to file.
    ini_map();
    OthelloBoard bd;
    bd.board=board;
    bd.next_valid_spots=next_valid_spots;
    bd.cur_player=player;
    bd.sum_recount();
    int max=INT_MIN, trav;
    for(auto it : bd.next_valid_spots)
    {
    	OthelloBoard next_bd=bd;
    	if(next_bd.put_disc(it))
    	{
    		trav=minimax(next_bd, 6, INT_MIN, INT_MAX, false);
    		if(trav>max)
    		{
    			max=trav;
    			p=it;
    			//std::cout<< "best.x:" << best.x << " best.y:" << best.y << std::endl;
    			fout << p.x << " " << p.y << std::endl;
			}
		}
	}
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
