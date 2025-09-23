#ifndef _SCORE_HPP_
#define _SCORE_HPP_

class Score {
private:
	struct HighScore {
		char name[10];
		int score;
	} hiscores[5];

public:
	Score();
	~Score();
};

#endif /* _SCORE_HPP_ */
