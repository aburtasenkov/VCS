#include <chrono>
#include "Document.hpp"

namespace Commit_Namespace
{
    /*
    Commit structure:
        {
        HASH "COMMIT_COMMENT" 
        { "SOURCE_FILEPATH" "MODIFIED_FILEPATH" }
        { { REMOVED_LINE INDEX } { REMOVED_LINE INDEX } } 
        { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
        }
    */
    struct Filechange
    {
            std::filesystem::path source;
            std::filesystem::path modified;
            Document_Namespace::DocumentComparison changes;

            Filechange() {  }
            Filechange(const Document_Namespace::Document& doc1, const Document_Namespace::Document& doc2)
                :source(doc1.get_path()), modified(doc2.get_path())
            {
                changes = Document_Namespace::DocumentComparison{doc1, doc2};
            }

            friend std::istream& operator>>(std::istream& is, Filechange& c);
    };

    class Commit{
        public:
            Commit();
            Commit(const std::string& message);
            void push_back(const Filechange& fc);
            friend std::ostream& operator<<(std::ostream& os, const Commit& c);
            friend std::istream& operator>>(std::istream& is, Commit& c);
            bool is_pushed() const { return state; }
            void push() { state = commit_state::pushed; }
        private:
            enum commit_state
            {
                unpushed, pushed
            };
            commit_state state = unpushed;

            int hash_index;
            std::string commit_message;
            std::vector<Filechange> modified_files;
    };
    std::ostream& operator<<(std::ostream& os, const Commit& c);
    std::ostream& operator<<(std::ostream& os, const Filechange& c);
    std::istream& operator>>(std::istream& is, Filechange& c);
    std::istream& operator>>(std::istream& is, Commit& c);
}
