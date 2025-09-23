#ifndef ERRLOG_HPP
#define ERRLOG_HPP

#include <fstream>
#include "xstring.hpp"

class ErrLog
{
    private:
        static constexpr const char *fpath = "res/errlog.csv";
        void fclear() const;

    public:
        enum class ErrType {
            STUDENT_MISSING,
            COURSE_MISSING,
            DIFFERENT_GRADES,
            RUNTIME_ERR
        };

        ErrLog();
        void write(ErrType type, const lab::xstring& s) const;
};

#endif /* ERRLOG_HPP */
