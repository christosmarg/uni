#ifndef _SCORE_HPP_
#define _SCORE_HPP_

#include <fstream>

class Score {
private:
	struct HighScore {
		char name[10];
		int score;
	} hiscores[5];

public:
	Score(const char *scorefile);
	~Score();
};

#endif /* _SCORE_HPP_ */
