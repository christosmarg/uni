#ifndef _SCORE_HPP_
#define _SCORE_HPP_

#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

class Score {
private:
	static const int NAME_LEN = 10;
	static const int SCORES_LEN = 5;

	struct HighScore {
		char name[NAME_LEN];
		int score;
	} hiscores[SCORES_LEN];

	std::string fpath;
	std::fstream sf;
	char curname[NAME_LEN];
	int curscore;

public:
	Score(const char *scorefile);
	~Score();

	Score& operator<< (const char name[NAME_LEN]);
	Score& operator<< (const int score);
	std::vector<std::string> scores_strfmt() const;
	const char *get_curname() const;
	int get_curscore() const;
};

#endif /* _SCORE_HPP_ */
