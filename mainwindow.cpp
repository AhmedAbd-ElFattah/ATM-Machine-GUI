#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TransferPage_Init();
    ReservationSystem_Init();
    Keypad_Init();
    AvailableUserLed_Init();

}

MainWindow::~MainWindow()
{
    TransferPage_DeInit();

    delete ui;
}


void MainWindow::on_clear_pushButton_clicked()
{
    ui->userName_lineEdit->clear();
    ui->password_lineEdit->clear();
}


void MainWindow::on_login_pushButton_clicked()
{
    UserStatus L_usr_status;
    /*Read Login id*/
    const int user_logic_id = ui->userName_lineEdit->text().toInt();
    /*Read PIN number*/
    const short int User_PIN = ui->password_lineEdit->text().toInt();

    /*Try to Login*/
    L_usr_status = Database_sq.LoginIn(user_logic_id, User_PIN);
    /*If loginid not valid go to page "UserNameNoExist_Page" page*/
    if (!L_usr_status.ValidUser){
        trnsPage->GoToPage(UserNameNoExist_Page);
        return ;
    }
    /*If pin not correct go to page "PasswordNotCorrect_Page" page*/
    if (!L_usr_status.ValidUserPassword){
        trnsPage->GoToPage(PasswordNotCorrect_Page);
        return ;
    }
    /*Stop LED blinking*/
    AvailableUserLedTimer.stop();

    trnsPage->GoToPage(Service_Page);
}


void MainWindow::on_ReturnToMainPage_pushButton_clicked()
{
    Logout();
}


void MainWindow::on_ReturnToMainPage_pushButton_2_clicked()
{
    Logout();
}


void MainWindow::UpdateAvailableUserLed()
{
    if (0 == ui->stackedWidget->currentIndex()){
        AvailableUserLed.TurnOnLedForPulse(CONFIG_AVAILABLE_USER_LED_FLASH_INTERVAL_TIME_IN_MS/2);
    }
}


void MainWindow::on_logout_pushButton_clicked()
{
    Logout();
}


void MainWindow::on_AccountBalance_pushButton_clicked()
{

    Database_sq.ShowBalance(ui->AccountBalance_tableWidget);
    trnsPage->GoToPage(AccountBalance_Page);

}


void MainWindow::on_ReturnToMainPage_pushButton_3_clicked()
{
    trnsPage->GoToPage(Service_Page);
}


void MainWindow::on_logout_pushButton1_clicked()
{
    Logout();
    trnsPage->GoToPage(Login_Page);
}

void MainWindow::KeypadAction()
{
    /*Scrolling device section*/
    ScrollType Current_Scroll = Scroll_Device.GetScrollReading();

    auto QT_Focus_Obj = QGuiApplication::focusObject();
    /*Check for scrolling up*/
    if (Current_Scroll == ScrollType_UpScroll){
        QKeyEvent key_press = QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Up, Qt::AltModifier, QString());
        /*Send event to object*/
        QApplication::sendEvent(QT_Focus_Obj, &key_press);
        /*Stop timer till the configured time between two pressed buttons is elapsed.*/
        KeypadTimer.stop();
        QThread::msleep(CONFIG_CONSECUTIVE_TIME_BETWEEN_PRESSED_BUTTONS_FOR_SCROLLING_DEVICE_S_IN_ms);
        Buzzer.TurnOnBuzzerForPulse(CONFIG_CLICK_BUZZER_PULESE_TIME_IN_ms);
        KeypadTimer.start();
        return ;
    }
    else if (Current_Scroll == ScrollType_DownScroll)
    {
        QKeyEvent key_press = QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Down, Qt::AltModifier, QString());
        QApplication::sendEvent(QT_Focus_Obj, &key_press);
        KeypadTimer.stop();
        /*Stop timer till the configured time between two pressed buttons is elapsed.*/
        QThread::msleep(CONFIG_CONSECUTIVE_TIME_BETWEEN_PRESSED_BUTTONS_FOR_SCROLLING_DEVICE_S_IN_ms);
        Buzzer.TurnOnBuzzerForPulse(CONFIG_CLICK_BUZZER_PULESE_TIME_IN_ms);
        KeypadTimer.start();
        return ;
    }

    char Active_key = Keypad.GetActiveKey();
    /*No pressed button.*/
    if ('Z' == Active_key){
        return;
    }
    KeypadTimer.stop();
    /*Wait till button is released*/
    while (Active_key != Keypad.GetActiveKey());


    Buzzer.TurnOnBuzzerForPulse(CONFIG_CLICK_BUZZER_PULESE_TIME_IN_ms);
    if ((Active_key >= '0') && (Active_key <= '9')){
        QKeyEvent key_press = QKeyEvent(QKeyEvent::KeyPress, Active_key, Qt::NoModifier, QString(Active_key));
        QApplication::sendEvent(QT_Focus_Obj, &key_press);
    }
    else{
        QKeyEvent key_press = QKeyEvent(QKeyEvent::KeyPress, Active_key, Qt::AltModifier, QString());
        QApplication::sendEvent(QT_Focus_Obj, &key_press);
    }
    QThread::msleep(CONFIG_CONSECUTIVE_TIME_BETWEEN_PRESSED_BUTTONS_FOR_KEYPAD_IN_ms);
    KeypadTimer.start();
}


