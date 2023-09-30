#ifndef DATABASE_H
#define DATABASE_H
/*
 * File Name --> database.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Database operations like login, logout, query account balance, ... and so on.
 * */

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QPluginLoader>
#include <QVariant>
#include <vector>
#include "account.h"
#include <QDebug>
#include <QTableWidget>
#include "Configurations.h"

enum AccountOperations{
    Account_op_Succeed,
    Account_op_Failed,
    Account_op_NoAvailableBalance,
    Account_op_TargetUserNotExist,
    Account_op_NoLoggedInAccount,
};

struct UserStatus{
    bool ValidUser=false;
    bool ValidUserPassword=false;
    int SystemUserID;
};

class Database
{
private:
    const QString Loader_Path = CONFIG_LOADER_PATH;
    const QString Database_Path = CONFIG_DATABASE_PATH;

    QSqlDatabase DatabaseObj;
    int LoggedInUserId;
    /*It holds wheter there is logged in user  or not.*/
    bool userLoggedin;
    /*Retreive Account type in string format
     * It can be used as a table name included in query.
     */
    QString GetAccountTypeInStringFromAccountNumber(int Arg_AccountId);
    Account_Type GetAccountTypeFromAccountNumber(int Arg_AccountId);


public:
    Database();
    UserStatus LoginIn(int loginid, short int password);
    void LogOut();

    /*Show balance in specific QTableWidget*/
    void ShowBalance(QTableWidget *Arg_QTableWidget);
    AccountOperations WithDraw(int Arg_AccountId, unsigned int Arg_amount);
    AccountOperations Deposit(int Arg_AccountId, unsigned int Arg_amount);

    bool IsUserExist(int Arg_LoginId, int *UserId);
    bool IsAccountExist(int Arg_UserId, int Arg_AccountNum);

    ~Database();
};

#endif // DATABASE_H
