#pragma once
class Logger
{
public:
    static Logger& GetInstance();
    void operator()(char const* message);

    ~Logger();
protected:
    Logger();
    void* file;
};

extern Logger& Log;

