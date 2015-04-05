/***************************************************************************
 *            Fl_RPNCalc.cc
 *
 *  Sunday Aug 22 23:16:21 2004
 *  Copyright  2004  Robert Arkiletian
 *  Email fltk_beginner_tutorial AT yahoo DOT com
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


// Note: please change the fltk-config script in /usr/local/bin to use g++
// instead of gcc before compiling.


#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <cmath>		//only for sqrt
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

//-------------------------------------------

class MyOutput:public Fl_Output
{
public:
	
	MyOutput (int x, int y, int w, int h)
		:Fl_Output (x,y,w,h)
	
	{
		textfont (FL_COURIER_BOLD);	//fixed width font
		textsize (24);
	}

	/*
		this overloaded handle function prevents the Output box (Display) from 
		consuming a keydown event when it has focus so the window (calculator) 
		will continue searching for a shortcut event
	*/
	
	int handle (int e)
	{
		int ret = Fl_Output::handle (e);
		
		if ((e == FL_KEYDOWN) && (ret==1)) 
			ret=0;		
		return (ret);   
	}
};

//-------------------------------------------

class MyButton:public Fl_Button
{

      public:
	int mycolor;
	MyButton (int x, int y, int w, int h, const char *l)
		:Fl_Button (x,y,w,h,l)
	
	{
		box (FL_PLASTIC_UP_BOX);
		labelsize (18);
		labelfont (FL_COURIER_BOLD);	//constant width font for rightjustify
		mycolor = FL_BACKGROUND_COLOR;
	}

	int handle (int e)
	{
		int ret = Fl_Button::handle (e);
		switch (e)
		{

		case FL_ENTER:
			color (FL_BLUE);
			redraw();
			break;

		case FL_LEAVE:
			color (mycolor);
			redraw();
			break;


		case FL_SHORTCUT:
			if (Fl::event_key() == shortcut())
			{
				box (FL_PLASTIC_DOWN_BOX);
				redraw();
			}
			break;

		case FL_KEYUP:
			if (Fl::event_key() == shortcut())
			{
				box (FL_PLASTIC_UP_BOX);
				redraw();
				ret=1; //return handled so keyup event propagation stops
			}
			break;

		}
		return (ret);
	}
};

//---------------------------------------------------

class Fl_RPNCalc:public Fl_Window
{

      public:
		  
	Fl_RPNCalc (int , int , const char *);
	~Fl_RPNCalc();
	MyButton *key1;
	MyButton *key2;
	MyButton *key3;
	MyButton *key4;
	MyButton *key5;
	MyButton *key6;
	MyButton *key7;
	MyButton *key8;
	MyButton *key9;
	MyButton *key0;
	MyButton *dec;
	MyButton *mult;
	MyButton *div;
	MyButton *add;
	MyButton *sub;
	MyButton *clr;
	MyButton *ent;
	MyButton *pm;
	MyButton *rcl;
	MyButton *sto;
	MyButton *sum;
	MyButton *sqr;
	MyButton *back;
	MyButton *clrstck;
	Fl_Output *disp;
	Fl_Menu_Bar *menu;

      private:

	enum state
	{ enter, operation, key }; // to keep track of the last operation
	state return_state;
	vector < double > stack;
	double mem;
	char digits[40];
	static const int dw;	//Display Width
	static const char zeros[11];

	static void cb_key1 (Fl_Widget *, void *);
	static void cb_key2 (Fl_Widget *, void *);
	static void cb_key3 (Fl_Widget *, void *);
	static void cb_key4 (Fl_Widget *, void *);
	static void cb_key5 (Fl_Widget *, void *);
	static void cb_key6 (Fl_Widget *, void *);
	static void cb_key7 (Fl_Widget *, void *);
	static void cb_key8 (Fl_Widget *, void *);
	static void cb_key9 (Fl_Widget *, void *);
	static void cb_key0 (Fl_Widget *, void *);
	static void cb_dec (Fl_Widget *, void *);
	static void cb_mult (Fl_Widget *, void *);
	static void cb_div (Fl_Widget *, void *);
	static void cb_add (Fl_Widget *, void *);
	static void cb_sub (Fl_Widget *, void *);
	static void cb_clr (Fl_Widget *, void *);
	static void cb_ent (Fl_Widget *, void *);
	static void cb_pm (Fl_Widget *, void *);
	static void cb_rcl (Fl_Widget *, void *);
	static void cb_sto (Fl_Widget *, void *);
	static void cb_sum (Fl_Widget *, void *);
	static void cb_sqr (Fl_Widget *, void *);
	static void cb_back (Fl_Widget *, void *);
	static void cb_clrstck (Fl_Widget *, void *);
	