void MainWindow::on_withdraw_pushButton_clicked()
{
    ui->Message_WithdrawPage_label->clear();
    ui->AmountOfMoney_FromWithdrawPage_lineEdit->clear();
    Database_sq.ShowBalance(ui->AccountBalanceFromWithdraw_tableWidget);
    trnsPage->GoToPage(Withdraw_Page);

}


void MainWindow::on_deposit_pushButton_clicked()
{
    ui->Message_DepositPage_label->clear();
    ui->AmountOfMoney_FromDepositPage_lineEdit->clear();
    Database_sq.ShowBalance(ui->AccountBalance_DepositPage_tableWidget);
    trnsPage->GoToPage(Deposit_Page);
}


void MainWindow::on_Up_FromWithdraw_pushButton_clicked(){
   SwitchSelectedAccountToUp(ui->AccountBalanceFromWithdraw_tableWidget);
}


void MainWindow::on_Down_FromWithdraw_pushButton_clicked()
{
    SwitchSelectedAccountToDown(ui->AccountBalanceFromWithdraw_tableWidget);
}



void MainWindow::on_Withdraw_WithdrawPage_pushButton_clicked()
{
    int balance;
    int acc_id;
    AccountOperations L_OperationStatus;
    if (ui->AccountBalanceFromWithdraw_tableWidget->selectedItems().empty()){
        ui->Message_WithdrawPage_label->setText("Please select account.");
        return ;
    }


    balance = ui->AmountOfMoney_FromWithdrawPage_lineEdit->text().toInt();

    acc_id = ui->AccountBalanceFromWithdraw_tableWidget->selectedItems().at(1)->text().toInt();


    L_OperationStatus = Database_sq.WithDraw(acc_id, balance);
    /*Refresh page*/
    on_withdraw_pushButton_clicked();

    switch (L_OperationStatus){
    case Account_op_Succeed:
        ui->Message_WithdrawPage_label->setText("Withdraw succeeded.");
        break;

    case Account_op_NoAvailableBalance:
        ui->Message_WithdrawPage_label->setText("No available balance");
        break;

    default:
        ui->Message_WithdrawPage_label->setText("Unexpected error !.");
    }


}


void MainWindow::on_ReturnToMainPage_pushButton_4_clicked()
{
    trnsPage->GoToPage(Service_Page);
}


void MainWindow::on_logout_pushButton_2_clicked()
{
    Logout();
}

void MainWindow::Logout()
{
    /*Increase displayed number on seven segment module.*/
    Reservation_sys_obj.RequestNewClient();
    Database_sq.LogOut();
    AvailableUserLedTimer.start();
    ui->userName_lineEdit->clear();
    ui->password_lineEdit->clear();
    trnsPage->GoToPage(Login_Page);
}

