#include "Score.hpp"

Score::Score(const char *scorefile, const char *name)
{
	fpath = std::string(scorefile);

	sf.exceptions(std::fstream::badbit);
	sf.open(fpath, std::fstream::in | std::fstream::binary);
	if (!sf.is_open())
		throw std::runtime_error(fpath + ": cannot open file");
	for (int i = 0; i < hiscores.size(); i++) {
		sf.read((char *)&hiscores[i].name, sizeof(hiscores[i].name));
		sf.read((char *)&hiscores[i].score, sizeof(hiscores[i].score));
	}
	sf.close();

	/* Initialize the current name and score. */
	(void)strncpy(curname, name, sizeof(curname));
	curscore = 0;
}

/* 
 * I'm not sure if this stupid or not...
 */
Score::~Score()
{
	add_new_hiscore();

	sf.open(fpath, std::fstream::out | std::fstream::binary);
	if (sf.is_open()) {
		for (int i = 0; i < hiscores.size(); i++) {
			sf.write((char *)&hiscores[i].name, 
			    sizeof(hiscores[i].name));
			sf.write((char *)&hiscores[i].score,
			    sizeof(hiscores[i].score));
		}
		sf.close();
	}
}

/*
 * The following 2 overloads return a reference to `this`, so that
 * we can chain arguments together.
 *
 * Take the following chain as an example:
 *	`*score << "string" << 100`
 *
 * First, `*score << "string"` will call the overload which
 * takes a `const char *` , and will return a reference to `this`.
 *
 * After the first overload has returned, `*score << "string"` will
 * be replaced with just `*score` and the initial overload will 
 * look like this:
 *	`*score << 100`
 *
 * Now, the overload getting a `const int` argument will get called.
 *
 * Technically, this chain can work no matter the order or number
 * of the arguments.
 */
Score&
Score::operator<< (const char *name)
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

	for (int i = 0; i < hiscores.size(); i++)
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

void
Score::add_new_hiscore()
{
	auto cmp = [](const HighScore& a, const HighScore& b) -> bool {
		return a.score > b.score;
	};

	/* 
	 * Add our new score in the array in case it's higher
	 * than any of the existing entries. The array is sorted
	 * in descending order, so we'll search it backwards --
	 * this will have the effect of replacing the lower scores
	 * first.
	 */
	for (int i = hiscores.size() - 1; i >= 0; i--) {
		if (curscore > hiscores[i].score) {
			hiscores[i].score = curscore;
			(void)strncpy(hiscores[i].name, curname, 
			    sizeof(hiscores[i].name));
			break;
		}
	}
	std::sort(hiscores.begin(), hiscores.end(), cmp);
}