	static void cb_quit (Fl_Widget *, void *);
	static void cb_about (Fl_Widget *, void *);
	static void cb_license (Fl_Widget *, void *);

	inline void cb_key1_i();
	inline void cb_key2_i();
	inline void cb_key3_i();
	inline void cb_key4_i();
	inline void cb_key5_i();
	inline void cb_key6_i();
	inline void cb_key7_i();
	inline void cb_key8_i();
	inline void cb_key9_i();
	inline void cb_key0_i();
	inline void cb_dec_i();
	inline void cb_mult_i();
	inline void cb_div_i();
	inline void cb_add_i();
	inline void cb_sub_i();
	inline void cb_clr_i();
	inline void cb_ent_i();
	inline void cb_pm_i();
	inline void cb_rcl_i();
	inline void cb_sto_i();
	inline void cb_sum_i();
	inline void cb_sqr_i();
	inline void cb_back_i();
	inline void cb_clrstck_i();
	
	void rightjustify();
	void stripzeros();
	void stripblanks();
	void viewable();
	int countchar();

};

const char
	Fl_RPNCalc::zeros[] = "0000000000"; // to display errors eg. div by 0
const int
	Fl_RPNCalc::dw = 11; // the mantissa length

//----------------------------------------------------

int
main()
{

	Fl_RPNCalc calc (205,430,"Fl_RPNCalc");
	return Fl::run();
}

//----------------------------------------------------

