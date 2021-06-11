#ifndef _SCORE_HPP_
#define _SCORE_HPP_

#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#define NAMEMAX 11
#define SCORE_STONE 10
#define SCORE_PARCHMENT 100

class Score {
private:
	struct HighScore {
		char name[NAMEMAX];
		int score;
	};
       
	std::array<HighScore, 5> hiscores;
	std::string fpath;
	std::fstream sf;
	char curname[NAMEMAX];
	int curscore;

public:
	Score(const char *scorefile, const char *name);
	~Score();

	Score& operator<< (const char *name);
	Score& operator<< (const int score);

	std::vector<std::string> scores_strfmt() const;
	const char *get_curname() const;
	int get_curscore() const;

private:
	void add_new_hiscore();
};

#endif /* _SCORE_HPP_ */
