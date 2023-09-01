#include "preferences.h"
#include "settings_key_variables.h"
#include "settings.h"
#include "ui_preferences.h"
#include <QDebug>
#include <QSlider>
#include <QPixmap>
#include <QLabel>
#include <QLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include "winuser.h"
#include "windows.h"


Preferences::Preferences(QWidget *parent) : QDialog(parent), ui(new Ui::Preferences)
{
	ui->setupUi(this);
    install_event_filter();
	ui->horizontalSlider->adjustSize();
    ui->buttonBox->connect(ui->buttonBox, &QDialogButtonBox::accepted, [=] {    // running the functions to change and save the new settings if the user presses ok
		this->change_mouse_sensitivity(ui->horizontalSlider->value() * 100);
        qDebug() << mouse_sensivity;
        save_setting(setting_keys::Mouse_sensivity, mouse_sensivity / 100); //saving the new mouse sensivity
        change_key_inputs(); //changing and saving key maps
	});
    ui->formLayout->setSizeConstraint(QLayout::SetMinimumSize);
    ui->formLayout->setHorizontalSpacing(50);
    ui->formLayout->setVerticalSpacing(10);
	ui->horizontalSlider->setValue(mouse_sensivity / 100);
    Preferences::load_keys();
}

/**
 * @brief Preferences::change_mouse_sensitivity
 * changes the mouse sensivity or the cursor speed
 * @param value
 * the amount of mouse sensivity you want to set.
 */
void Preferences::change_mouse_sensitivity(int value)
{
	mouse_sensivity = value;
}

/**
 * @brief Preferences::change_key_inputs
 * this changes the keyboard maps and saves those changes in the config file.
 * this function is executed if the user presses ok button.
 */

void Preferences::change_key_inputs()
{
    //change and save key maps
    GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_X] = this->X;
    save_setting(keymaps[setting_keys::keys::X], this->X);
    /*------------------------------------------------------------*/
    GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_Y] = this->Y;
    save_setting(keymaps[setting_keys::keys::Y], this->Y);
    /*------------------------------------------------------------*/
    GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_A] = this->A;
    save_setting(keymaps[setting_keys::keys::A], this->A);
    /*------------------------------------------------------------*/
    GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_B] = this->B;
    save_setting(keymaps[setting_keys::keys::B], this->B);
    /*------------------------------------------------------------*/
    GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_LeftThumbstick] = this->LT;
    save_setting(keymaps[setting_keys::keys::LT], this->LT);
    /*------------------------------------------------------------*/
    GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_RightThumbstick] = this->RT;
    save_setting(keymaps[setting_keys::keys::RT], this->RT);
    /*------------------------------------------------------------*/
    GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_DPadDown] = this->DDOWN;
    save_setting(keymaps[setting_keys::keys::DPADDOWN], this->DDOWN);
    /*------------------------------------------------------------*/
    GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_DPadUp] = this->DUP;
    save_setting(keymaps[setting_keys::keys::DPADUP], this->DUP);
    /*------------------------------------------------------------*/
    GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_DPadRight] = this->DRIGHT;
    save_setting(keymaps[setting_keys::keys::DPADRIGHT], this->DRIGHT);
    /*------------------------------------------------------------*/
    GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_DPadLeft] = this->DLEFT;
    save_setting(keymaps[setting_keys::keys::DPADLEFT], this->DLEFT);
}

/**
 * @brief Preferences::get_scan_code
 * gets the name of the of corrosponding key or virutal key code.
 * @param vk
 * the virtual key code of the key you want to get.
 * @param a
 * the buffer to store the name of the key.
 * @param size
 * size of the buffer in which the name is stored to ensure memory safety
 */
void Preferences::get_scan_code(WORD vk, char* a, int size)
{
    char sc = MapVirtualKeyA((UINT)vk, MAPVK_VK_TO_CHAR);
    if(sc >= '0' && sc <= 'Z') {
        strncpy(a, "", size);
        strncpy(a, &sc, 1);
    }
    else {
        strncpy(a, vk_maps[vk], size);
    }
}