Fl_RPNCalc::Fl_RPNCalc (int w, int h, const char *title)
	:Fl_Window (w, h, title)
{

	begin();

	key1 = new MyButton (15, 335, 40, 40, "1");
	key1->callback ( cb_key1, this);
	key1->shortcut (FL_KP + '1');

	key2 = new MyButton (60, 335, 40, 40, "2");
	key2->callback ( cb_key2, this);
	key2->shortcut (FL_KP + '2');

	key3 = new MyButton (105, 335, 40, 40, "3");
	key3->callback ( cb_key3, this);
	key3->shortcut (FL_KP + '3');

	key4 = new MyButton (15, 290, 40, 40, "4");
	key4->callback ( cb_key4, this);
	key4->shortcut (FL_KP + '4');

	key5 = new MyButton (60, 290, 40, 40, "5");
	key5->callback ( cb_key5, this);
	key5->shortcut (FL_KP + '5');

	key6 = new MyButton (105, 290, 40, 40, "6");
	key6->callback ( cb_key6, this);
	key6->shortcut (FL_KP + '6');

	key7 = new MyButton (15, 245, 40, 40, "7");
	key7->callback ( cb_key7, this);
	key7->shortcut (FL_KP + '7');

	key8 = new MyButton (60, 245, 40, 40, "8");
	key8->callback ( cb_key8, this);
	key8->shortcut (FL_KP + '8');

	key9 = new MyButton (105, 245, 40, 40, "9");
	key9->callback ( cb_key9, this);
	key9->shortcut (FL_KP + '9');

	key0 = new MyButton (15, 380, 85, 40, "0");
	key0->callback ( cb_key0, this);
	key0->shortcut (FL_KP + '0');

	dec = new MyButton (105, 380, 40, 40, ".");
	dec->callback ( cb_dec, this);
	dec->shortcut (FL_KP + '.');

	mult = new MyButton (105, 200, 40, 40, "*");
	mult->callback ( cb_mult, this);
	mult->shortcut (FL_KP + '*');

	div = new MyButton (60, 200, 40, 40, "/");
	div->callback ( cb_div, this);
	div->shortcut (FL_KP + '/');

	add = new MyButton (150, 245, 40, 85, "+");
	add->callback ( cb_add, this);
	add->shortcut (FL_KP + '+');

	sub = new MyButton (150, 200, 40, 40, "-");
	sub->callback ( cb_sub, this);
	sub->shortcut (FL_KP + '-');

	clr = new MyButton (65, 145, 40, 40, "C");
	clr->callback ( cb_clr, this);
	clr->shortcut (FL_Delete);
	clr->tooltip ("Delete");
	clr->color (FL_YELLOW);
	clr->redraw();
	clr->mycolor = FL_YELLOW;

	ent = new MyButton (150, 335, 40, 85, "E\nN\nT\nE\nR");
	ent->labelsize (16);
	ent->callback ( cb_ent, this);
	ent->shortcut (FL_KP_Enter);
	ent->tooltip ("Keypad Enter");

	pm = new MyButton (155, 145, 40, 40, "+/-");
	pm->callback ( cb_pm, this);
	pm->shortcut (FL_Page_Down);
	pm->tooltip ("Page Down");
	pm->color (FL_YELLOW);
	pm->redraw();
	pm->mycolor = FL_YELLOW;

	rcl = new MyButton (110, 100, 40, 40, "RCL");
	rcl->callback ( cb_rcl, this);
	rcl->shortcut (FL_Home);
	rcl->tooltip ("Home");
	rcl->color (FL_YELLOW);
	rcl->redraw();
	rcl->mycolor = FL_YELLOW;

	sto = new MyButton (155, 100, 40, 40, "STO");
	sto->callback ( cb_sto, this);
	sto->shortcut (FL_Page_Up);
	sto->tooltip ("Page Up");
	sto->color (FL_YELLOW);
	sto->redraw();
	sto->mycolor = FL_YELLOW;

	sum = new MyButton (65, 100, 40, 40, "SUM");
	sum->callback ( cb_sum, this);
	sum->shortcut (FL_Insert);
	sum->tooltip ("Insert");
	sum->color (FL_YELLOW);
	sum->redraw();
	sum->mycolor = FL_YELLOW;

	sqr = new MyButton (110, 145, 40, 40, "SQR");
	sqr->callback ( cb_sqr, this);
	sqr->shortcut (FL_End);
	sqr->tooltip ("End");
	sqr->color (FL_YELLOW);
	sqr->redraw();
	sqr->mycolor = FL_YELLOW;

	back = new MyButton (10, 100, 40, 40, "<-");
	back->callback ( cb_back, this);
	back->shortcut (FL_BackSpace);
	back->tooltip ("Backspace");
	back->color (FL_MAGENTA);
	back->redraw();
	back->mycolor = FL_MAGENTA;
	
	clrstck = new MyButton (10, 145, 40, 40, "AC");
	clrstck->callback ( cb_clrstck, this);
	clrstck->shortcut (92);
	clrstck->tooltip ("Backslash");
	clrstck->color (FL_MAGENTA);
	clrstck->redraw();
	clrstck->mycolor = FL_MAGENTA;

	disp = new MyOutput (10, 35, 185, 50);
	
	menu = new Fl_Menu_Bar (0, 0, 205, 30);
	menu->box (FL_FLAT_BOX);
	menu->add ("File/Exit", 0,  cb_quit,this);
	menu->add ("Help/About", 0,  cb_about);
	menu->add ("Help/License", 0,  cb_license);

	end();
	
	stack.push_back (0);
	mem = 0;
	return_state = key;
	show();
}

//----------------------------------------------------

Fl_RPNCalc::~Fl_RPNCalc()
{
}

//----------------------------------------------------

void
Fl_RPNCalc::cb_key1 (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_key1_i();
}

void
Fl_RPNCalc::cb_key1_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 1;
		strcpy (digits, "1");
		break;

	case enter:
		stack[stack.size() - 1] = 1;
		strcpy (digits, "1");
		break;

	case key:
		if (countchar() < dw)
		{		
			strcpy (digits, disp->value());
			stripblanks();
			strcat (digits, "1");
			stack[stack.size() - 1] = atof (digits);
		}

		break;
	}
	rightjustify();
	return_state = key;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_key2 (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_key2_i();
}

void
Fl_RPNCalc::cb_key2_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 2;
		strcpy (digits, "2");
		break;

	case enter:
		stack[stack.size() - 1] = 2;
		strcpy (digits, "2");
		break;

	case key:
		if (countchar() < dw)
		{
			strcpy (digits, disp->value());
			stripblanks();
			strcat (digits, "2");
			stack[stack.size() - 1] = atof (digits);
		}
		break;
	}
	rightjustify();
	return_state = key;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_key3 (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_key3_i();
}

