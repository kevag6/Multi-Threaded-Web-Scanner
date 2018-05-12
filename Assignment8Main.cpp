/***************************************************************
 * Name:      Assignment8Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    Kevin Grifo ()
 * Created:   2018-04-02
 * Copyright: Kevin Grifo ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "Assignment8Main.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/textfile.h>
#include <wx/arrstr.h>
#include <wx/url.h>
#include <wx/sstream.h>
#include<string>
#include <wx/stopwatch.h>
#include "UrlThread.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>



//Data Structures
//struct threadInfo {
//    UrlThread *thread;
//    int status;   //1 - done, 0 - working
//    int cntWords;
//    int listStart;
//    int listEnd;
//    int listpos;
//};

struct passwd *pw = getpwuid(getuid());

const char *homedir = pw->pw_dir;

wxString outputFileName(homedir, wxConvUTF8);




wxArrayString URLList;
wxArrayString WordList;
struct threadInfo threadData[10];
int numThreads = 0;
int threadsComplete = 0;
wxString dest;
int counter = 0;
//wxTextFile outFile(wxT("/home/kevag6/Untitled Document"));
wxTextFile programOut;
wxString results;




//(*InternalHeaders(Assignment8Frame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(Assignment8Frame)
const long Assignment8Frame::ID_STATICTEXT1 = wxNewId();
const long Assignment8Frame::ID_TEXTCTRL1 = wxNewId();
const long Assignment8Frame::ID_BUTTON1 = wxNewId();
const long Assignment8Frame::ID_STATICTEXT2 = wxNewId();
const long Assignment8Frame::ID_TEXTCTRL2 = wxNewId();
const long Assignment8Frame::ID_BUTTON2 = wxNewId();
const long Assignment8Frame::ID_STATICTEXT3 = wxNewId();
const long Assignment8Frame::ID_GAUGE1 = wxNewId();
const long Assignment8Frame::ID_STATICTEXT4 = wxNewId();
const long Assignment8Frame::ID_SPINCTRL1 = wxNewId();
const long Assignment8Frame::ID_STATICTEXT5 = wxNewId();
const long Assignment8Frame::ID_TEXTCTRL3 = wxNewId();
const long Assignment8Frame::ID_STATICTEXT6 = wxNewId();
const long Assignment8Frame::ID_STATICTEXT7 = wxNewId();
const long Assignment8Frame::ID_BUTTON3 = wxNewId();
const long Assignment8Frame::ID_PANEL1 = wxNewId();
const long Assignment8Frame::idMenuQuit = wxNewId();
const long Assignment8Frame::idMenuAbout = wxNewId();
const long Assignment8Frame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Assignment8Frame,wxFrame)
    //(*EventTable(Assignment8Frame)
    //*)
END_EVENT_TABLE()

Assignment8Frame::Assignment8Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(Assignment8Frame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(500,500), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(0,0));
    Panel1->SetMaxSize(wxSize(500,500));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("URL File"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("Choose Url File"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    BoxSizer2->Add(TextCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("Select"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Word File"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl2 = new wxTextCtrl(Panel1, ID_TEXTCTRL2, _("Choose Word"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer3->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button2 = new wxButton(Panel1, ID_BUTTON2, _("Select"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer3->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer7 = new wxBoxSizer(wxVERTICAL);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Progress"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer7->Add(StaticText3, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
    ProgressBar = new wxGauge(Panel1, ID_GAUGE1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAUGE1"));
    BoxSizer7->Add(ProgressBar, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("# of Threads"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer4->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ThreadAmt = new wxSpinCtrl(Panel1, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 1, 10, 0, _T("ID_SPINCTRL1"));
    ThreadAmt->SetValue(_T("0"));
    BoxSizer4->Add(ThreadAmt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _("URL Left:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer5->Add(StaticText5, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
    TextCtrl3 = new wxTextCtrl(Panel1, ID_TEXTCTRL3, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    BoxSizer5->Add(TextCtrl3, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
    BoxSizer1->Add(BoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT6, _("Time in ms:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer6->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Time = new wxStaticText(Panel1, ID_STATICTEXT7, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    BoxSizer6->Add(Time, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    showButton = new wxButton(Panel1, ID_BUTTON3, _("Show"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer6->Add(showButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer1);
    SetSizer(BoxSizer1);
    Layout();
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&Assignment8Frame::OnTextCtrl1Text);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Assignment8Frame::OnButton1Click);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&Assignment8Frame::OnTextCtrl2Text);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Assignment8Frame::OnButton2Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Assignment8Frame::OnshowButtonClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Assignment8Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Assignment8Frame::OnAbout);
    //*)
}

Assignment8Frame::~Assignment8Frame()
{
    //(*Destroy(Assignment8Frame)
    //*)
}

void Assignment8Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Assignment8Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

//URL Button
void Assignment8Frame::OnTextCtrl1Text(wxCommandEvent& event)
{
}

void Assignment8Frame::OnTextCtrl2Text(wxCommandEvent& event){}

//URL Button
void Assignment8Frame::OnButton1Click(wxCommandEvent& event)
{
    wxString file;
    wxFileDialog fdlog(this);

    // Show file dialog and get the path to
    // the file that was selected.
    if(fdlog.ShowModal() != wxID_OK) return;
    file.Clear();
    file = fdlog.GetPath();

    wxString str;

    //open the file
    wxTextFile tfile;
    tfile.Open(file);

    TextCtrl1->ChangeValue(file);

    int lineCount = (int) tfile.GetLineCount();


    wxString Foobar;
    Foobar.Printf( wxT("There are %d URLs that we will search."), lineCount);
    wxMessageBox(Foobar);
    //Used to iterate through URL list.
    int i = 0;

    // read the first line
    str = tfile.GetFirstLine();
    //wxMessageBox(str );

    //wxString listURL[lineCount];

    //Save the firstline into the first section in the array.
    //listURL[i] = str;
    URLList.Add(str, 1);
    ++i;
    // read all lines one by one
    // until the end of the file.
    while(!tfile.Eof()){
        if(i == lineCount){
            break;
        }
        str = tfile.GetNextLine();
        //wxMessageBox(str);
        //listURL[i] = str;
        URLList.Add(str, 1);
        ++i;
    }
    //wxMessageBox(URLList.Item(1));
}

//Word List Button
void Assignment8Frame::OnButton2Click(wxCommandEvent& event)
{
    wxString file;
    wxFileDialog fdlog(this);

    // Show file dialog and get the path to
    // the file that was selected.
    if(fdlog.ShowModal() != wxID_OK) return;
    file.Clear();
    file = fdlog.GetPath();

    wxString str;

    //open the file
    wxTextFile tfile;
    tfile.Open(file);

    //Updates text in textCtrl2 to file path.
    TextCtrl2->ChangeValue(file);

    int lineCount = (int) tfile.GetLineCount();



    //Used to iterate through URL list.
    int i = 0;

    // read the first line
    str = tfile.GetFirstLine();
    //wxMessageBox(str);

    //Save the firstline into the first section in the array.
    WordList.Add(str, 1);
    ++i;
    // read all lines one by one
    // until the end of the file.
    while(!tfile.Eof()){
        if(i == lineCount){
            break;
        }
        str = tfile.GetNextLine();
        //wxMessageBox(str);
        WordList.Add(str, 1);
        ++i;
    }
    //wxMessageBox(WordList[0]);
}

void assignThreads()
{
    // Algorithm to compute sublist for each thread
    int numUrls = URLList.Count();
    int urlBlockSize = 0;
    if (numUrls >= numThreads) {
        urlBlockSize = numUrls / numThreads;
        int ls = 0;
        int le = 0;
        int i;
        for (i = 0; i <numThreads-1; i++){
            ls = le;
            le = le+urlBlockSize;

            threadData[i].status = 0;
            threadData[i].listStart = ls;
            threadData[i].listEnd = le-1;
            threadData[i].listpos = ls;
            threadData[i].cntWords =0;
        }
        ls = le;
        threadData[i].status = 0;
        threadData[i].listStart = ls;
        threadData[i].listEnd = numUrls-1;
        threadData[i].listpos = ls;
        threadData[i].cntWords = 0;
    }
    else {

        threadData[0].status = 0;
        threadData[0].listStart = 0;
        threadData[0].listEnd = numUrls-1;
        threadData[0].listpos = 0;
        threadData[0].cntWords = 0;
    }

}

int progressBarValue;
int fileFlag = 0;

//Shows the urls and number of matching words.
void Assignment8Frame::OnshowButtonClick(wxCommandEvent& event)
{
    threadsComplete = 0;
    //outputFileName.Append(homedirWx);
    if(!fileFlag){
        outputFileName.Append(wxT("/programOutput"));
        fileFlag = 1;
    }


    //programOut()

    wxStopWatch sw;

    numThreads = ThreadAmt->GetValue();

     progressBarValue = URLList.GetCount() / numThreads;

    assignThreads();

    wxString Foobar;
    Foobar.Printf( wxT("There are %d threads"), numThreads);
    wxMessageBox(Foobar);

    //outFile.Open();
    programOut.Create(outputFileName);
    programOut.Open();

    //ProgressBar->SetValue(50);

    for(int i = 0; i < numThreads; i++){
        //threadData[i].thread->Run();
        //wxMessageBox(wxT("In For loop"));
        threadData[i].thread = new UrlThread(i);
        threadData[i].thread->Create();
        //threadData[i].thread->setIndex(i);
        if ( threadData[i].thread->Run() != wxTHREAD_NO_ERROR )
        {
            wxMessageBox(wxT("Can't create the thread!"));
            delete threadData[i].thread;
            threadData[i].thread = NULL;
        }
    }


    //outFile.Close();
    programOut.Close();

    long swMilliTime = sw.Time();

    wxString strLong = wxString::Format(wxT("%ld"), swMilliTime);

    Time->SetLabel(strLong);

    sw.Pause();


    //UrlThread *testThread;
    //testThread = new UrlThread(0);

    sleep(2);

    ProgressBar->SetValue(100);


//    wxString printCounter;
//    printCounter.Printf(wxT("Counter is %d and index is %d"), counter, threadData[0].thread->getIndex());
//    wxMessageBox(printCounter);
//
//    wxString UrlListValues;
//    UrlListValues.Printf(wxT("List start is %d, and list end is %d, thread execution took %ld, listpos contains URL, threadsComplete is %d "), threadData[0].listStart, threadData[0].listEnd,
//                          swMilliTime, threadsComplete);
//    wxMessageBox(UrlListValues);

    //wxMessageBox(wxT(""));
    //wxMessageBox(URLList[threadData[0].listpos]);

    wxString finalMessage = wxT("Output will be printed in file: ");
    finalMessage.Append(outputFileName);


    wxMessageBox(finalMessage);


}



void Assignment8Frame::OnIdle(wxIdleEvent& event){


    if(threadsComplete < numThreads){
        ProgressBar->SetValue(progressBarValue);
    }

    if(threadsComplete == numThreads){
        wxMessageBox(_("Finished"));
    }

    event.Skip();
}