/**
 * @brief Preferences::load_keys
 * displays the key to which each button is mapped to.
 * saves the initial key maps in variables that can be changed later if user wants to.
 */
void Preferences::load_keys()
{
    char buffer[256];
    this->X = GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_X];
    get_scan_code(GAMEPAD_BUTTONS[GamepadButtons_X], buffer, 256);
    this->ui->xmap->setText(QString(buffer));
    /*------------------------------------------------------------*/
    this->Y = GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_Y];
    get_scan_code(GAMEPAD_BUTTONS[GamepadButtons_Y], buffer, 256);
    this->ui->ymap->setText(QString(buffer));
    /*------------------------------------------------------------*/
    this->A = GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_A];
    get_scan_code(GAMEPAD_BUTTONS[GamepadButtons_A], buffer, 256);
    this->ui->amap->setText(QString(buffer));
    /*------------------------------------------------------------*/
    this->B = GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_B];
    get_scan_code(GAMEPAD_BUTTONS[GamepadButtons_B], buffer, 256);
    this->ui->bmap->setText(QString(buffer));
    /*------------------------------------------------------------*/
    this->RT = GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_RightThumbstick];
    get_scan_code(GAMEPAD_BUTTONS[GamepadButtons_RightThumbstick], buffer, 256);
    this->ui->Rtmap->setText(QString(buffer));
    /*------------------------------------------------------------*/
    this->LT = GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_LeftThumbstick];
    get_scan_code(GAMEPAD_BUTTONS[GamepadButtons_LeftThumbstick], buffer, 256);
    this->ui->Ltmap->setText(QString(buffer));
    /*------------------------------------------------------------*/
    this->DDOWN = GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_DPadDown];
    get_scan_code(GAMEPAD_BUTTONS[GamepadButtons_DPadDown], buffer, 256);
    this->ui->ddownmap->setText(QString(buffer));
    /*------------------------------------------------------------*/
    this->DUP = GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_DPadUp];
    get_scan_code(GAMEPAD_BUTTONS[GamepadButtons_DPadUp], buffer, 256);
    this->ui->dupmap->setText(QString(buffer));
    /*------------------------------------------------------------*/
    this->DRIGHT = GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_DPadRight];
    get_scan_code(GAMEPAD_BUTTONS[GamepadButtons_DPadRight], buffer, 256);
    this->ui->drightmap->setText(QString(buffer));
    /*------------------------------------------------------------*/
    this->DLEFT = GAMEPAD_BUTTONS[GamepadButtons::GamepadButtons_DPadLeft];
    get_scan_code(GAMEPAD_BUTTONS[GamepadButtons_DPadLeft], buffer, 256);
    this->ui->dleftmap->setText(QString(buffer));
}

/**
 * @brief Preferences::eventFilter
 * the event filter virtual function is redefined to to filter for mouse and keyboard inputs when user tries to change the button-key maps.
 * checks which object is sending the event and type of event.
 * if event is a keyboard or mousebutton press than map and the object is buttonmap than get the virtual key code of the key pressed and store the change in a temporary variable.
 * @param sender
 * to get the address of the object that is triggering the event.
 * @param event
 * to capture the event that was triggered.
 * @return [bool]
 * true if event is handled else false.
 */