void MainWindow::ReservationSystem_Init()
{
    Reservation_sys_obj.setReservationButtonFilePath(CONFIG_RESERVATION_PUSH_BUTTON_DEVICE_FILE_PATH);
    Reservation_sys_obj.setsevenSegmentModuleFilePath(CONFIG_SEVEN_SEGMENT_MODULE_DEVICE_FILE_PATH);
    Reservation_sys_obj.moveToThread(&ReservationSystemThread);
    Reservation_sys_obj.start();
}

void MainWindow::Keypad_Init()
{
    KeypadTimer.setInterval(CONFIG_KEYPAD_INTERVAL_TIME_IN_MS);
    connect(&KeypadTimer, &QTimer::timeout, this, &MainWindow::KeypadAction);
    KeypadTimer.start();
}

void MainWindow::AvailableUserLed_Init()
{
    AvailableUserLedTimer.setInterval(CONFIG_AVAILABLE_USER_LED_FLASH_INTERVAL_TIME_IN_MS);
    connect(&AvailableUserLedTimer, &QTimer::timeout, this, &MainWindow::UpdateAvailableUserLed);
    AvailableUserLedTimer.start();
}

void MainWindow::TransferPage_Init()
{
    trnsPage = new TransferPage(ui->stackedWidget);
    trnsPage->GoToPage(Login_Page);
}

void MainWindow::TransferPage_DeInit()
{
    if (nullptr != trnsPage){
        delete trnsPage;
        trnsPage = nullptr;
    }
}


void MainWindow::on_Deposit_DepositPage_pushButton_2_clicked()
{
    int balance;
    int acc_id;
    AccountOperations L_OperationStatus;
    if (ui->AccountBalance_DepositPage_tableWidget->selectedItems().empty()){
        ui->Message_DepositPage_label->setText("Please select account.");
        return ;
    }

    balance = ui->AmountOfMoney_FromDepositPage_lineEdit->text().toInt();

    acc_id = ui->AccountBalance_DepositPage_tableWidget->selectedItems().at(1)->text().toInt();

    L_OperationStatus = Database_sq.Deposit(acc_id, balance);
    /*Refresh page*/
    on_deposit_pushButton_clicked();

    switch (L_OperationStatus){
    case Account_op_Succeed:
        ui->Message_DepositPage_label->setText("Deposit succeeded.");
        break;

    default:
        ui->Message_DepositPage_label->setText("Unexpected error !.");
    }


}


void MainWindow::on_logout_pushButton_3_clicked()
{
    Logout();
}


void MainWindow::on_ReturnToMainPage_pushButton_5_clicked()
{
    trnsPage->GoToPage(Service_Page);
}


void MainWindow::on_Up_FromDeposit_pushButton_clicked()
{
    SwitchSelectedAccountToUp(ui->AccountBalance_DepositPage_tableWidget);
}


void MainWindow::on_Down_FromDeposit_pushButton_clicked()
{
    SwitchSelectedAccountToDown(ui->AccountBalance_DepositPage_tableWidget);
}


void MainWindow::on_Up_FromAccBaalance_pushButton_clicked()
{
    SwitchSelectedAccountToUp(ui->AccountBalance_tableWidget);
}


void MainWindow::on_Down_FromAccBaalance_pushButton_clicked()
{
    SwitchSelectedAccountToDown(ui->AccountBalance_tableWidget);
}


