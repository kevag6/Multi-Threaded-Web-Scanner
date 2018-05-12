#include "UrlThread.h"
#include <wx/url.h>
#include <wx/textfile.h>

wxString output;

UrlThread::UrlThread(int aIndex)
{
    //ctor
    index = aIndex;

}

UrlThread::UrlThread(){};

UrlThread::~UrlThread()
{
    //dtor
}

void UrlThread::setIndex(int aIndex){
    index = aIndex;
}

int UrlThread::getIndex(){
    return index;
}

void *UrlThread::Entry()
{
    //Entry Method
    //wxMessageBox(wxT("testThread ran successfully"));
    ++counter;

    while(threadData[index].listpos <= threadData[index].listEnd) {
            wxString currentUrlPos;

            currentUrlPos.Printf(wxT("list position is %d of URL: "), threadData[index].listpos);
            currentUrlPos.Append(URLList[threadData[index].listpos]);

            programOut.AddLine(currentUrlPos);

            wxURL currentURL1(URLList[threadData[index].listpos]);

            if(currentURL1.GetError() == wxURL_NOERR){
                //put the page source into an input stream.
                wxInputStream* inStream = currentURL1.GetInputStream();

                //get the stream size to initialize the buffer.
                size_t size = inStream->GetSize();

                //initialize the buffer
                char* source = new char[size];

                //put the stream/source into the buffer.
                inStream->Read(source, size);

                //change the char buffer into a wxString for further analysis.
                wxString dest(source, wxConvUTF8);

                //Make the whole string lower case.
                dest.Lower();

                //wxMessageBox(dest);



                //outFile.AddLine(dest);

                results.Append(wxT("URL is: "));
                results.Append(URLList[threadData[index].listpos]);
                results.Append(wxT("\n"));

                for(size_t i = 0; i < WordList.GetCount(); i++){
                    //wxString searchString = WordList
                    //WordList[i].Append(wxT(" "));
                    size_t startPos = dest.find(WordList[i], 0);
                    int wordCount = 0;

                    //See if the word is in the dest string.
                    //if(startPos != 0)
                    //wxMessageBox(WordList[i]);

                    while(startPos != wxString::npos){
                        //threadData[index].cntWords++;
                        ++wordCount;
                        startPos = dest.find(WordList[i], startPos + 1);
                    }

                    wxString temp;
                    wxString finalString = WordList[i];

                    //results.Append(WordList[i]);
                    temp.Printf(wxT(" :word was found %d times"), wordCount);
                    finalString.Append(temp);

                    results.Append(temp);

                    results.Append(wxT("\n"));





                    programOut.AddLine(finalString);



                }

                delete source;
                delete inStream;
            }

        results.Append(wxT("\n"));
        programOut.AddLine(wxT("\n"));
        threadData[index].listpos++;

    }
    //outFile.AddLine(wxT("new thread"));
    results.Append(wxT("new thread"));
    //programOut.AddLine(wxT("New Thread!"));


    //outFile.Write();
    programOut.Write();
    sleep(1);
    ++threadsComplete;
    threadData[index].status = 1;

}
