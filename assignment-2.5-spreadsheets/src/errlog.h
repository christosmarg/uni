#ifndef ERRLOG_H
#define ERRLOG_H

#include <fstream>
#include "xstring.h"

class ErrLog
{
    private:
        static constexpr const char *fpath = "res/errlog.csv";
        void fclear() const;

    public:
        enum class ErrType {
            STUDENT_MISSING,
            COURSE_MISSING,
            DIFFERENT_GRADES
        };

        ErrLog();
        void write(ErrType type, const lab::xstring& s) const;
};

#endif /* ERRLOG_H */
