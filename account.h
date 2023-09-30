/*
 * File Name --> account.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> It includes account properities used by application.
 * */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <map>
#include <QString>
#include <array>

#define TOTAL_ACCOUNT_TYPES 6

enum TransferStatus{
    Transfer_Succeed,
    Transfer_NoAvailableBalance,
    Transfer_Failled,
};

enum WithdrawStatus{
    Withdraw_Succeed,
    Withdraw_NoAvailableBalance,
    Withdraw_Failled,
};

enum DepositStatus{
    Deposit_Succeed,
    Deposit_Failled,
};

enum Account_Type{
    CurrentAccount_t,
    SavingAccount_t,
    Certificate3Years_t,
    Certificate4Years_t,
    Certificate5Years_t,
    Certificate7Years_t,
};

enum Account_Currency{
    Currency,
    Dollar_Currency,
    Euro_Currency
};
/*
 * This array of account types mapes each account type index
 * by user friendly enum val
 */
extern std::array<Account_Type, TOTAL_ACCOUNT_TYPES> Arr_AccountTypes;
/*
 * This array of account type name maps each account type index
 * with it's name in string.
 * Also string must has the same name of table name in database, because it's used by query.
 */
extern std::array<QString, TOTAL_ACCOUNT_TYPES> Arr_AccountTypesNameMapping;


#endif // ACCOUNT_H
