#include "ConverterJSON.h"


int main() {

    ConverterJSON converter;
    InvertedIndex index;

    try {
        converter.testFilesForValid();
        index.UpdateDocumentBase(converter.GetTextDocuments());
        SearchServer server(index);
        server.setResponseLimit(converter.GetResponsesLimit());
        auto answers = server.search(converter.GetRequests());
        converter.putAnswers(answers);
        std::cout << "Execution is complete!" << std::endl;
    } catch (ConfigFilesException &ex) {
        std::cout << ex.what() << std::endl;
    } catch (WriteToFileException &ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