void
Fl_RPNCalc::cb_key3_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 3;
		strcpy (digits, "3");
		break;

	case enter:
		stack[stack.size() - 1] = 3;
		strcpy (digits, "3");
		break;

	case key:
		if (countchar() < dw)
		{
			strcpy (digits, disp->value());
			stripblanks();
			strcat (digits, "3");
			stack[stack.size() - 1] = atof (digits);
		}
		break;
	}
	rightjustify();
	return_state = key;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_key4 (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_key4_i();
}

void
Fl_RPNCalc::cb_key4_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 4;
		strcpy (digits, "4");
		break;

	case enter:
		stack[stack.size() - 1] = 4;
		strcpy (digits, "4");
		break;

	case key:
		if (countchar() < dw)
		{
			strcpy (digits, disp->value());
			stripblanks();
			strcat (digits, "4");
			stack[stack.size() - 1] = atof (digits);
		}
		break;
	}
	rightjustify();
	return_state = key;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_key5 (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_key5_i();
}

void
Fl_RPNCalc::cb_key5_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 5;
		strcpy (digits, "5");
		break;

	case enter:
		stack[stack.size() - 1] = 5;
		strcpy (digits, "5");
		break;

	case key:
		if (countchar() < dw)
		{
			strcpy (digits, disp->value());
			stripblanks();
			strcat (digits, "5");
			stack[stack.size() - 1] = atof (digits);
		}
		break;
	}
	rightjustify();
	return_state = key;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_key6 (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_key6_i();
}

void
Fl_RPNCalc::cb_key6_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 6;
		strcpy (digits, "6");
		break;

	case enter:
		stack[stack.size() - 1] = 6;
		strcpy (digits, "6");
		break;

	case key:
		if (countchar() < dw)
		{
			strcpy (digits, disp->value());
			stripblanks();
			strcat (digits, "6");
			stack[stack.size() - 1] = atof (digits);
		}
		break;
	}
	rightjustify();
	return_state = key;

}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_key7 (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_key7_i();
}

void
Fl_RPNCalc::cb_key7_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 7;
		strcpy (digits, "7");
		break;

	case enter:
		stack[stack.size() - 1] = 7;
		strcpy (digits, "7");
		break;

	case key:
		if (countchar() < dw)
		{
			strcpy (digits, disp->value());
			stripblanks();
			strcat (digits, "7");
			stack[stack.size() - 1] = atof (digits);
		}
		break;
	}
	rightjustify();
	return_state = key;
}

//-----------------------------------------------------
void
Fl_RPNCalc::cb_key8 (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_key8_i();
}

void
Fl_RPNCalc::cb_key8_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 8;
		strcpy (digits, "8");
		break;

	case enter:
		stack[stack.size() - 1] = 8;
		strcpy (digits, "8");
		break;

	case key:
		if (countchar() < dw)
		{
			strcpy (digits, disp->value());
			stripblanks();
			strcat (digits, "8");
			stack[stack.size() - 1] = atof (digits);
		}
		break;
	}
	rightjustify();
	return_state = key;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_key9 (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_key9_i();
}

void
Fl_RPNCalc::cb_key9_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 9;
		strcpy (digits, "9");
		break;

	case enter:
		stack[stack.size() - 1] = 9;
		strcpy (digits, "9");
		break;

	case key:
		if (countchar() < dw)
		{
			strcpy (digits, disp->value());
			stripblanks();
			strcat (digits, "9");
			stack[stack.size() - 1] = atof (digits);
		}
		break;
	}
	rightjustify();
	return_state = key;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_key0 (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_key0_i();
}

void
Fl_RPNCalc::cb_key0_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 0;
		strcpy (digits, "0");
		break;

	case enter:
		stack[stack.size() - 1] = 0;
		strcpy (digits, "0");
		break;

	case key:
		if (countchar() < dw)
		{
			strcpy (digits, disp->value());
			stripblanks();
			strcat (digits, "0");
			stack[stack.size() - 1] = atof (digits);
		}
		break;
	}
	rightjustify();
	return_state = key;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_dec (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_dec_i();
}

