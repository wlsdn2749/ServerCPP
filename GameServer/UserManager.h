#pragma once
#include <mutex>
#include "Types.h"

class User
{
    //Todo  
};

class UserManager
{
public:
    static UserManager* Instance()
    {
        static UserManager instance;
        return &instance;
    }

    User* GetUser(int32 id)
    {
        std::lock_guard<std::mutex> guard(_mutex);
        return nullptr;
    }

    void ProcessSave();

private:
    std::mutex _mutex;
};