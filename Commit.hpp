#include "./Document/Document.hpp"

namespace Commit_Namespace
{
    /*
        A single Commit followed by another commit:
    {
        HASH { 
            SOURCE_FILEPATH
            MODIFIED_FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
             {
            SOURCE_FILEPATH
            MODIFIED_FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
    }
    {
        HASH { 
            SOURCE_FILEPATH
            MODIFIED_FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
             {
            SOURCE_FILEPATH
            MODIFIED_FILEPATH
                { INDEX INDEX } 
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
            Commit() {  }
            void push_back(const Filechange& fc);
            std::ostream& output(std::ostream& os, const std::string& indentation = "\t") const;
        private:
            std::string hash_value;
            std::vector<Filechange> modified_files;
    };
}