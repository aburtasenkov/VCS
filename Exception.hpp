#include <exception>
#include <string>

class Exception: public std::exception
{
public:
    explicit Exception()
    {   }

    explicit Exception(std::string s)
        :error_msg(s)
    {   }

    explicit Exception(std::string s, std::string f)
        :error_msg(s), error_location(f)
    {   }

    virtual ~Exception() noexcept
    {   }

    virtual const char* what() const noexcept
    {
        return error_msg.c_str();
    }

    virtual const std::string where() const noexcept
    {
        return error_location;
    }
protected:
    std::string error_msg;
    std::string error_location;
};