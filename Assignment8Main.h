/***************************************************************
 * Name:      Assignment8Main.h
 * Purpose:   Defines Application Frame
 * Author:    Kevin Grifo ()
 * Created:   2018-04-02
 * Copyright: Kevin Grifo ()
 * License:
 **************************************************************/

#ifndef ASSIGNMENT8MAIN_H
#define ASSIGNMENT8MAIN_H

//(*Headers(Assignment8Frame)
#include <wx/gauge.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class Assignment8Frame: public wxFrame
{
    public:

        Assignment8Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Assignment8Frame();
        void OnIdle(wxIdleEvent& event);

    private:

        //(*Handlers(Assignment8Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnTextCtrl2Text(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnshowButtonClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(Assignment8Frame)
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL2;
        static const long ID_BUTTON2;
        static const long ID_STATICTEXT3;
        static const long ID_GAUGE1;
        static const long ID_STATICTEXT4;
        static const long ID_SPINCTRL1;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_BUTTON3;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(Assignment8Frame)
        wxSpinCtrl* ThreadAmt;
        wxTextCtrl* TextCtrl3;
        wxPanel* Panel1;
        wxStatusBar* StatusBar1;
        wxStaticText* Time;
        wxButton* Button1;
        wxButton* Button2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxTextCtrl* TextCtrl1;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText2;
        wxGauge* ProgressBar;
        wxStaticText* StaticText6;
        wxButton* showButton;
        wxTextCtrl* TextCtrl2;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // ASSIGNMENT8MAIN_H
