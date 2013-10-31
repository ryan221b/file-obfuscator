/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * FileObfuscator
 * Copyright (C) 2013 Ryan Babb <ryan221b@gmail.com>
 * 
 * FileObfuscator is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FileObfuscator is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _APPWINDOW_H_
#define _APPWINDOW_H_

#include "gtkmm.h"

class AppWindow : public Gtk::Window 
{
public:
	AppWindow();
	virtual ~AppWindow();
	
protected:
	// Signal handlers:
	void on_button_scramble();
	void on_button_quit();
	void on_buffer_changed();
	void on_infobar_response(int);
	
	// Child widgets:
	Gtk::Box m_VBox_Top;
	Gtk::Box m_HBox_File, m_HBox_Key;
	
	Gtk::InfoBar m_InfoBar;
	Gtk::Label   m_Info_Label;

	Gtk::Label m_Label_File, m_Label_Key;
	Gtk::Entry m_Entry_File, m_Entry_Key;
	Glib::RefPtr<Gtk::EntryBuffer> m_refFileBuffer, m_refKeyBuffer;

	Gtk::ButtonBox m_ButtonBox;
	Gtk::Button	   m_Button_Scramble, m_Button_Quit;
};

#endif // _APPWINDOW_H_

