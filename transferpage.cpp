#include "transferpage.h"

TransferPage::TransferPage(QStackedWidget * const Arg_widget):widget(Arg_widget)
{

}


void TransferPage::GoToPage(const System_Pages Arg_page)
{
    /*Switch to page defined by Arg_page*/
    widget->setCurrentIndex(Arg_page);
}
