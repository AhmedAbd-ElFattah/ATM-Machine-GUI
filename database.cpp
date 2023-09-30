#include "database.h"
#include <QDebug>
#include <stdexcept>

Database::Database()
{
    DatabaseObj = DatabaseObj.addDatabase("QSQLITE");
    DatabaseObj.setDatabaseName(Database_Path);
    /*Load database loader & Connect to Database. */
    QPluginLoader loader(Loader_Path);
    if (!loader.load()){
        throw std::runtime_error("Can't load Database loader !");
    }
    /*Connect to data base*/
    if (!DatabaseObj.open()){
        throw std::runtime_error("Can't Open Database !");
    }
    userLoggedin = false;
}

QString Database::GetAccountTypeInStringFromAccountNumber(int Arg_AccountId)
{
    short int idx = (short int)(Arg_AccountId/1000000) - 1;
    if (Arg_AccountId < 1000000){
        throw std::out_of_range("Account number out of range hence it's not valid");
    }
    return Arr_AccountTypesNameMapping.at(idx);
}

Account_Type Database::GetAccountTypeFromAccountNumber(int Arg_AccountId)
{
    short int idx = (short int)(Arg_AccountId/1000000) - 1;
    if (Arg_AccountId < 1000000){
        throw std::out_of_range("Account number out of range hence it's not valid");
    }
    return Arr_AccountTypes.at(idx);
}



UserStatus Database::LoginIn(int loginid, short password)
{
    UserStatus user_st;

    QString cmd = "SELECT LoginId, UserId, Password FROM Users WHERE LoginId = ";
    cmd  +=QString::number(loginid, 10);

    QSqlQuery query;
    if (query.exec(cmd)){
        while(query.next()){
            /*Check if user is valid, incase of invalid break.*/
            if (loginid == query.value(0).toInt()){
                user_st.ValidUser = true;
            }
            else{
                break;
            }

            /*Check if password is correct, incase of invalid break.*/
            if (password == query.value(2).toInt()){
                user_st.ValidUserPassword = true;
            }
            else{
                break;
            }
            /*Store userid of logged in user.*/
            user_st.SystemUserID = query.value(1).toInt();
            LoggedInUserId = user_st.SystemUserID;
            userLoggedin = true;
        }
    }

    return user_st;
}

void Database::LogOut()
{
    userLoggedin = false;
}

Database::~Database()
{
    DatabaseObj.close();
}


void Database::ShowBalance(QTableWidget *Arg_QTableWidget)
{
    /*Check if there is logged in user or not.*/
    if (!userLoggedin){
        return ;
    }
    short int new_row_idx;
    QString Cell_String = "";
    /*Clear table*/
    while (Arg_QTableWidget->rowCount()) {
        Arg_QTableWidget->removeRow(0);
    }

    QSqlQuery query;
    /*Loop over all account type*/
    for (const auto &acc_type : Arr_AccountTypes){
        /*Apply querty that gets Total Balance, Available Balance and Account Number*/
        QString L_SQLQuery =
                QString("SELECT TotalBalance, AvailableBalance, AccountNum FROM %1 WHERE UserId= %2")
                .arg(Arr_AccountTypesNameMapping.at(acc_type))
                .arg(LoggedInUserId, 10);

        if (query.exec(L_SQLQuery)){
            while(query.next()){
                /*1. Insert new empty row*/
                new_row_idx = Arg_QTableWidget->rowCount();
                Arg_QTableWidget->insertRow(new_row_idx);

                /*2. Set first coloumn to show Account type.*/
                Cell_String = Arr_AccountTypesNameMapping.at(acc_type);
                Arg_QTableWidget->setItem(new_row_idx, 0, new QTableWidgetItem(Cell_String));

                /*3. Set second coloumn to show Account type.*/
                Cell_String = QString::number(query.value(2).toInt(), 10);
                Arg_QTableWidget->setItem(new_row_idx, 1, new QTableWidgetItem(Cell_String));

                /*4. Set third  coloumn to show total balance.*/
                Cell_String = QString::number(query.value(0).toInt(), 10);
                Arg_QTableWidget->setItem(new_row_idx, 2, new QTableWidgetItem(Cell_String));

                /*5. Set fourth coloumn to show available balance.*/
                Cell_String = QString::number(query.value(1).toInt(), 10);
                Arg_QTableWidget->setItem(new_row_idx, 3, new QTableWidgetItem(Cell_String));
            }
        }
    }

    Arg_QTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    /*Selece default row number 0.*/
    if (Arg_QTableWidget->rowCount()){
        Arg_QTableWidget->selectRow(0);
    }
    Arg_QTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}

