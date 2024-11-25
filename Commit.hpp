#include <chrono>
#include "Document.hpp"

namespace Commit_Namespace
{
    /*
    Commit structure:
        {
        HASH COMMIT_COMMENT 
        {  
        SOURCE_FILEPATH
        MODIFIED_FILEPATH
        { { REMOVED_LINE INDEX } { REMOVED_LINE INDEX } } 
        { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
        }
        }
    */
    struct Filechange
    {
            Document_Namespace::Document source;
            Document_Namespace::Document modified;
            Document_Namespace::DocumentComparison changes;

            Filechange() {  }
            Filechange(const Document_Namespace::Document& doc1, const Document_Namespace::Document& doc2)
                :source(doc1), modified(doc2)
            {
                changes = Document_Namespace::DocumentComparison{doc1, doc2};
            }
    };

    class Commit{
        public:
            Commit();
            Commit(const std::string& message);
            void push_back(const Filechange& fc);
            friend std::ostream& operator<<(std::ostream& os, const Commit& c);
            bool is_pushed() const { return state; }
            void push() { state = commit_state::pushed; }
        private:
            enum commit_state
            {
                unpushed, pushed
            };
            commit_state state = unpushed;

            std::string commit_message;
            std::chrono::time_point<std::chrono::system_clock> commit_timepoint;
            std::vector<Filechange> modified_files;

            int hash() const;
    };
    std::ostream& operator<<(std::ostream& os, const Commit& c);
}
