/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * fileobfuscator
 * Copyright (C) 2013 Ryan Babb <ryan221b@gmail.com>
 * 
 * fileobfuscator is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * fileobfuscator is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AppWindow.h"
#include "Crypto.h"
#include "BinaryData.h" 
#include <iostream>

/* AppWindow():
 *  GUI constructor
 */
AppWindow::AppWindow()
: m_VBox_Top(Gtk::ORIENTATION_VERTICAL, 10),
  m_Label_File("File: "),
  m_Label_Key("Key: "),
  m_ButtonBox(Gtk::ORIENTATION_HORIZONTAL),
  m_Button_Scramble("_Scramble", true),
  m_Button_Quit("_Quit", true)
{
	set_title("File Obfuscator");
	set_border_width(10);

	// Add Layout:
	add(m_VBox_Top);

	
	// Setup InfoBar:
	Gtk::Container *infoBarContainer = 
		dynamic_cast<Gtk::Container *>(m_InfoBar.get_content_area());
	
	if(infoBarContainer)
		infoBarContainer->add(m_Label_Info);
	
	m_InfoBar.add_button("_OK", 0);

	m_InfoBar.signal_response().connect(sigc::mem_fun(*this,
			&AppWindow::on_infobar_response));
	
	m_VBox_Top.pack_start(m_InfoBar, Gtk::PACK_SHRINK);

	
	// Setup File box:
	m_Entry_File.signal_changed().connect(sigc::mem_fun(*this,
			&AppWindow::on_entrys_changed));

	m_HBox_File.pack_start(m_Label_File, Gtk::PACK_SHRINK, 5);
	m_HBox_File.pack_end(m_Entry_File, Gtk::PACK_EXPAND_WIDGET, 5);

	m_VBox_Top.pack_start(m_HBox_File, Gtk::PACK_EXPAND_PADDING, 5);

	
	// Setup Key box:
	m_Entry_Key.signal_changed().connect(sigc::mem_fun(*this,
			&AppWindow::on_entrys_changed));

	m_Entry_Key.set_visibility(false);
	
	m_HBox_Key.pack_start(m_Label_Key, Gtk::PACK_SHRINK, 5);
	m_HBox_Key.pack_end(m_Entry_Key, Gtk::PACK_EXPAND_WIDGET, 5);

	m_VBox_Top.pack_start(m_HBox_Key, Gtk::PACK_EXPAND_PADDING, 5);

	
	// Setup ButtonBox:
	m_Button_Scramble.signal_clicked().connect(sigc::mem_fun(*this,
			&AppWindow::on_button_scramble));
	
	m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
			&AppWindow::on_button_quit));

	m_ButtonBox.set_layout(Gtk::BUTTONBOX_SPREAD);
	m_ButtonBox.set_homogeneous(true);

	m_ButtonBox.add(m_Button_Scramble);
	m_ButtonBox.add(m_Button_Quit);

	m_VBox_Top.pack_end(m_ButtonBox);

	
	// Show all widgets:
	show_all_children();

	// Hide InfoBar:
	m_InfoBar.hide();

	// Deactivate 'Scramble' button:
	m_Button_Scramble.set_sensitive(false);
}


/* ~AppWindow():
 *  GUI destructor
 */
AppWindow::~AppWindow()
{
}


/* on_entrys_changed():
 *  Detect changes to Gtk::Entry widgets and
 *  activate/deactivate 'Scramble' button
 *  when any/both of them are empty
 */
void AppWindow::on_entrys_changed()
{

	bool flag = (m_Entry_File.get_text_length())
		&& (m_Entry_Key.get_text_length());
	m_Button_Scramble.set_sensitive(flag);
}


/* on_infobar_response():
 *  Erase InfoBar label's text and hide
 *  the InfoBar widget when 'OK' is clicked
 */
void AppWindow::on_infobar_response(int)
{
	m_Label_Info.set_text("");
	m_InfoBar.hide();
}


/* on_button_scramble():
 *  Apply encoding algorith to file by
 *  looping through it's contents and
 *  XORing each byte with a byte in the key
 */
void AppWindow::on_button_scramble()
{
	try
	{
		xor_scramble(m_Entry_Key.get_text(), m_Entry_File.get_text());
	}
	catch (const BinaryData::BinDataError &err)
	{
		m_Label_Info.set_text(err.what());
		m_InfoBar.set_message_type(Gtk::MESSAGE_ERROR);
		m_InfoBar.show();
		return;
	}

	// All fine:
	m_Label_Info.set_text(m_Entry_File.get_text()+ ".obf written successfully!");
	m_InfoBar.set_message_type(Gtk::MESSAGE_INFO);
	m_InfoBar.show();
}


/* on_button_quit():
 *  Close window and exit application
 */
void AppWindow::on_button_quit()
{
	hide();
}