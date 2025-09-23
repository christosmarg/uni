#ifndef ERRLOG_HPP
#define ERRLOG_HPP

#include <fstream>
#include <string>

class ErrLog
{
    private:
        static constexpr const char *fpath = "res/errlog.txt";

    public:
        ErrLog() = default;

        void fclear() const;
        void write(std::string&& str) const;
};

#endif /* ERRLOG_HPP */