void MainWindow::on_transfer_pushButton_clicked()
{

    int LoginId = ui->userNumber_lineEdit->text().toInt();
    int UserId;
    int accountNumber = ui->accNumber_lineEdit->text().toInt();

    /*Check the existance of user*/
    if (!Database_sq.IsUserExist(LoginId, &UserId)){
        ui->Message_TransferPage_label->setText("User not-exist !");
        return;
    }
    else{
        ui->Message_TransferPage_label->clear();
    }

    /*Check account number existance and if exists, get balance*/
    try {
        if (!Database_sq.IsAccountExist(UserId, accountNumber)){
            ui->Message_TransferPage_label->setText("Account not-exist !");
            return;
        }
        else{
            ui->Message_TransferPage_label->clear();
        }
    }  catch (const std::out_of_range& ex) {
        ui->Message_TransferPage_label->setText("Account not-exist !");
    }

    /*If User id and account number valid clear text*/
    ui->Message_TransferPage_label->clear();



    /*****************************************************************************/
    /*With draw money from logged account.*/
    int balance = ui->AmountOfMoney_FromTransferPage_lineEdit->text().toInt();
    int acc_id;
    AccountOperations L_OperationStatus;
    if (ui->AccountBalance_TransferPage_tableWidget->selectedItems().empty()){
        ui->Message_TransferPage_label->setText("Please select account.");
        return ;
    }

    acc_id = ui->AccountBalance_TransferPage_tableWidget->selectedItems().at(1)->text().toInt();
    L_OperationStatus = Database_sq.WithDraw(acc_id, balance);
    switch (L_OperationStatus){
    case Account_op_Succeed:

        break;
    case Account_op_NoAvailableBalance:
        ui->Message_TransferPage_label->setText("No available balance");
        return ;
        break;

    default:
        ui->Message_TransferPage_label->setText("Unexpected error !");

        return ;
    }

    /*Deposit money*/

    acc_id = ui->accNumber_lineEdit->text().toInt();

    L_OperationStatus = Database_sq.Deposit(acc_id, balance);

    /*Refresh page*/
    on_transfer_pushButton_9_clicked();

    switch (L_OperationStatus){
    case Account_op_Succeed:
        ui->Message_TransferPage_label->setText("Transfer succeeded.");
        break;

    default:
        ui->Message_TransferPage_label->setText("Unexpected error !");
    }


}

void MainWindow::on_transfer_pushButton_9_clicked()
{
    ui->userNumber_lineEdit->clear();
    ui->accNumber_lineEdit->clear();
    ui->Message_TransferPage_label->clear();
    Database_sq.ShowBalance(ui->AccountBalance_TransferPage_tableWidget);
    trnsPage->GoToPage(TransferMoney_Page);
}






void MainWindow::on_Up_FromTransfer_pushButton_clicked()
{

}


void MainWindow::on_Down_FromTransfer_pushButton_clicked()
{

}


void MainWindow::on_username_Focus_Loginpage_clicked()
{
    ui->userName_lineEdit->setFocus();
}


void MainWindow::on_password_Focus_Loginpage_clicked()
{
    ui->password_lineEdit->setFocus();
}




void MainWindow::on_AmountOfMoney_Focus_Withdrawpage_clicked()
{
    ui->AmountOfMoney_FromWithdrawPage_lineEdit->setFocus();
}


void MainWindow::on_AmountOfMoney_Focus_Depositpage_clicked()
{
    ui->AmountOfMoney_FromDepositPage_lineEdit->setFocus();
}


void MainWindow::on_ToUser_Focus_Transferpage_clicked()
{
    ui->userNumber_lineEdit->setFocus();
}


void MainWindow::on_AccNumUser_Focus_Transferpage_clicked()
{
    ui->accNumber_lineEdit->setFocus();
}


void MainWindow::on_AmountOfMoney_Focus_Transferpage_clicked()
{
    ui->AmountOfMoney_FromTransferPage_lineEdit->setFocus();
}

void MainWindow::SwitchSelectedAccountToUp(QTableWidget *Arg_QTableWidget)
{
    if (Arg_QTableWidget->selectedItems().empty()){
        if (Arg_QTableWidget->rowCount()){
            Arg_QTableWidget->selectRow(0);
        }
        else{

        }
        return ;

    }
    Arg_QTableWidget->selectRow(Arg_QTableWidget->selectedItems().at(0)->row()-1);

}

void MainWindow::SwitchSelectedAccountToDown(QTableWidget *Arg_QTableWidget)
{
    if (Arg_QTableWidget->selectedItems().empty()){
        if (Arg_QTableWidget->rowCount()){
            Arg_QTableWidget->selectRow(0);
        }
        else{

        }
        return ;

    }
    Arg_QTableWidget->selectRow(Arg_QTableWidget->selectedItems().at(0)->row()+1);

}