bool Preferences::eventFilter(QObject *sender, QEvent *event)
{
    if(sender == ui->xmap) {
        if(event->type() == QEvent::KeyRelease && ui->xmap->text() == "") {
            QKeyEvent* key_press = (QKeyEvent*)event;
            this->X = key_press->nativeVirtualKey();
            char buffer[256];
            get_scan_code(key_press->nativeVirtualKey(), buffer, 256);
            ui->xmap->setText(QString(buffer));
        }
        else if(event->type() == QEvent::MouseButtonPress && ui->xmap->text() == "") {
            QMouseEvent* mouse_press = static_cast<QMouseEvent*>(event);
            char buffer[256];
            bool valid = true;
            UINT button = mouse_press->button();
            switch(button) {
            case Qt::MouseButton::LeftButton:
                this->X = VK_LBUTTON;
                get_scan_code(VK_LBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::RightButton:
                this->X = VK_RBUTTON;
                get_scan_code(VK_RBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::MiddleButton:
                this->X = VK_MBUTTON;
                get_scan_code(VK_MBUTTON, buffer, 256);
                break;
            default:
                qDebug() << "Some Error Occured No Legal Mouse Button found";
                valid = false;
            }
            if(valid)
            ui->xmap->setText(QString(buffer));
        }
    }
    else if(sender == ui->ymap) {
        if(event->type() == QEvent::KeyRelease) {
            QKeyEvent* key_press = (QKeyEvent*)event;
            this->Y = key_press->nativeVirtualKey();
            char buffer[256];
            get_scan_code(key_press->nativeVirtualKey(), buffer, 256);
            ui->ymap->setText(QString(buffer));
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* mouse_press = static_cast<QMouseEvent*>(event);
            char buffer[256];
            bool valid = true;
            UINT button = mouse_press->button();
            switch(button) {
            case Qt::MouseButton::LeftButton:
                this->Y = VK_LBUTTON;
                get_scan_code(VK_LBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::RightButton:
                this->Y = VK_RBUTTON;
                get_scan_code(VK_RBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::MiddleButton:
                this->Y = VK_MBUTTON;
                get_scan_code(VK_MBUTTON, buffer, 256);
                break;
            default:
                qDebug() << "Some Error Occured No Legal Mouse Button found";
                valid = false;
            }
            if(valid)
            ui->ymap->setText(QString(buffer));
        }
    }
    else if(sender == ui->amap) {
        if(event->type() == QEvent::KeyRelease) {
            QKeyEvent* key_press = static_cast<QKeyEvent*>(event);
            this->A = key_press->nativeVirtualKey();
            char buffer[256];
            get_scan_code(key_press->nativeVirtualKey(), buffer, 256);
            ui->amap->setText(buffer);
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* mouse_press = static_cast<QMouseEvent*>(event);
            char buffer[256];
            bool valid = true;
            UINT button = mouse_press->button();
            switch(button) {
            case Qt::MouseButton::LeftButton:
                this->A = VK_LBUTTON;
                get_scan_code(VK_LBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::RightButton:
                this->A = VK_RBUTTON;
                get_scan_code(VK_RBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::MiddleButton:
                this->A = VK_MBUTTON;
                get_scan_code(VK_MBUTTON, buffer, 256);
                break;
            default:
                qDebug() << "Some Error Occured No Legal Mouse Button found";
                valid = false;
            }
            if(valid)
            ui->amap->setText(QString(buffer));
        }
    }
    else if(sender == ui->bmap) {
        if(event->type() == QEvent::KeyRelease) {
            QKeyEvent* key_press = static_cast<QKeyEvent*>(event);
            this->B = key_press->nativeVirtualKey();
            char buffer[256];
            get_scan_code(key_press->nativeVirtualKey(), buffer, 256);
            ui->bmap->setText(QString(buffer));
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* mouse_press = static_cast<QMouseEvent*>(event);
            char buffer[256];
            bool valid = true;
            UINT button = mouse_press->button();
            switch(button) {
            case Qt::MouseButton::LeftButton:
                this->B = VK_LBUTTON;
                get_scan_code(VK_LBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::RightButton:
                this->B = VK_RBUTTON;
                get_scan_code(VK_RBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::MiddleButton:
                this->B = VK_MBUTTON;
                get_scan_code(VK_MBUTTON, buffer, 256);
                break;
            default:
                qDebug() << "Some Error Occured No Legal Mouse Button found";
                valid = false;
            }
            if(valid)
            ui->bmap->setText(QString(buffer));
        }
    }
    else if(sender == ui->Ltmap) {
        if(event->type() == QEvent::KeyRelease) {
            QKeyEvent* key_press = static_cast<QKeyEvent*>(event);
            this->LT = key_press->nativeVirtualKey();
            char buffer[256];
            get_scan_code(key_press->nativeVirtualKey(), buffer, 256);
            ui->Ltmap->setText(QString(buffer));
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* mouse_press = static_cast<QMouseEvent*>(event);
            char buffer[256];
            bool valid = true;
            UINT button = mouse_press->button();
            switch(button) {
            case Qt::MouseButton::LeftButton:
                this->LT = VK_LBUTTON;
                get_scan_code(VK_LBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::RightButton:
                this->LT = VK_RBUTTON;
                get_scan_code(VK_RBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::MiddleButton:
                this->LT = VK_MBUTTON;
                get_scan_code(VK_MBUTTON, buffer, 256);
                break;
            default:
                qDebug() << "Some Error Occured No Legal Mouse Button found";
                valid = false;
            }
            if(valid)
            ui->Ltmap->setText(QString(buffer));
        }
    }
    else if(sender == ui->Rtmap) {
        if(event->type() == QEvent::KeyRelease) {
            QKeyEvent* key_press = static_cast<QKeyEvent*>(event);
            this->RT = key_press->nativeVirtualKey();
            char buffer[256];
            get_scan_code(key_press->nativeVirtualKey(), buffer, 256);
            ui->Rtmap->setText(QString(buffer));
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* mouse_press = static_cast<QMouseEvent*>(event);
            char buffer[256];
            bool valid = true;
            UINT button = mouse_press->button();
            switch(button) {
            case Qt::MouseButton::LeftButton:
                this->RT = VK_LBUTTON;
                get_scan_code(VK_LBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::RightButton:
                this->RT = VK_RBUTTON;
                get_scan_code(VK_RBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::MiddleButton:
                this->RT = VK_MBUTTON;
                get_scan_code(VK_MBUTTON, buffer, 256);
                break;
            default:
                qDebug() << "Some Error Occured No Legal Mouse Button found";
                valid = false;
            }
            if(valid)
            ui->Rtmap->setText(QString(buffer));
        }
    }
    else if(sender == ui->dupmap) {
        if(event->type() == QEvent::KeyRelease) {
            QKeyEvent* key_press = static_cast<QKeyEvent*>(event);
            this->DUP = key_press->nativeVirtualKey();
            char buffer[256];
            get_scan_code(key_press->nativeVirtualKey(), buffer, 256);
            ui->dupmap->setText(QString(buffer));
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* mouse_press = static_cast<QMouseEvent*>(event);
            char buffer[256];
            bool valid = true;
            UINT button = mouse_press->button();
            switch(button) {
            case Qt::MouseButton::LeftButton:
                this->DUP = VK_LBUTTON;
                get_scan_code(VK_LBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::RightButton:
                this->DUP = VK_RBUTTON;
                get_scan_code(VK_RBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::MiddleButton:
                this->DUP = VK_MBUTTON;
                get_scan_code(VK_MBUTTON, buffer, 256);
                break;
            default:
                qDebug() << "Some Error Occured No Legal Mouse Button found";
                valid = false;
            }
            if(valid)
            ui->dupmap->setText(QString(buffer));
        }
    }
    else if(sender == ui->ddownmap) {
        if(event->type() == QEvent::KeyRelease) {
            QKeyEvent* key_press = static_cast<QKeyEvent*>(event);
            this->DDOWN = key_press->nativeVirtualKey();
            char buffer[256];
            get_scan_code(key_press->nativeVirtualKey(), buffer, 256);
            ui->ddownmap->setText(QString(buffer));
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* mouse_press = static_cast<QMouseEvent*>(event);
            char buffer[256];
            bool valid = true;
            UINT button = mouse_press->button();
            switch(button) {
            case Qt::MouseButton::LeftButton:
                this->DDOWN = VK_LBUTTON;
                get_scan_code(VK_LBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::RightButton:
                this->DDOWN = VK_RBUTTON;
                get_scan_code(VK_RBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::MiddleButton:
                this->DDOWN = VK_MBUTTON;
                get_scan_code(VK_MBUTTON, buffer, 256);
                break;
            default:
                qDebug() << "Some Error Occured No Legal Mouse Button found";
                valid = false;
            }
            if(valid)
            ui->ddownmap->setText(QString(buffer));
        }
    }
    else if(sender == ui->drightmap) {
        if(event->type() == QEvent::KeyRelease) {
            QKeyEvent* key_press = static_cast<QKeyEvent*>(event);
            this->DRIGHT = key_press->nativeVirtualKey();
            char buffer[256];
            get_scan_code(key_press->nativeVirtualKey(), buffer, 256);
            ui->drightmap->setText(QString(buffer));
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* mouse_press = static_cast<QMouseEvent*>(event);
            char buffer[256];
            bool valid = true;
            UINT button = mouse_press->button();
            switch(button) {
            case Qt::MouseButton::LeftButton:
                this->DRIGHT = VK_LBUTTON;
                get_scan_code(VK_LBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::RightButton:
                this->DRIGHT = VK_RBUTTON;
                get_scan_code(VK_RBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::MiddleButton:
                this->DRIGHT = VK_MBUTTON;
                get_scan_code(VK_MBUTTON, buffer, 256);
                break;
            default:
                qDebug() << "Some Error Occured No Legal Mouse Button found";
                valid = false;
            }
            if(valid)
            ui->drightmap->setText(QString(buffer));
        }
    }
    else if(sender == ui->dleftmap) {
        if(event->type() == QEvent::KeyRelease) {
            QKeyEvent* key_press = static_cast<QKeyEvent*>(event);
            this->DLEFT = key_press->nativeVirtualKey();
            char buffer[256];
            get_scan_code(key_press->nativeVirtualKey(), buffer, 256);
            ui->dleftmap->setText(QString(buffer));
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* mouse_press = static_cast<QMouseEvent*>(event);
            char buffer[256];
            bool valid = true;
            UINT button = mouse_press->button();
            switch(button) {
            case Qt::MouseButton::LeftButton:
                this->DLEFT = VK_LBUTTON;
                get_scan_code(VK_LBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::RightButton:
                this->DLEFT = VK_RBUTTON;
                get_scan_code(VK_RBUTTON, buffer, 256);
                break;
            case Qt::MouseButton::MiddleButton:
                this->DLEFT = VK_MBUTTON;
                get_scan_code(VK_MBUTTON, buffer, 256);
                break;
            default:
                qDebug() << "Some Error Occured No Legal Mouse Button found";
                valid = false;
            }
            if(valid)
            ui->dleftmap->setText(QString(buffer));
        }
    }
    return QWidget::eventFilter(sender,event);
}

/**
 * @brief Preferences::keyPressEvent
 * make the Qdialog box ignores the enter key and escape key presses when the focus is on button map
 * @param e
 * capture the key_press event
 */
void Preferences::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return || e->key() == Qt::Key_Escape)
        return;
    return QDialog::keyPressEvent(e);
}

/**
 * @brief Preferences::install_event_filter
 * install the above event filter on all the button maps to capture the key presses when they have the focus.
 */
void Preferences::install_event_filter() {
    ui->xmap->installEventFilter(this);
    ui->ymap->installEventFilter(this);
    ui->amap->installEventFilter(this);
    ui->bmap->installEventFilter(this);
    ui->Ltmap->installEventFilter(this);
    ui->Rtmap->installEventFilter(this);
    ui->ddownmap->installEventFilter(this);
    ui->dupmap->installEventFilter(this);
    ui->drightmap->installEventFilter(this);
    ui->dleftmap->installEventFilter(this);
}

Preferences::~Preferences()
{
    delete ui;
}
