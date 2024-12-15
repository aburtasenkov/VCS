#include <ctime>
#include "Document.hpp"

namespace Commit_Namespace
{
/*
Commit structure:
COMMIT_TIMEPOINT COMMIT_MESSAGE COMMITED_STATE_PATH STAGED_STATE_PATH {}/{} COMMITED_STATE_PATH STAGED_STATE_PATH {}/{}
COMMIT_TIMEPOINt COMMIT_MESSAGE COMMITED_STATE_PATH STAGED_STATE_PATH {{{REMOVED_LINE}REMOVED_LINE_INDEX}}/{} COMMITED_STATE_PATH STAGED_STATE_PATH {{{INSERTED_LINE}INSERTED_LINE_INDEX}}/{}
*/
    const int FILEPATH_LENGHT_TO_MODIFIED_STATE = 2;    // amount of directories until VCS/commited_state

    std::filesystem::path skip_n_parents(const std::filesystem::path& path, int n);

    struct Filechange
    {
            std::filesystem::path source;
            std::filesystem::path modified;
            Document_Namespace::DocumentComparison changes;

            Filechange() {  }
            Filechange(const Document_Namespace::Document& doc1, const Document_Namespace::Document& doc2)
                :source(skip_n_parents(doc1.get_path(), FILEPATH_LENGHT_TO_MODIFIED_STATE)), modified(skip_n_parents(doc2.get_path(), FILEPATH_LENGHT_TO_MODIFIED_STATE))
            {
                std::cout << source << "\t" << modified << "\n";
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
            friend std::istream& operator>>(std::istream& is, std::tm& timepoint);
            friend std::ostream& operator<<(std::ostream& os, const std::tm& timepoint);
            bool is_pushed() const { return state; }
            void push() { state = commit_state::pushed; }
            std::vector<Filechange>& get_changes() { return modified_files; }
        private:
            enum commit_state
            {
                unpushed, pushed
            };
            commit_state state = unpushed;

            std::tm timepoint;
            std::string commit_message;
            std::vector<Filechange> modified_files;
    };
    std::ostream& operator<<(std::ostream& os, const Commit& c);
    std::ostream& operator<<(std::ostream& os, const Filechange& c);
    std::ostream& operator<<(std::ostream& os, const std::tm& timepoint);
    std::istream& operator>>(std::istream& is, Filechange& c);
    std::istream& operator>>(std::istream& is, Commit& c);
    std::istream& operator>>(std::istream& is, std::tm& timepoint);
}
