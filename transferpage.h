/*
 * File Name --> transferpage.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> It includes trasfer between pages.
 * */
#ifndef TRANSFERPAGE_H
#define TRANSFERPAGE_H

#include <QStackedWidget>
/* This enum includes all available pages on the system
 * any add, removal, or position edir of any page on UI
 * must be notified here
 */
enum System_Pages{
    Login_Page=0,
    Service_Page,
    UserNameNoExist_Page,
    PasswordNotCorrect_Page,
    AccountBalance_Page,
    Withdraw_Page,
    Deposit_Page,
    TransferMoney_Page
};

class TransferPage
{
private:
    QStackedWidget * const widget;
public:
    TransferPage(QStackedWidget * const Arg_widget);
    void GoToPage(const System_Pages Arg_page);
};

#endif // TRANSFERPAGE_H
