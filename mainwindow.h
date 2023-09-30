#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "transferpage.h"

#include "account.h"

#include "database.h"
#include <functional>
#include "reservationsystem.h"
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include "keypad_4x4.h"
#include "scrollingdevice.h"
#include "pulseled.h"
#include <QKeyEvent>
#include <QWidget>
#include "Configurations.h"
#include "pulsebuzzer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clear_pushButton_clicked();

    void on_login_pushButton_clicked();

    void on_ReturnToMainPage_pushButton_clicked();

    void on_ReturnToMainPage_pushButton_2_clicked();

    void on_logout_pushButton_clicked();

    void on_AccountBalance_pushButton_clicked();

    void on_ReturnToMainPage_pushButton_3_clicked();

    void on_logout_pushButton1_clicked();

    void on_withdraw_pushButton_clicked();

    void on_deposit_pushButton_clicked();

    void on_Up_FromWithdraw_pushButton_clicked();

    void on_Down_FromWithdraw_pushButton_clicked();

    void on_Withdraw_WithdrawPage_pushButton_clicked();

    void on_ReturnToMainPage_pushButton_4_clicked();

    void on_logout_pushButton_2_clicked();

    void on_Deposit_DepositPage_pushButton_2_clicked();

    void on_logout_pushButton_3_clicked();

    void on_ReturnToMainPage_pushButton_5_clicked();

    void on_Up_FromDeposit_pushButton_clicked();

    void on_Down_FromDeposit_pushButton_clicked();

    void on_Up_FromAccBaalance_pushButton_clicked();

    void on_Down_FromAccBaalance_pushButton_clicked();

    void on_transfer_pushButton_clicked();

    void on_transfer_pushButton_9_clicked();

    void on_Up_FromTransfer_pushButton_clicked();

    void on_Down_FromTransfer_pushButton_clicked();

    void on_username_Focus_Loginpage_clicked();

    void on_password_Focus_Loginpage_clicked();

    void on_AmountOfMoney_Focus_Withdrawpage_clicked();

    void on_AmountOfMoney_Focus_Depositpage_clicked();

    void on_ToUser_Focus_Transferpage_clicked();

    void on_AccNumUser_Focus_Transferpage_clicked();

    void on_AmountOfMoney_Focus_Transferpage_clicked();

private:

    void SwitchSelectedAccountToUp(QTableWidget *Arg_QTableWidget);
    void SwitchSelectedAccountToDown(QTableWidget *Arg_QTableWidget);

    void Logout();
    void ReservationSystem_Init();
    void Keypad_Init();
    void AvailableUserLed_Init();

    void TransferPage_Init();
    void TransferPage_DeInit();

    /*Devices objects*/
    Keypad_4x4 Keypad = Keypad_4x4(CONFIG_KEYPAD_FILE_PATH);
    ScrollingDevice Scroll_Device =  ScrollingDevice(CONFIG_SCROLLING_DEVICE_FILE_PATH);
    PulseLed AvailableUserLed = PulseLed(CONFIG_AVAILABLE_USER_LED_FILE_PATH);
    PulseBuzzer Buzzer = PulseBuzzer(CONFIG_BUZZER_FILE_PATH);
    /*
    * Timers like,
    * Keypad timer --> check for keypad events
    * AvailableUserLedTimer timer --> check for keypad events
    */
    QTimer KeypadTimer;
    QTimer AvailableUserLedTimer;
    QThread ReservationSystemThread;

    void KeypadAction();

    Database Database_sq;
    ReservationSystem Reservation_sys_obj;
    void UpdateAvailableUserLed();


    TransferPage *trnsPage = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
