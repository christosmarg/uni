#include <cstring>
#include "Score.hpp"

Score::Score()
{
	(void)memset(&hiscores, 0, sizeof(hiscores));
}

Score::~Score()
{
}
