#include "errlog.hpp"

void
ErrLog::fclear() const
{
    std::ofstream f;
    f.open(fpath, std::ofstream::trunc);
    f.close();
}

void
ErrLog::write(const std::string& str) const
{
    std::ofstream f;
    f.open(fpath, std::ios_base::app);
    f << str << std::endl;
    f.close();
}