AccountOperations Database::WithDraw(int Arg_AccountId, unsigned int Arg_amount)
{
    /*Check if there is logged in user or not.*/
    if (!userLoggedin){
        return Account_op_NoLoggedInAccount;
    }
    QString L_accTypeInString = GetAccountTypeInStringFromAccountNumber(Arg_AccountId);

    QSqlQuery query;
    int currentAvailableBalance=0;
    int currentTotalBalance=0;
    /*Get current balance*/
    /*Apply querty that gets Available Balance & Total Balance*/
    QString Query_cmd = QString("SELECT AvailableBalance, TotalBalance FROM %1 WHERE UserId= %2 AND AccountNum = %3")
            .arg(L_accTypeInString)
            .arg(LoggedInUserId)
            .arg(QString::number(Arg_AccountId, 10));
    /**/
    if (query.exec(Query_cmd)){
        while(query.next()){
            currentAvailableBalance = query.value(0).toInt();
            currentTotalBalance = query.value(1).toInt();
        }
    }
    else{
        return Account_op_Failed;
    }

    /*Check it there is available balance or not.*/
    if ((unsigned int)currentAvailableBalance < (unsigned int)Arg_amount){
        return Account_op_NoAvailableBalance;
    }
    else{
        currentAvailableBalance -= Arg_amount;
        currentTotalBalance -= Arg_amount;

        Query_cmd = QString("UPDATE %1 SET AvailableBalance = %2, TotalBalance=%3 WHERE UserId= %4 AND AccountNum = %5")
                .arg(L_accTypeInString)
                .arg(currentAvailableBalance)
                .arg(currentTotalBalance)
                .arg(LoggedInUserId)
                .arg(Arg_AccountId);

        if (query.exec(Query_cmd)) {
            return Account_op_Succeed;
        } else {
            return Account_op_Failed;
        }
    }

    return Account_op_Failed;
}

AccountOperations Database::Deposit(int Arg_AccountId, unsigned int Arg_amount)
{
    if (!userLoggedin){
        return Account_op_NoLoggedInAccount;
    }
    QString L_accTypeInString = GetAccountTypeInStringFromAccountNumber(Arg_AccountId);
    QSqlQuery query;
    int currentAvailableBalance = 0;
    int currentTotalBalance = 0;

    /*Get current balance*/
    /*Apply querty that gets Available Balance & Total Balance*/
    QString Query_cmd = QString("SELECT AvailableBalance, TotalBalance FROM %1 WHERE UserId= %2 AND AccountNum = %3")
            .arg(L_accTypeInString)
            .arg(LoggedInUserId)
            .arg(QString::number(Arg_AccountId, 10));
    /*Get available balance & total balance.*/
    if (query.exec(Query_cmd)){
        while(query.next()){
            currentAvailableBalance = query.value(0).toInt();
            currentTotalBalance = query.value(1).toInt();
        }
    }
    else{
        return Account_op_Failed;
    }
    /*Deposit new balance*/
    currentAvailableBalance += Arg_amount;
    currentTotalBalance += Arg_amount;
    /*Update new balance in database.*/
    Query_cmd = QString("UPDATE %1 SET AvailableBalance = %2, TotalBalance=%3 WHERE UserId= %4 AND AccountNum = %5")
            .arg(L_accTypeInString)
            .arg(currentAvailableBalance)
            .arg(currentTotalBalance)
            .arg(LoggedInUserId)
            .arg(Arg_AccountId);

    if (query.exec(Query_cmd)) {
        return Account_op_Succeed;
    } else {
        return Account_op_Failed;
    }


    return Account_op_Failed;
}



bool Database::IsUserExist(int Arg_LoginId, int *UserId=nullptr)
{
    QSqlQuery query;
    QString queryCMD = QString("SELECT COUNT(*), UserId FROM Users WHERE LoginId = %1 ;").arg(Arg_LoginId);
    if (query.exec(queryCMD) && query.next()) {
        if (!query.value(0).toInt()){
            return false;
        }
        if (nullptr != UserId){
            *UserId = query.value(1).toInt();
        }

    }
    return true;
}

bool Database::IsAccountExist(int Arg_UserId, int Arg_AccountNum)
{
    QSqlQuery query;

    QString queryCMD = QString("SELECT COUNT(*), UserId FROM %1 WHERE LoginId = %2 ;").arg(GetAccountTypeInStringFromAccountNumber(Arg_AccountNum)).arg(Arg_UserId);
    qDebug()<<queryCMD;
    if (query.exec(queryCMD) && query.next()) {
        if (!query.value(0).toInt()){

            return false;
        }

    }
    return true;
}


