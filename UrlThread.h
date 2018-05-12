#ifndef URLTHREAD_H
#define URLTHREAD_H

#include <wx/textfile.h>

class UrlThread;

//Data Structures
 struct threadInfo {
    UrlThread *thread;
    int status;   //1 - done, 0 - working
    int cntWords;
    int listStart;
    int listEnd;
    int listpos;
};

extern struct threadInfo threadData[10];
extern int numThreads;
extern int threadsComplete;
extern wxArrayString URLList;
extern wxArrayString WordList;
extern wxString dest;
extern int counter;
//extern wxTextFile outFile;
extern wxTextFile programOut;
extern wxString results;

class UrlThread: public wxThread
{

    public:
        UrlThread(int index);

        UrlThread();

        virtual ~UrlThread();

        virtual void *Entry();

        void setIndex(int aIndex);

        int getIndex();



    protected:

    private:
        int index;
};

#endif // URLTHREAD_H
