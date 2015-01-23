/*
 * menuWindow.h
 *
 *  Created on: Jan 23, 2015
 *      Author: akukushk
 */

#ifndef MENUWINDOW_H_
#define MENUWINDOW_H_

#include <list>

struct ButtonContext
{
    ButtonContext()
    {
        X0      = 0;
        Y0      = 0;
        x_len   = 0;
        y_len   = 0;
        action  = 0;
    }

    ButtonContext(unsigned X0_in, unsigned Y0_in, unsigned x_len_in, unsigned y_len_in, void* action_in)
    {
        X0      = X0_in;
        Y0      = Y0_in;
        x_len   = x_len_in;
        y_len   = y_len_in;
        action  = action;
    }
    unsigned X0, Y0;
    unsigned x_lent, y_len;

    void* action();
};

class MenuWindow: public ButtonContext
{



private:
    std::list<ButtonContext> buttons;

};


#endif /* MENUWINDOW_H_ */
