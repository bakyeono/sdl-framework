#ifndef C_EXIT_CTRL_H
#define C_EXIT_CTRL_H

#include "../lib.h"

class CExitCtrl
{
private:
    CExitCtrl();
    ~CExitCtrl();

public:
    inline static bool IsExitCalled()
    {
        return is_exit_called;
    };

    inline static void CallExit()
    {
        is_exit_called = true;
    };

    inline static int GetExitStatus()
    {
        return exit_status;
    };

    inline static void SetExitStatus(int value)
    {
        exit_status = value;
    };

private:
    static bool is_exit_called;
    static int  exit_status;
};

#endif // C_EXIT_CTRL_H