void
Fl_RPNCalc::cb_dec_i()
{
	switch (return_state)
	{

	case operation:
		stack.push_back (stack[stack.size() - 1]);
		stack[stack.size() - 1] = 0;
		strcpy (digits, ".");
		break;

	case enter:
		stack[stack.size() - 1] = 0;
		strcpy (digits, ".");
		break;

	case key:
		string n (digits);
		if ((n.find (".") == -1) && (countchar() < dw))
		{
			stripblanks();
			n += '.';
			strcpy (digits, n.c_str());
			stack[stack.size() - 1] = atof (digits);
		}
		break;
	}
	rightjustify();
	return_state = key;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_mult (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_mult_i();
}

void
Fl_RPNCalc::cb_mult_i()
{
	if (stack.size() < 2)
	{
		stack.push_back (0);	// to ensure min 2 reg always avail
		stack[1] = stack[0];
		stack[0] = 0;
	}

	double f = stack[stack.size() - 2] * stack[stack.size() - 1];
	sprintf (digits, "%.9f", f);
	viewable();
	stack.pop_back();
	stack[stack.size() - 1] = f;
	stripzeros();
	rightjustify();
	return_state = operation;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_div (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_div_i();
}

void
Fl_RPNCalc::cb_div_i()
{
	if (stack.size() < 2)
	{
		stack.push_back (0);	// to ensure min 2 reg always avail
		stack[1] = stack[0];
		stack[0] = 0;
	}
	if (stack[stack.size() - 1] != 0)
	{			//to prevent div by zero
		double f =
			stack[stack.size() - 2] / stack[stack.size() - 1];
		sprintf (digits, "%.9f", f);
		//cout << digits << endl;
		viewable();
		stack.pop_back();
		stack[stack.size() - 1] = f;
		stripzeros();
	}
	else
	{
		strcpy (digits, zeros);
	}
	rightjustify();
	return_state = operation;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_add (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_add_i();
}

void
Fl_RPNCalc::cb_add_i()
{
	if (stack.size() < 2)
	{
		stack.push_back (0);
		stack[1] = stack[0];
		stack[0] = 0;
	}
	double f = stack[stack.size() - 2] + stack[stack.size() - 1];
	sprintf (digits, "%.9f", f);
	viewable();
	stack.pop_back();
	stack[stack.size() - 1] = f;
	stripzeros();
	rightjustify();
	return_state = operation;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_sub (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_sub_i();
}

void
Fl_RPNCalc::cb_sub_i()
{
	if (stack.size() < 2)
	{
		stack.push_back (0);
		stack[1] = stack[0];
		stack[0] = 0;
	}

	double f = stack[stack.size() - 2] - stack[stack.size() - 1];
	sprintf (digits, "%.9f", f);
	viewable();
	stack.pop_back();
	stack[stack.size() - 1] = f;
	stripzeros();
	rightjustify();
	return_state = operation;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_clr (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_clr_i();
}

void
Fl_RPNCalc::cb_clr_i() 
{
	stack[stack.size() - 1] = 0;
	strcpy (digits, "");
	disp->value ("");
	return_state = key;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_ent (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_ent_i();
}

void
Fl_RPNCalc::cb_ent_i()
{
	stack.push_back (stack[stack.size() - 1]);
	return_state = enter;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_pm (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_pm_i();
}

void
Fl_RPNCalc::cb_pm_i()
{
	strcpy (digits, disp->value());
	stripblanks();
	std::string n (digits);
	if (n[0] == '-')
		n = n.erase (0, 1);
	else
		n = '-' + n;
	strcpy (digits, n.c_str());
	stack[stack.size() - 1] = atof (digits);
	rightjustify();
	// no change of state
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_rcl (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_rcl_i();
}

void
Fl_RPNCalc::cb_rcl_i()
{
	stack.push_back (stack[stack.size() - 1]);
	stack[stack.size() - 1] = mem;
	sprintf (digits, "%.9f", mem);
	stripzeros();
	rightjustify();
	return_state = operation;
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_sto (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_sto_i();
}

void
Fl_RPNCalc::cb_sto_i()
{
	mem = stack[stack.size() - 1];
	return_state = operation;
}

//---------------------------------------------------

void
Fl_RPNCalc::cb_sum (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_sum_i();
}

void
Fl_RPNCalc::cb_sum_i()
{
	strcpy (digits, disp->value());
	mem += atof (digits);
	return_state = operation;
}

//---------------------------------------------------

void
Fl_RPNCalc::cb_sqr (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_sqr_i();
}

void
Fl_RPNCalc::cb_sqr_i()
{
	double num = sqrt (atof (digits));
	if (num >= 0)
	{
		stack[stack.size() - 1] = num;
		sprintf (digits, "%.9f", num);
		viewable();
		stripzeros();
	}
	else
	{
		strcpy (digits, zeros);
	}
	rightjustify();
	return_state = operation;
}

//---------------------------------------------------

void
Fl_RPNCalc::cb_back (Fl_Widget* o, void *v)
{
	
	( (Fl_RPNCalc*)v )->cb_back_i();
}

void
Fl_RPNCalc::cb_back_i()
{
	if (return_state == key)
	{
		string d (digits);
		if (d.size() > 0)
		{
			d = d.erase (d.size() - 1, 1);
			strcpy (digits, d.c_str());
			stack[stack.size() - 1] = atof (digits);
			rightjustify();
		}
		return_state = key;
	}
}


//---------------------------------------------------

void
Fl_RPNCalc::cb_clrstck (Fl_Widget* o, void *v) //clears entire stack
{
	
	( (Fl_RPNCalc*)v )->cb_clrstck_i();
}

void
Fl_RPNCalc::cb_clrstck_i()
{
	stack.clear();
	stack.push_back (0);
	disp->value ("");
	return_state = key;
}


//---------------------------------------------------

void
Fl_RPNCalc::stripblanks() //removes leading blanks needed for right justify
{
	string d (digits);
	while (d[0] == ' ')
		d = d.erase (0, 1);
	strcpy (digits, d.c_str());
}

//-----------------------------------------------------

void
Fl_RPNCalc::stripzeros() //removes unnecessary trailing zeros (eg 3.2000 => 3.2)
{
	string d (digits);
	while ((d[d.size() - 1] == '0' || d[d.size() - 1] == '.')
	       && d.find ('.') != -1)
	{
		d = d.erase (d.size() - 1, 1);
	}
	strcpy (digits, d.c_str());
}

//-----------------------------------------------------

int
Fl_RPNCalc::countchar() //counts the number of actual viewable digit characters
{
	string d (disp->value());
	while (d[0] == ' ')
		d = d.erase (0, 1);
	return (d.size());
}


//-----------------------------------------------------

void
Fl_RPNCalc::rightjustify() //hack for Fl_Output to right justify text      
{
	string d (digits);
	string blanks ("");
	short spaces (0);
	spaces = (disp->w() - 15 * (short (d.size()))) / 15;
	for (short x = 0; x < spaces; x++)
		blanks += " ";
	d = blanks + d;
	disp->value (d.c_str());
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_quit (Fl_Widget *, void* v)
{
	((Fl_RPNCalc*)v)->hide();
	//exit (0); // I prefer the line above which has the same effect
}

//-----------------------------------------------------

void
Fl_RPNCalc::viewable() 
/*
* copies the part of digits which is viewable in an 11 digit mantissa to itself.
* one space is left over for the +/- character
*/                       
{
	string s (digits);
	int len;

	if (s.size() > 11)
	{
		if (s[0] == '-')
			len = 13;
		else
			len = 12;
		if ((s.substr (0, len)).find ('.') == -1)
		{		//. not found (num too big to show)
			strcpy (digits, zeros);
		}
		else
		{
			s = s.substr (0, len - 1);
			strcpy (digits, s.c_str());
		}
	}
	else
	{
		return;
	}
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_about (Fl_Widget *, void *)
{
	fl_message
		("Fl_RPNCalc version 1.1\nAuthor: Robert Arkiletian (http://www3.telus.net/public/robark/index.html)\n\nFl_RPNCalc is a simple Reverse Polish Notation Calculator. \nIt is based in part on the work of the FLTK project (http://www.fltk.org)\nIt is designed to be easily used with one hand on the keyboard\n\nPlease report any bugs to fltk_beginner_tutorial AT yahoo DOT com\nCopyright  2004  Robert Arkiletian");
}

//-----------------------------------------------------

void
Fl_RPNCalc::cb_license (Fl_Widget *, void *)
{
	fl_message
		(" * This program is free software; you can redistribute it and/or modify\n *  it under the terms of the GNU General Public License as published by\n *  the Free Software Foundation; either version 2 of the License, or\n *  (at your option) any later version.\n\n *  This program is distributed in the hope that it will be useful,\n *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n *  GNU Library General Public License for more details.\n\n *  You should have received a copy of the GNU General Public License\n *  along with this program; if not, write to the Free Software\n *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  ");
}
