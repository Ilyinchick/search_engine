#include "../include/ConverterJSON.h"



int main() {
    ConverterJSON converter;
    InvertedIndex index;

    converter.testFilesForValid();
    index.UpdateDocumentBase(converter.GetTextDocuments());
    SearchServer server(index);
    server.setResponseLimit(converter.GetResponsesLimit());
    auto answers = server.search(converter.GetRequests());
    converter.putAnswers(answers);

    return 0;
}
