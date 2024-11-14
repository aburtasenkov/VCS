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

    explicit Exception(std::string s, std::pair<std::string, int> location)
        :error_msg(s), error_location(location)
    {   }

    virtual ~Exception() noexcept
    {   }

    virtual const char* what() const noexcept
    {
        return error_msg.c_str();
    }

    virtual const std::pair<const std::string, const int> location() const noexcept
    {
        return error_location;
    }
protected:
    std::string error_msg;
    std::pair<const std::string, const int> error_location;
};