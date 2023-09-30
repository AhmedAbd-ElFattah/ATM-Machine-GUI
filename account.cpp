#include "account.h"
/*
 * Definition of Arr_AccountTypes array.
 * Important Note : Any addition or removal of account types should be notified by an
 * increase / decrease on TOTAL_ACCOUNT_TYPES macro.
 */
std::array<Account_Type, TOTAL_ACCOUNT_TYPES> Arr_AccountTypes
{
    CurrentAccount_t,
    SavingAccount_t,
    Certificate3Years_t,
    Certificate4Years_t,
    Certificate5Years_t,
    Certificate7Years_t,
};

/*
 * Definition of Arr_AccountTypesNameMapping array.
 * Important Note : Any addition or removal of account types should be notified by an
 * increase / decrease on TOTAL_ACCOUNT_TYPES macro.
 */
std::array<QString, TOTAL_ACCOUNT_TYPES> Arr_AccountTypesNameMapping
{
    "CurrentAccount",
    "SavingAccount",
    "Certificate3Years",
    "Certificate4Years",
    "Certificate5Years",
    "Certificate7Years",
};
