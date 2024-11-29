#include "../Exception.hpp"
#include "../Repository.hpp"

Repository* read_cache()
// load data into Repository object
// return object containing loaded data
{
    if (!std::filesystem::exists("cached_data"))
        throw Exception{"Missing File Error: Repository uninitialized", "test.cpp"};

    std::ifstream ifs{"cached_data"};

    Repository* repo = new Repository{};

    ifs >> (*repo);

    ifs.close();

    return repo;
}

void save_cache(Repository* repo)
// save data from Repository object
{
    std::ofstream ofs{"cached_data_compare"};
    ofs << (*repo);
    ofs.close();
}

std::string bool_to_str(bool val)
{
    return (val ? "true" : "false");
}

int main(void)
{
    Repository* repo = read_cache();
    save_cache(repo);

    Document_Namespace::DocumentComparison comparison{Document_Namespace::Document{"cached_data"}, Document_Namespace::Document{"cached_data_compare"}};

    std::cout << "Repositories are saved and loaded correctly - " << bool_to_str(!comparison.is_modified()) << "\n";    

    return 0;
}