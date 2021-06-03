#include "Score.hpp"

Score::Score(const char *scorefile)
{
	fpath = std::string(scorefile);
	sf.exceptions(std::fstream::badbit | std::fstream::failbit);
	sf.open(fpath, std::fstream::in | std::fstream::binary);
	if (!sf.is_open())
		throw std::runtime_error(fpath + ": cannot open file");
	for (int i = 0; i < SCORES_LEN; i++) {
		sf.read((char *)&hiscores[i].name, sizeof(hiscores[i].name));
		sf.read((char *)&hiscores[i].score, sizeof(hiscores[i].score));
	}
	sf.close();

	/* FIXME: how to get player name? */
	(void)strncpy(curname, "christos", sizeof(curname));
	curscore = 0;
}

Score::~Score()
{
	sf.open(fpath, std::fstream::out | std::fstream::binary);
	if (sf.is_open()) {
		for (int i = 0; i < SCORES_LEN; i++) {
			sf.write((char *)&hiscores[i].name, 
			    sizeof(hiscores[i].name));
			sf.write((char *)&hiscores[i].score,
			    sizeof(hiscores[i].score));
		}
		sf.close();
	}
}

Score&
Score::operator<< (const char name[NAME_LEN])
{
	(void)strncpy(curname, name, sizeof(curname));
	return *this;
}

Score&
Score::operator<< (const int score)
{
	curscore = score;
	return *this;
}

/* 
 * Convert the hiscores array to something the `popup` method in 
 * `Engine` can print.
 */
std::vector<std::string>
Score::scores_strfmt() const
{
	std::vector<std::string> v;

	for (int i = 0; i < SCORES_LEN; i++)
		v.push_back(std::string(hiscores[i].name) + ": " +
		    std::to_string(hiscores[i].score));
	v.push_back("Press any key to continue");

	return v;
}

const char *
Score::get_curname() const
{
	return curname;
}

int
Score::get_curscore() const
{
	return curscore;
}
