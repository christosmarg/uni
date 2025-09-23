#include <cstring>
#include "Score.hpp"

Score::Score(const char *scorefile)
{
	(void)memset(&hiscores, 0, sizeof(hiscores));
}

Score::~Score()
{
}
