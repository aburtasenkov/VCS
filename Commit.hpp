#include <ctime>
#include "Document.hpp"

namespace Commit_Namespace
{
/*
Commit structure:
COMMIT_TIMEPOINT COMMIT_MESSAGE COMMITED_STATE_PATH STAGED_STATE_PATH {}/{} COMMITED_STATE_PATH STAGED_STATE_PATH {}/{}
COMMIT_TIMEPOINt COMMIT_MESSAGE COMMITED_STATE_PATH STAGED_STATE_PATH {{{REMOVED_LINE}REMOVED_LINE_INDEX}}/{} COMMITED_STATE_PATH STAGED_STATE_PATH {{{INSERTED_LINE}INSERTED_LINE_INDEX}}/{}
*/
    const int VCS_CHANGED_STATE_CHAR_COUNT = 17;

    struct Filechange
    {
            std::filesystem::path filename;
            Document_Namespace::DocumentComparison changes;

            Filechange() {  }
            Filechange(const Document_Namespace::Document& doc1, const Document_Namespace::Document& doc2)
                :filename(ignore_first_n_chars(doc2.get_path(), VCS_CHANGED_STATE_CHAR_COUNT))
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
            friend std::istream& operator>>(std::istream& is, std::tm& timepoint);
            friend std::ostream& operator<<(std::ostream& os, const std::tm& timepoint);
            bool is_pushed() const { return state; }
            void push() { state = commit_state::pushed; }
            bool contains_changes();
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
